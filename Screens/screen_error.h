/*
*	Sometimes the RTC resets. This screen prevents freezing.
*/

#ifndef COMMON_H
	#include "common.h"
#endif

void scr_error_main(uint TimeStamp){
	myTFT.clear_screen(RED);

	Shivam_TXT  txt = Shivam_TXT(0, 140, FreeMonoBold14pt7b, 1, YELLOW, RED);
	txt.begin(myTFT.tft);
	txt.print_tft_middle("ERROR: TS OUT OF BOUNDS");
}

void scr_error_per_second(uint TimeStamp){
	Shivam_TXT  txt2 = Shivam_TXT(0, 170, FreeMonoBold11pt7b, 1, CYAN, RED);
	txt2.begin(myTFT.tft);
	txt2.print_tft_middle("UTC: "+get_readable_datetime_full(TimeStamp));

	if (RTC_SET_MODE)
		rtc_set_loop();
}

void scr_error_on_enter(uint TimeStamp){
	// RTC_SET_MODE=true;
	scr_error_main(TimeStamp);
}

void scr_error_initialize(Screen* S){
	S->set_func_per_second(scr_error_per_second);
	S->set_func_per_minute(scr_error_main);
	S->set_func_per_hour(do_nothing);
	S->set_func_on_enter(scr_error_on_enter);
	S->set_func_on_exit(do_nothing);
	S->set_func_on_touch(do_nothing);
	// S->show_power_info=false;
	// S->show_backlight_info=false;
	// S->show_mw_icon=false;
	// S->show_icons=false;
}





