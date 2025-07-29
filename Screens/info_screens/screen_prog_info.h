#ifndef COMMON_H
	#include "../common.h"
#endif

#define INFO_START_ROW 110

Shivam_TXT    PROG_INFO_L1_data = Shivam_TXT(80,  INFO_START_ROW+1*30+5, FreeMonoBold14pt7b, 1, TXT_COLOR, BG_COLOR);
Shivam_TXT    PROG_INFO_L2_data = Shivam_TXT(155, INFO_START_ROW+2*40-5, FreeMonoBold14pt7b, 1, TXT_COLOR, BG_COLOR);

void scr_prog_info_per_second(uint TimeStamp){
	int X=(int)(TimeStamp-OFFSET_T_SECS-program_start_time);
	uint8_t _m,_s;
	uint16_t _h;
	secondsToHMS( X,  _h,  _m,  _s );

	uint16_t num_days=0;
	String T_str;

	if (_h>24){
		uint16_t remainder=_h%24;
		num_days=(_h-remainder)/24;
		_h=remainder;
		T_str=String(num_days)+"days "+String(_h)+"hr "+String(_m)+"min "+String(_s)+"s";
	}
	else
		T_str=String(_h)+"hr "+String(_m)+"min "+String(_s)+"s";


	PROG_INFO_L2_data.print_tft(T_str);
	// return;
}


void scr_prog_info_on_enter(uint TimeStamp){
	myTFT.clear_screen(BG_COLOR);

	// Shivam_TXT title = Shivam_TXT(5, 105, FreeMonoBold12pt7b, 1, TERTIARY_TXT_COLOR, BG_COLOR);
	// title.begin(myTFT.tft);
	// title.print_tft("PROGRAM INFO");
	_PRINT_TITLE_MEDIUM_("PROGRAM INFO")

	Shivam_TXT    PROG_INFO_LABEL = Shivam_TXT(INFO_COL, INFO_START_ROW+35, FreeMonoBold9pt7b, 1, CYAN, BG_COLOR);
	PROG_INFO_LABEL.begin(myTFT.tft);
	PROG_INFO_LABEL.print_tft("Begin: ");

	PROG_INFO_LABEL.increment_y_pos(40);
	PROG_INFO_LABEL.print_tft("Time elapsed: ");

	scr_prog_info_per_second(TimeStamp);

	PROG_INFO_LABEL.increment_y_pos(40);
	PROG_INFO_LABEL.print_tft("Sleeping in: ");

	PROG_INFO_LABEL.increment_y_pos(40);
	PROG_INFO_LABEL.print_tft("# Sleeps: ");


	PROG_INFO_LABEL.increment_x_pos(165);
	PROG_INFO_LABEL.print_tft("# Detected: ");

	PROG_INFO_L1_data.print_tft(get_readable_datetime(convert_to_local_time(program_start_time)));
	// PROG_INFO_L4_data.print_tft(String(NUM_SLEEPS));
}

void scr_prog_info_initialize(Screen* S){
	S->set_func_per_second(scr_prog_info_per_second);
	S->set_func_per_minute(do_nothing);
	S->set_func_per_hour(do_nothing);
	S->set_func_on_enter(scr_prog_info_on_enter);
	S->set_func_on_exit(do_nothing);
	S->set_func_on_touch(do_nothing);

	PROG_INFO_L1_data.begin(myTFT.tft);
	PROG_INFO_L2_data.begin(myTFT.tft);
}