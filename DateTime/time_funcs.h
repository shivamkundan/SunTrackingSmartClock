#ifndef TIME_FUNCS_H
	#define TIME_FUNCS_H
#endif

#ifndef TIME_VALS_H
	#include "time_vals.h"
#endif

#include <TimeLib.h>

#ifndef ARX_DEBUGLOG_H
	#include <DebugLog.h>
#endif

#define LEAP_YEAR(Y)     ( (Y>0) && !(Y%4) && ( (Y%100) || !(Y%400) ))     // from time-lib

// ------------------------------------------------- //
uint get_day_of_month(time_t inTime);
uint get_month_of_year(time_t inTime);
uint get_day_of_year(time_t inTime);
// ------------------------------------------------- //
String get_day_name(uint8_t dayOfWeek);
int my_dayOfWeek(uint16_t year, uint8_t month, uint8_t day);
void secondsToHMS( const uint32_t seconds, uint16_t &h, uint8_t &m, uint8_t &s );
// ------------------------------------------------- //
void update_previous_vals(uint16_t DD, uint8_t HH, uint8_t MM, uint8_t ss);
tmElements_t convert_to_tmelements(time_t inTime);
void get_individual_time(time_t inTime, uint16_t &DD,uint8_t &HH, uint8_t &MM, uint8_t &SS, bool &AM);
uint8_t get_curr_seconds(time_t inTime);
// ------------------------------------------------- //
String get_readable_day(time_t inTime);
String get_readable_date(time_t inTime);
String get_readable_datetime(time_t inTime);
String get_readable_datetime_full(time_t inTime);
// ------------------------------------------------- //
time_t convert_to_local_time(time_t utcTime);
uint16_t get_minute_of_day(time_t localTime);
void init_previous_vals(time_t TS);
// ------------------------------------------------- //
void check_dst_offset(time_t intime);
String get_readable_time(time_t inTime);
// ------------------------------------------------- //
uint8_t get_month_length(uint8_t month_num, uint16_t year);
String get_event_type(uint8_t event_type);
uint16_t calc_event_index(time_t inTime);
String secondsToHH( const int seconds);
String secondsToMM( const uint32_t seconds);

// ------------------------------------------------- //
String get_month_name(uint8_t month_num)
/* Returns day name string from index */
{
	switch(month_num){
	case 1:
		return ("JAN");
	case 2:
		return ("FEB");
	case 3:
		return ("MAR");
	case 4:
		return ("APR");
	case 5:
		return ("MAY");
	case 6:
		return ("JUN");
	case 7:
		return ("JUL");
	case 8:
		return ("AUG");
	case 9:
		return ("SEP");
	case 10:
		return ("OCT");
	case 11:
		return ("NOV");
	case 12:
		return ("DEC");
	default:
		return("Err");
	}
}

uint get_day_of_month(time_t inTime)
/* Returns day of month */
{
	tmElements_t te=convert_to_tmelements(inTime);
	return te.Day;
}

uint get_month_of_year(time_t inTime)
/* Returns month# of year */
{
	tmElements_t te=convert_to_tmelements(inTime);
	return te.Month;
}

uint get_day_of_year(time_t inTime)
/* Returns value between 1 and 365 (or 366 for leap years). */
{
	uint day_num=0;
	tmElements_t te=convert_to_tmelements(inTime);

	int M=get_month_of_year(inTime);
	for (int i=1;i<M;i++)
		day_num+=get_month_length(i, te.Year+UNIX_START_YEAR);
	day_num+=get_day_of_month(inTime);

	// LOG_DEBUG("day_num final:"+String(day_num));

	return day_num;
}


// ------------------------------------------------- //
String get_day_name(uint8_t dayOfWeek)
/* Returns day name string from index */
{
	switch(dayOfWeek){
	case 1:
		return ("Sun");
	case 2:
		return ("Mon");
	case 3:
		return ("Tue");
	case 4:
		return ("Wed");
	case 5:
		return ("Thu");
	case 6:
		return ("Fri");
	case 0:
		return ("Sat");
	default:
		return("Err");
	}
}

int my_dayOfWeek(uint16_t year, uint8_t month, uint8_t day)
/* Returns day of week string */
{
	uint16_t months[] =
	{
		0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 // days until 1st of month
	};

	uint32_t days = year * 365;   // days until year
	for (uint16_t i = 4; i < year; i+=4)
	{
		if (LEAP_YEAR(i)) days++;  // adjust leap years
	}

	days += months[month-1] + day;
	if ((month > 2) && LEAP_YEAR(year)) days++;
	return days % 7;
}

