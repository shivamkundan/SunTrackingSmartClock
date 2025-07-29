#ifndef COMMON_H
	#include "common.h"
#endif

// ------------------------------------ String Obkects ------------------------------------ //
Shivam_TXT   time_remaining = Shivam_TXT(100, 135, FreeSansBold40pt7b, 1, TXT_COLOR,           BG_COLOR);
Shivam_TXT   event_name_str2 = Shivam_TXT(100, 215, FreeMonoBold24pt7b, 1, TXT_COLOR,           BG_COLOR);
Shivam_TXT  next_event_str  = Shivam_TXT(100, 275, FreeMonoBold22pt7b, 1, SECONDARY_TXT_COLOR, BG_COLOR);
// Shivam_TXT date_str_scr_one = Shivam_TXT(  0,  15, FreeSansBold10pt7b, 1, SECONDARY_TXT_COLOR, BG_COLOR);
Shivam_TXT       TILL_label = Shivam_TXT( 20, 210, FreeMonoBold16pt7b, 1, SECONDARY_TXT_COLOR, BG_COLOR);
Shivam_TXT   timestr_single = Shivam_TXT(  0,  15, FreeSansBold10pt7b, 1, SECONDARY_TXT_COLOR, BG_COLOR);
Shivam_TXT      AT_label_0  = Shivam_TXT(100, 265, FreeMonoBold12pt7b, 1, SECONDARY_TXT_COLOR, BG_COLOR);

#define _START_ROW 100
#define _START_COL 75
Shivam_TXT  hrs_remain = Shivam_TXT(_START_COL,     _START_ROW,    FreeSansBold44pt7b, 1, TXT_COLOR, BG_COLOR);
Shivam_TXT 			 hours = Shivam_TXT(_START_COL+100, _START_ROW-30, FreeMonoBold18pt7b, 1, TXT_COLOR, BG_COLOR);
Shivam_TXT mins_remain = Shivam_TXT(_START_COL+100, _START_ROW+55, FreeMonoBold38pt7b, 1, TXT_COLOR, BG_COLOR);
Shivam_TXT 		 minutes = Shivam_TXT(_START_COL+200, _START_ROW+30, FreeMonoBold16pt7b, 1, TXT_COLOR, BG_COLOR);


void print_fancy_time_remain(int diff)
/* Print remaining time in staggered order*/
{
	String ___HH=secondsToHH(abs(diff));
	String ___MM=secondsToMM(abs(diff));
	String hms;

	// If less than one hour away
	if (___HH=="00"){
			if (___MM[0]=='0')
				hms=String(___MM[1])+(___MM[1]=='1'? " minute":" minutes");
			else
				hms=String(___MM)+" minutes";

			time_remaining.print_tft_middle(hms);
	}
	else {
		hrs_remain.print_tft(___HH);
		hours.print_tft(___HH=="01" ? "hour" : "hours");
		// if (___HH=="01")
		// 	hours.print_tft("hour");
		// else
		// 	hours.print_tft("hours");
		mins_remain.print_tft(___MM);
		minutes.print_tft("minutes");
	}
}

void scr_next_main(uint TimeStamp, int index_offset){

	myTFT.clear_screen(BG_COLOR);
	// Find the next event
	uint16_t index=calc_event_index(TimeStamp);
	index+=index_offset;

	// ----------------- Calc time diff from event ----------------- //
	String event_name = get_event_type(index%NUM_ITEMS_PER_DAY);
	time_t localTime = convert_to_local_time(TimeStamp);
	int next=retrieve_time_from_index(TimeStamp,index);
	int diff = next - (int)localTime;

	int mm=convert_to_tmelements(localTime).Month;
	int yy=convert_to_tmelements(localTime).Year+UNIX_START_YEAR;
	int curr = all_years[yy-BASE_YEAR][mm-1][index];
	// int diff = localTime - curr;	// Both are in UTC

	print_fancy_time_remain(diff);

	// Line 2
	event_name_str2.print_tft_middle(event_name);

	// Line 3.1
	TILL_label.print_tft("till");
	time_t TT=convert_to_local_time(curr);
	next_event_str.print_tft_middle(get_readable_time(TT));

	AT_label_0.print_tft_no_prev_bg("@");

	// // Line 3.2
	// date_str_scr_one.print_tft(get_readable_day(localTime)+", "+get_readable_date(localTime));
}

void scr_next_per_minute(uint TimeStamp){
	scr_next_main(TimeStamp,0);
}

void scr_next_on_enter(uint TimeStamp){
	scr_next_main(TimeStamp,0);
}

void scr_next_initialize(Screen* S){
	S->set_func_per_second(do_nothing);
	S->set_func_per_minute(scr_next_per_minute);
	S->set_func_per_hour(do_nothing);
	S->set_func_on_enter(scr_next_on_enter);
	S->set_func_on_exit(do_nothing);
	S->set_func_on_touch(do_nothing);
	// S->show_power_info=false;
	// S->show_mw_icon=false;
	// S->show_icons=false;

	time_remaining.begin(myTFT.tft);
	event_name_str2.begin(myTFT.tft);
	next_event_str.begin(myTFT.tft);
	TILL_label.begin(myTFT.tft);
	timestr_single.begin(myTFT.tft);
	AT_label_0.begin(myTFT.tft);

	hrs_remain.begin(myTFT.tft);
	hours.begin(myTFT.tft);
	mins_remain.begin(myTFT.tft);
	minutes.begin(myTFT.tft);
}