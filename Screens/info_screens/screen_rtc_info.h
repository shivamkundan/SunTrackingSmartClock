#ifndef COMMON_H
	#include "../common.h"
#endif


#define START_ROW 145
Shivam_TXT RTC_INFO_DATA_L1   = Shivam_TXT(70, START_ROW, FreeMonoBold10pt7b, 1, TXT_COLOR, BG_COLOR);
Shivam_TXT RTC_INFO_DATA_L2   = Shivam_TXT(70, START_ROW+40, FreeMonoBold14pt7b, 1, TXT_COLOR, BG_COLOR);
Shivam_TXT RTC_INFO_DATA_L3   = Shivam_TXT(110, START_ROW+2*40, FreeMonoBold14pt7b, 1, TXT_COLOR, BG_COLOR);
Shivam_TXT RTC_INFO_DATA_L4   = Shivam_TXT(110, START_ROW+3*40, FreeMonoBold14pt7b, 1, TXT_COLOR, BG_COLOR);

void scr_rtc_info_per_minute(uint TimeStamp){

	RTC_INFO_DATA_L1.print_tft_ralign(get_readable_datetime(TimeStamp));

	float c = myRTC.temperature() / 4.;
	float f = c * 9. / 5. + 32.;
	RTC_INFO_DATA_L3.print_tft(String(c)+" C / "+String(f)+" f");

	uint16_t now_minute=get_minute_of_day(convert_to_local_time(TimeStamp));
	if (now_minute>1)
		now_minute-=2;
	RTC_INFO_DATA_L4.print_tft(String(temperature_array[now_minute])+" ["+String(humidity_array[now_minute])+"%]");
}

void scr_rtc_info_per_second(uint TimeStamp){


	time_t unix_timestamp =  makeTime(convert_to_tmelements(TimeStamp));
	// char buf[20];
	// sprintf(buf, "%d",unix_timestamp);
	RTC_INFO_DATA_L2.print_tft(printfcomma(unix_timestamp));
}

void scr_rtc_info_on_enter(uint TimeStamp){
	myTFT.clear_screen(BG_COLOR);
	Shivam_TXT title = Shivam_TXT(5, 105, FreeMonoBold12pt7b, 1, TERTIARY_TXT_COLOR, BG_COLOR);
	title.begin(myTFT.tft);
	title.print_tft("RTC INFO");

	// uint16_t curr_y=145;
	Shivam_TXT RTC_INFO_LABEL = Shivam_TXT(5, START_ROW, FreeMonoBold9pt7b,  1, CYAN, BG_COLOR);
	RTC_INFO_LABEL.begin(myTFT.tft);

	RTC_INFO_LABEL.print_tft_no_prev_bg("Stored Time (UTC+0): ");

	RTC_INFO_LABEL.increment_y_pos(40);
	RTC_INFO_LABEL.print_tft_no_prev_bg("UNIX: ");

	scr_rtc_info_per_second(TimeStamp);

	RTC_INFO_LABEL.increment_y_pos(40);

	RTC_INFO_LABEL.print_tft_no_prev_bg("RTC Temp: ");

	RTC_INFO_LABEL.increment_y_pos(40);
	RTC_INFO_LABEL.print_tft_no_prev_bg("Outside: ");

	scr_rtc_info_per_minute(TimeStamp);

}

void scr_rtc_info_initialize(Screen* S){
	S->set_func_per_second(scr_rtc_info_per_second);
	S->set_func_per_minute(scr_rtc_info_per_minute);
	S->set_func_per_hour(do_nothing);
	S->set_func_on_enter(scr_rtc_info_on_enter);
	S->set_func_on_exit(do_nothing);
	S->set_func_on_touch(do_nothing);
	
	RTC_INFO_DATA_L1.begin(myTFT.tft);
	RTC_INFO_DATA_L2.begin(myTFT.tft);
	RTC_INFO_DATA_L3.begin(myTFT.tft);
	RTC_INFO_DATA_L4.begin(myTFT.tft);
}