void secondsToHMS( const uint32_t seconds, uint16_t &h, uint8_t &m, uint8_t &s )
/* Converts raw seconds to separate HMS values */
{
	uint32_t t = seconds;
	s = t % 60;
	t = (t - s)/60;
	m = t % 60;
	t = (t - m)/60;
	h = t;
}
// ------------------------------------------------- //
void update_previous_vals(uint16_t DD, uint8_t HH, uint8_t MM, uint8_t ss)
/* Saves previous values of hh,mm,ss */
{
	prev_ss=ss;
	prev_MM=MM;
	prev_HH=HH;
	prev_DD=DD;
}


tmElements_t convert_to_tmelements(time_t inTime)
/* Convert time_t to tmElements_t */
{
	// LOG_INFO("");
	tmElements_t te;
	te.Second = second(inTime);
	te.Hour = hour(inTime);
	te.Minute = minute(inTime);
	te.Day = day(inTime);
	te.Month = month(inTime);
	te.Year = year(inTime)-UNIX_START_YEAR;

	return te;
}

void get_individual_time(time_t inTime, uint16_t &DD,uint8_t &HH, uint8_t &MM, uint8_t &SS, bool &AM)
/* Computes separate HH:MM:SS from raw seconds input */
{
	// LOG_INFO("");
	tmElements_t te=convert_to_tmelements(inTime);

	int hour_12hr=0;
	AM=isAM(inTime);
	if (AM)
		hour_12hr=(te.Hour==0 ? 12 : te.Hour);
	else
		hour_12hr=(te.Hour==12 ? 12 : te.Hour-12);

	HH=hour_12hr;
	MM=te.Minute;
	SS=te.Second;
	DD=te.Day;

	// MONTH=te.Month;
	// DAY_NUM=te.Day;
	// YEAR=te.Year+UNIX_START_YEAR;
}

uint8_t get_curr_seconds(time_t inTime){
	tmElements_t te=convert_to_tmelements(inTime);
	return te.Second;
}


// ------------------------------------------------- //
String get_readable_day(time_t inTime)
/* Returns day name */
{
	tmElements_t te=convert_to_tmelements(inTime);

	int day=my_dayOfWeek(te.Year+UNIX_START_YEAR,te.Month,te.Day);
	String dayname=get_day_name(day);

	return (dayname);
}

String get_readable_date(time_t inTime)
/* Returns date */
{
	tmElements_t te=convert_to_tmelements(inTime);

	char buf[40];
	sprintf(buf,"%s %d",monthShortStr(te.Month),te.Day);

	return (buf);
}

String get_readable_datetime(time_t inTime)
/* Returns preferred readable date time string */
{
	tmElements_t te=convert_to_tmelements(inTime);

	int hour_12hr=0;
	String am_pm;
	if (isAM(inTime)==1){
		am_pm=" AM";
		if (te.Hour==0)
			hour_12hr=12;
		else
			hour_12hr=te.Hour;
	}
	else{
		am_pm=" PM";
		if (te.Hour==12)
			hour_12hr=12;
		else
			hour_12hr=te.Hour-12;
	}
	char buf[80];
	// sprintf(buf,", %s %d %d %02d:%02d",monthShortStr(te.Month),te.Day,te.Year+UNIX_START_YEAR,hour_12hr,te.Minute);
	// sprintf(buf,", %s %d %02d:%02d:%02d",monthShortStr(te.Month),te.Day,hour_12hr,te.Minute,te.Second);
	sprintf(buf,", %s %d %02d:%02d",monthShortStr(te.Month),te.Day,hour_12hr,te.Minute);
	int day=my_dayOfWeek(te.Year+UNIX_START_YEAR,te.Month,te.Day);

	String dayname=get_day_name(day);

	return (dayname+String(buf)+=am_pm);
}

String get_readable_datetime_full(time_t inTime)
/* Returns preferred readable date time string */
{
	tmElements_t te=convert_to_tmelements(inTime);

	int hour_12hr=0;
	String am_pm;
	if (isAM(inTime)==1){
		am_pm=" AM";
		if (te.Hour==0)
			hour_12hr=12;
		else
			hour_12hr=te.Hour;
	}
	else{
		am_pm=" PM";
		if (te.Hour==12)
			hour_12hr=12;
		else
			hour_12hr=te.Hour-12;
	}
	char buf[80];
	sprintf(buf,", %s %d %d %02d:%02d:%02d",monthShortStr(te.Month),te.Day,te.Year+UNIX_START_YEAR,hour_12hr,te.Minute,te.Second);
	int day=my_dayOfWeek(te.Year+UNIX_START_YEAR,te.Month,te.Day);

	String dayname=get_day_name(day);

	return (dayname+String(buf)+=am_pm);
}


