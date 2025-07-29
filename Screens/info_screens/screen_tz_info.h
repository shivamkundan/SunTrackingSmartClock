#ifndef COMMON_H
	#include "../common.h"
#endif


#define START_ROW 145

void scr_tz_info_on_enter(uint TimeStamp){
	myTFT.clear_screen(BG_COLOR);
	Shivam_TXT title = Shivam_TXT(5, 105, FreeMonoBold12pt7b, 1, TERTIARY_TXT_COLOR, BG_COLOR);
	title.begin(myTFT.tft);
	title.print_tft("TIME ZONE INFO");

	// uint16_t curr_y=145;
	Shivam_TXT label_txt = Shivam_TXT(5, START_ROW, FreeMonoBold9pt7b,  1, CYAN, BG_COLOR);
	label_txt.begin(myTFT.tft);

	label_txt.print_tft_no_prev_bg("Time Diff: ");

	label_txt.increment_y_pos(40);
	label_txt.print_tft_no_prev_bg("Curr TZ: ");


	label_txt.increment_y_pos(40);
	label_txt.print_tft_no_prev_bg("DST: ");

	label_txt.increment_y_pos(40);
	label_txt.print_tft_no_prev_bg("T OFFSET: ");

	Shivam_TXT TZ_INFO_DATA_L1   = Shivam_TXT(110, START_ROW, FreeMonoBold14pt7b, 1, TXT_COLOR, BG_COLOR);
	TZ_INFO_DATA_L1.begin(myTFT.tft);
	TZ_INFO_DATA_L1.print_tft(String(TIME_ZONE_DIFF_SECS)+" s");

	TZ_INFO_DATA_L1.increment_y_pos(40);
	TZ_INFO_DATA_L1.print_tft(DST ? "CDT (UTC-5)" : "CST (UTC-6)");

	TZ_INFO_DATA_L1.increment_y_pos(40);
	TZ_INFO_DATA_L1.print_tft(DST ? "Yes" : "No");

	TZ_INFO_DATA_L1.increment_y_pos(40);
	TZ_INFO_DATA_L1.print_tft(String(OFFSET_T_SECS)+" s");
}

void scr_tz_info_initialize(Screen* S){
	S->set_func_per_second(do_nothing);
	S->set_func_per_minute(do_nothing);
	S->set_func_per_hour(do_nothing);
	S->set_func_on_enter(scr_tz_info_on_enter);
	S->set_func_on_exit(do_nothing);
	S->set_func_on_touch(do_nothing);
}