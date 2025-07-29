#ifndef COMMON_H
	#include "common.h"
#endif

#define NUM_FUTURE_EVENTS 6

#define PADDING_VAL 23
#define LINE_SPACING 20
#define SROW 95 // starting row

String secondsToHM( const uint32_t seconds)//, uint16_t &h, uint8_t &m, uint8_t &s )
/* Converts raw seconds to HH:MM string */
{
	uint32_t t = seconds + (TIME_ZONE_DIFF_SECS);

	uint16_t s = t % 60;

	t = (t - s)/60;
	uint16_t m = t % 60;

	t = (t - m)/60;
	uint16_t h = t;

	char now_time_str[40];
	sprintf(now_time_str,"%02d:%02d",h,m);

	return now_time_str;
}


String get_formatted_datetime(time_t inTime)
/* for screen_detailed() : Returns preferred readable date time string  */
{
	tmElements_t te=convert_to_tmelements(inTime);

	int hour_12hr=0;
	String am_pm;
	if (isAM(inTime)==1){
		am_pm=" AM";
		hour_12hr = (te.Hour==0 ? 12 : te.Hour);
	}
	else{
		am_pm=" PM";
		hour_12hr = (te.Hour==12 ? 12 : te.Hour-12);
	}
	char buf[80];
	sprintf(buf,", %s %d %02d:%02d",monthShortStr(te.Month),te.Day,hour_12hr,te.Minute);
	int day=my_dayOfWeek(te.Year+UNIX_START_YEAR,te.Month,te.Day);

	String dayname=get_day_name(day);

	return (dayname+String(buf)+=am_pm);
}

void print_concise(uint16_t index, time_t inTime, uint16_t col, uint16_t row)
/* Print time remaining till next event */
{


	String event_name;

	// Need to shorten nautical dawn/dusk name
	if (index%NUM_ITEMS_PER_DAY==NAUTICAL_DUSK_OFFSET)
		event_name = "naut dusk";
	else if (index%NUM_ITEMS_PER_DAY==NAUTICAL_DAWN_OFFSET)
		event_name = "naut dawn";
	else
		event_name = get_event_type(index%NUM_ITEMS_PER_DAY);

	inTime = convert_to_local_time(inTime);
	int mm=convert_to_tmelements(inTime).Month;
	int yy=convert_to_tmelements(inTime).Year+UNIX_START_YEAR;
	int curr = all_years[yy-BASE_YEAR][mm-1][index];
	int diff = inTime - curr;	// Both are in UTC

	String hms=secondsToHM(abs(diff));
	String temp_str=hms+" till "+event_name+" ";

	// add padding for alignment
	if (temp_str.length()<PADDING_VAL)
		for (int i=0;i<(temp_str.length()-(PADDING_VAL));i++)
			temp_str+=" ";

	Shivam_TXT outstr=Shivam_TXT(col,row,FreeMonoBold9pt7b,1,TXT_COLOR,BG_COLOR);
	outstr.begin(myTFT.tft);

	outstr.print_tft(temp_str+get_formatted_datetime(convert_to_local_time(curr)));
}

void print_info(time_t TimeStamp)
/* Print current day/date/time */
{
	myTFT.clear_screen(BG_COLOR);
	uint16_t index=calc_event_index_all(TimeStamp);
	int row=SROW;
	for (uint8_t i=0;i<NUM_FUTURE_EVENTS;i++){
		print_concise(index+i, TimeStamp,0,row);
		row+=LINE_SPACING+20;
	}
}


void scr_next_five_per_minute(uint TimeStamp){
	print_info(TimeStamp);
}
void scr_next_five_per_second(uint TimeStamp){
	return;
}

void scr_next_five_on_enter(uint TimeStamp){
	print_info(TimeStamp);
}


void scr_next_five_initialize(Screen* S){
	S->set_func_per_second(scr_next_five_per_second);
	S->set_func_per_minute(scr_next_five_per_minute);
	S->set_func_per_hour(do_nothing);
	S->set_func_on_enter(scr_next_five_on_enter);
	S->set_func_on_exit(do_nothing);
	S->set_func_on_touch(do_nothing);

	S->show_power_info=false;
	S->show_backlight_info=false;
	// S->show_mw_icon=false;
	// S->show_icons=false;
}