// ------------------------------------------------- //
time_t convert_to_local_time(time_t utcTime)
/* Convert from UTC to local time */
{
	time_t out=utcTime+TIME_ZONE_DIFF_SECS;
	return out;
}


uint16_t get_minute_of_day(time_t localTime)
/* Returns value between 1 and 1440 (1339?). */
{
	uint16_t __DD;
	uint8_t __HH;
	uint8_t __MM;
	uint8_t __ss;
	bool __AM=false;

	// Get minute of day
	uint today_minute=0;
	get_individual_time(localTime, __DD, __HH, __MM, __ss, __AM);

	if (__HH==12 && __AM==true)
		today_minute=__MM;
	else
		today_minute=__HH*60+__MM;

	if (!__AM && __HH!=12)
		today_minute+=(12*60);

	// LOG_DEBUG("\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	// LOG_DEBUG("get_minute_of_day() -> ");
	// LOG_DEBUG(get_readable_datetime(localTime)+" = "+String(__HH)+":"+String(__MM)+":"+String(__ss)+" "+String(__AM));
	// LOG_DEBUG("today_minute# = "+String(today_minute));
	// LOG_DEBUG("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	// LOG_DEBUG("");

	return today_minute;
}

void init_previous_vals(time_t TS){
	uint16_t DD=1;
	uint8_t HH=99;
	uint8_t MM=99;
	uint8_t ss=99;
	bool AM=false;
	get_individual_time(convert_to_local_time(TS), DD, HH, MM, ss, AM);
	update_previous_vals(DD, HH, MM, ss);
}

// ------------------------------------------------- //
void check_dst_offset(time_t intime)
{
	if (intime>=DST_BEGIN_2024 && intime<DST_END_2024){
		TIME_ZONE_DIFF_SECS=TIME_ZONE_DIFF_SECS_CDT;
		DST=true;
	}
	else{
		TIME_ZONE_DIFF_SECS=TIME_ZONE_DIFF_SECS_CST;
		DST=false;
	}
}

String get_readable_time(time_t inTime)
/* Returns date and time in readable format string */
{
	tmElements_t te=convert_to_tmelements(inTime);

	int hour_12hr=0;
	String am_pm;
	String outstr;

	if (isAM(inTime)==1){
		am_pm=" AM";
		hour_12hr=(te.Hour==0 ? 12 : te.Hour);
	}
	else{
		am_pm=" PM";
		hour_12hr=(te.Hour==12 ? 12 : te.Hour-12);
	}
	char buf[80];
	sprintf(buf,"%d:%02d",hour_12hr,te.Minute);
	outstr=buf+am_pm;

	return outstr;
}

// ------------------------------------------------- //

uint8_t get_month_length(uint8_t month_num, uint16_t year)
/* Returns # of days in month (leap year aware) */
{

	// Use switch case because it is faster than if..else
	switch(month_num){
		case 1: return 31;
		case 2: {
			if (LEAP_YEAR(year))
				return 29;
			else
				return 28;
		}
		case 3:  return 31;
		case 4:  return 30;
		case 5:  return 31;
		case 6:  return 30;
		case 7:  return 31;
		case 8:  return 31;
		case 9:  return 30;
		case 10: return 31;
		case 11: return 30;
		case 12: return 31;
		default: return 0; // Just to be safe
	}
}

String get_event_type(uint8_t event_type)
/* Returns event name string from index */
{
	String outstr;

	// LOG_DEBUG ("[get_event_type]");

	switch (event_type){
		case 0:
			return "midnight";
		case 1:
			return "astro dawn";
		case 2:
			return "nautical dawn";
		case 3:
			return "first light";
		case 4:
			return "sunrise";
		case 5:
			return "solar noon";
		case 6:
			return "sunset";
		case 7:
			return "last light";
		case 8:
			return "nautical dusk";
		case 9:
			return "astro dusk";
	}
	return ("err: "+String(event_type));
}

uint16_t calc_event_index(time_t inTime)
/* Compares inTime with stored list */
{
	uint16_t index=0;

	// NOTE: HAVE to use local time to determine mm, otherwise it can lead to the next months array
	int localTime = convert_to_local_time(inTime);
	int mm=convert_to_tmelements(localTime).Month;
	int yy=convert_to_tmelements(localTime).Year+UNIX_START_YEAR;

	int limit= get_month_length(mm,yy)*NUM_ITEMS_PER_DAY;

	// LOG_DEBUG("Month: "+String(mm)+", Year: "+String(yy)+", limit:"+String(limit));

	// NOTE: Using limit+1 here after array upgrade to include 1st of next month
	for (index=START_INDEX;index<limit+1;index++){

		if (index%NUM_ITEMS_PER_DAY!=ASTRO_DAWN_OFFSET && index%NUM_ITEMS_PER_DAY!=NAUTICAL_DAWN_OFFSET && index%NUM_ITEMS_PER_DAY!=NAUTICAL_DUSK_OFFSET && index%NUM_ITEMS_PER_DAY!=ASTRO_DUSK_OFFSET){
			int curr = all_years[yy-BASE_YEAR][mm-1][index];
			int diff = inTime - curr;
			// LOG_DEBUG("diff="+String(diff)+", ");
			// LOG_DEBUG(String(index)+" | "+String(get_event_type(index%NUM_ITEMS_PER_DAY)));
			if (diff<=0)
				break;
		}
	}

	// LOG_DEBUG("index+INDEX_OFFSET: "+String(index+INDEX_OFFSET));

	return index+INDEX_OFFSET;
}
uint16_t calc_event_index_all(time_t inTime)
/* Compares inTime with stored list */
{
	uint16_t index=0;

	// NOTE: HAVE to use local time to determine mm, otherwise it can lead to the next months array
	int localTime = convert_to_local_time(inTime);
	int mm=convert_to_tmelements(localTime).Month;
	int yy=convert_to_tmelements(localTime).Year+UNIX_START_YEAR;

	int limit= get_month_length(mm,yy)*NUM_ITEMS_PER_DAY;

	// LOG_DEBUG("Month: "+String(mm)+", Year: "+String(yy)+", limit:"+String(limit));

	// NOTE: Using limit+1 here after array upgrade to include 1st of next month
	for (index=START_INDEX;index<limit+1;index++){

			int curr = all_years[yy-BASE_YEAR][mm-1][index];
			int diff = inTime - curr;
			// LOG_DEBUG("diff="+String(diff)+", ");
			// LOG_DEBUG(String(index)+" | "+String(get_event_type(index%NUM_ITEMS_PER_DAY)));
			if (diff<=0)
				break;
	}

	// LOG_DEBUG("index+INDEX_OFFSET: "+String(index+INDEX_OFFSET));

	return index+INDEX_OFFSET;
}

String secondsToHH( const int seconds)//, uint16_t &h, uint8_t &m, uint8_t &s )
{
	int t = seconds + (TIME_ZONE_DIFF_SECS);

	int s = t % 60;

	t = (t - s)/60;
	int m = t % 60;

	t = (t - m)/60;
	int h = t;

	char now_hh_str[40];
	sprintf(now_hh_str,"%02d",h);
	return now_hh_str;
}

String secondsToMM( const uint32_t seconds)//, uint16_t &h, uint8_t &m, uint8_t &s )
{
	uint32_t t = seconds + (TIME_ZONE_DIFF_SECS);
	uint16_t s = t % 60;

	t = (t - s)/60;
	uint16_t m = t % 60;

	char now_mm_str[40];
	sprintf(now_mm_str,"%02d",m);

	return now_mm_str;
}

uint get_day_len(int YYYY, int mm, int DD){

	int YY=YYYY-BASE_YEAR;

	int _MM=mm-1;
	int _DD=(DD-1);
	int _ND=NUM_ITEMS_PER_DAY;

	int sunrise     =    all_years[YY][_MM][_DD * _ND + SUNRISE_OFFSET];
	int sunset      =    all_years[YY][_MM][_DD * _ND + SUNSET_OFFSET];

	return (sunset-sunrise);
}

uint TS(int YYYY, int mm, int day_num, int index_offset){
	return all_years[YYYY-BASE_YEAR][mm-1][(day_num-1) * NUM_ITEMS_PER_DAY + index_offset];
}

uint midnight_today(time_t TimeStamp)
/* Time stamp for midnight local time */
{

	time_t localTime = convert_to_local_time(TimeStamp);
	// Retrieve current date/time
	int day_num=get_day_of_month(localTime);
	int mm=convert_to_tmelements(localTime).Month;
	int yy=convert_to_tmelements(localTime).Year+UNIX_START_YEAR;
	uint16_t today_minute=get_minute_of_day(localTime);

	return TS(yy, mm, day_num, MIDNIGHT_OFFSET);
	// return  all_years[yy-BASE_YEAR][mm-1][(day_num-1) * NUM_ITEMS_PER_DAY + MIDNIGHT_OFFSET];
}




uint get_midnight(int yy, int mm, int day_num){ return TS(yy, mm, day_num, MIDNIGHT_OFFSET);}
uint get_astro_dawn(int yy, int mm, int day_num){ return TS(yy, mm, day_num, ASTRO_DAWN_OFFSET);}
uint get_nautical_dawn(int yy, int mm, int day_num){ return TS(yy, mm, day_num, NAUTICAL_DAWN_OFFSET);}

uint get_first_light(int yy, int mm, int day_num){ return TS(yy, mm, day_num, FIRST_LIGHT_OFFSET);}
uint get_sunrise(int yy, int mm, int day_num){ return TS(yy, mm, day_num, SUNRISE_OFFSET);}
uint get_solar_noon(int yy, int mm, int day_num){ return TS(yy, mm, day_num, SOLAR_NOON_OFFSET);}
uint get_sunset(int yy, int mm, int day_num){ return TS(yy, mm, day_num, SUNSET_OFFSET);}
uint get_last_light(int yy, int mm, int day_num){ return TS(yy, mm, day_num, LAST_LIGHT_OFFSET);}
uint get_nautical_dusk(int yy, int mm, int day_num){ return TS(yy, mm, day_num, NAUTICAL_DUSK_OFFSET);}
uint get_astro_dusk(int yy, int mm, int day_num){ return TS(yy, mm, day_num, ASTRO_DUSK_OFFSET);}

uint get_solar_midnight(int yy, int mm, int day_num){ return TS(yy, mm, day_num, SOLAR_NOON_OFFSET + 12*NUM_SECS_IN_DAY);}


void get_today_events(int YYYY, int mm, int DD, int &midnight, int &astro_dawn, int &naut_dawn, int &first_light, int &sunrise, int &solar_noon, int &sunset, int &last_light, int &naut_dusk, int &astro_dusk){

	// int YY=YYYY-BASE_YEAR;

	// int _MM=mm-1;
	// int _DD=(DD-1);
	// int _ND=NUM_ITEMS_PER_DAY;

	midnight    = get_midnight(YYYY,mm,DD);
	astro_dawn  = get_astro_dawn(YYYY,mm,DD);
	naut_dawn   = get_nautical_dawn(YYYY,mm,DD);
	first_light = get_first_light(YYYY,mm,DD);
	sunrise     = get_sunrise(YYYY,mm,DD);
	solar_noon	= get_solar_noon(YYYY,mm,DD);
	sunset      = get_sunset(YYYY,mm,DD);
	last_light  = get_last_light(YYYY,mm,DD);
	naut_dusk   = get_nautical_dusk(YYYY,mm,DD);
	astro_dusk  = get_astro_dusk(YYYY,mm,DD);

	// LOG_DEBUG("\n------- TODAY -------");
	// LOG_DEBUG("midnight:    "+String(get_readable_datetime(convert_to_local_time(midnight))));
	// LOG_DEBUG("astro_dawn:  "+String(get_readable_datetime(convert_to_local_time(astro_dawn))));
	// LOG_DEBUG("naut_dawn:   "+String(get_readable_datetime(convert_to_local_time(naut_dawn))));
	// LOG_DEBUG("first_light: "+String(get_readable_datetime(convert_to_local_time(first_light))));
	// LOG_DEBUG("sunrise:     "+String(get_readable_datetime(convert_to_local_time(sunrise))));
	// LOG_DEBUG("solar_noon:  "+String(get_readable_datetime(convert_to_local_time(solar_noon))));
	// LOG_DEBUG("sunset:      "+String(get_readable_datetime(convert_to_local_time(sunset))));
	// LOG_DEBUG("last_light:  "+String(get_readable_datetime(convert_to_local_time(last_light))));
	// LOG_DEBUG("naut_dusk:   "+String(get_readable_datetime(convert_to_local_time(naut_dusk))));
	// LOG_DEBUG("astro_dusk:  "+String(get_readable_datetime(convert_to_local_time(astro_dusk))));
	// LOG_DEBUG("");
}
