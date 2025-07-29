// #ifndef SCREEN_CLASS_H
// 	#include "ScreenClass.h"
// #endif

// // #ifndef Shivam_PicoW_TFT_H
// // 	#include <Shivam_PicoW_TFT.h>
// // #endif

// // #ifndef COLORS_H
// // 	#include "../colors.h"
// // #endif

// #ifndef TIME_FUNCS_H
// 	#include "../DateTime/time_funcs.h"
// #endif



// #ifndef GLOBALS_H
// 	#include "../globals.h"
// #endif
#ifndef Shivam_PicoW_TFT_H
	#include <Shivam_PicoW_TFT.h>
#endif

#ifndef SHIVAM_TXT_H
	#include <Shivam_TXT.h>
#endif

#ifndef TIME_FUNCS_H
	#include "../DateTime/time_funcs.h"
#endif

#ifndef STRING_DEFS_H
	#include "string_defs.h"
#endif

#ifndef GLOBALS_H
	#include "../globals.h"
#endif

#ifndef SCREEN_CLASS_H
	#include "ScreenClass.h"
#endif

#ifndef BITMAPS_H
	#include "../Bitmaps/bitmaps.h"
#endif

// Day length in seconds (sans twilight)
#define JUN_20_DAYLEN 53192
#define DEC_21_DAYLEN 34392
#define MAR_19_DAYLEN 43640
#define SEP_22_DAYLEN 43662
// #define EQUINOX_AVG_DAYLEN 43651
#define EQUINOX_AVG_DAYLEN ((MAR_19_DAYLEN + SEP_22_DAYLEN) /2 )

#define DAY_LEN_CURVE_COLOR  PURPLE
#define START_Y_2 118
#define LABEL_STR_Y_POS 295
#define _DRAW_SEPARATORS_ {\
	myTFT.tft.drawLine(160, 250, 160, 300, LIGHTGREY);\
	myTFT.tft.drawLine(320, 250, 320, 300, LIGHTGREY);\
}

Shivam_TXT  SCR_DAYLEN_L1 = Shivam_TXT(SCR_DAYLIGHT_COL, 245, FreeMonoBold12pt7b, 1, SECONDARY_TXT_COLOR, BG_COLOR);



void scr_daylen_main(uint TimeStamp){

	myTFT.clear_screen(BG_COLOR);
	time_t localTime = convert_to_local_time(TimeStamp);

	// Show title
	Shivam_TXT title_str = Shivam_TXT(1, 95,      FreeMonoBold12pt7b, 1, TERTIARY_TXT_COLOR,    BG_COLOR);
	title_str.begin(myTFT.tft);
	title_str.print_tft("DAYLIGHT LEN");

	// ----------------- Draw daylight length graph ----------------- //
	uint start_x=SCREEN_W/2-DAY_LEN_BMP_W/2;
	myTFT.tft.drawBitmap(start_x,START_Y_2,bitmap_day_len, DAY_LEN_BMP_W, DAY_LEN_BMP_H, DAY_LEN_CURVE_COLOR);

	// ------------------ Show length of day today ------------------ //
	int mm=convert_to_tmelements(localTime).Month;
	// uint32_t DAY_LEN=DAY_LEN_ARR[mm-1][get_day_of_month(localTime)-1];
	uint day_of_year=get_day_of_year(localTime);
	uint32_t DAY_LEN=DAY_LENGTH_ARR[day_of_year];
	uint8_t m,s;
	uint16_t h;
	secondsToHMS(DAY_LEN,h,m,s);
	String DL=String(h)+"hr "+String(m)+"min "+String(s)+"s";
	SCR_DAYLEN_L1.set_y_pos(START_Y_2+DAY_LEN_BMP_H+15);
	SCR_DAYLEN_L1.print_tft_middle(DL);

	// ---------------- Mark the current day on plot ---------------- //
	int now_x_pos=custom_map (day_of_year,0,NUM_DAYS_YEAR-1,start_x,start_x+DAY_LEN_BMP_W);
	int now_y_pos=(int) custom_map(DAY_LEN,DEC_21_DAYLEN,JUN_20_DAYLEN,START_Y_2+DAY_LEN_BMP_H,START_Y_2);
	myTFT.tft.drawLine(now_x_pos, START_Y_2+DAY_LEN_BMP_H, now_x_pos, START_Y_2, LIGHTGREY);
	Shivam_TXT today_str= Shivam_TXT(now_x_pos-20, now_y_pos+35, FreeMonoBold9pt7b, 1, YELLOW, BG_COLOR);
	today_str.begin(myTFT.tft);
	today_str.print_tft_no_prev_bg(get_month_name(mm)+" "+String(get_day_of_month(localTime)));
	// myTFT.tft.drawBitmap(now_x_pos-SUN_SMALL_W/2, (int) now_y_pos-SUN_SMALL_H/2,sun_small_bmp, SUN_SMALL_W, SUN_SMALL_H, SUN_MARKER_COLOR);
	_SMALL_SUN_(now_x_pos, now_y_pos, SUN_MARKER_COLOR);

	// --------------- Calc time diff from solstices  --------------- //
	Shivam_TXT diff_str= Shivam_TXT(5, 270, FreeMonoBold9pt7b, 1, TXT_COLOR, BG_COLOR);
	diff_str.begin(myTFT.tft);

	// Time diff from summer solstice
	secondsToHMS(JUN_20_DAYLEN-DAY_LEN,h,m,s);
	DL="- "+String(h)+"h "+String(m)+"m "+String(s)+"s";
	uint16_t w_DL=get_text_width(DL, FreeMonoBold9pt7b);
	diff_str.set_x_pos(80-(int)(w_DL/2)-5);
	diff_str.print_tft_no_prev_bg(DL);
	label_str.set_x_pos(15);
	label_str.set_y_pos(LABEL_STR_Y_POS);
	label_str.print_tft_no_prev_bg("SUMMER SOLSTICE");

	// Time diff from winter solstice
	secondsToHMS(DAY_LEN-DEC_21_DAYLEN,h,m,s);
	DL="+ "+String(h)+"h "+String(m)+"m "+String(s)+"s";
	diff_str.set_x_pos(170);
	diff_str.print_tft_middle(DL);
	label_str.print_tft_middle("WINTER SOLSTICE");

	// ----------------- Time diff from equinox avg ----------------- //
	if (DAY_LEN>EQUINOX_AVG_DAYLEN){
		secondsToHMS(DAY_LEN-EQUINOX_AVG_DAYLEN,h,m,s);
		DL="+ "+String(h)+"h "+String(m)+"m "+String(s)+"s";
	}
	else{
		secondsToHMS(EQUINOX_AVG_DAYLEN-DAY_LEN,h,m,s);
		DL="- "+String(h)+"h "+String(m)+"m "+String(s)+"s";
	}
	w_DL=get_text_width(DL, FreeMonoBold9pt7b);
	diff_str.set_x_pos(400-(int)(w_DL/2));
	diff_str.print_tft_no_prev_bg(DL);
	uint16_t w1=get_text_width("EQUINOX AVG", Font4x5Fixed);

	label_str.set_x_pos(320+w1);
	label_str.print_tft_no_prev_bg("EQUINOX AVG");

	label_str.set_y_pos(START_Y_2+DAY_LEN_BMP_H-16);
	label_str.print_tft_middle("TODAY");

	// -------- Draw separators -------- //
	_DRAW_SEPARATORS_


	uint mar_19_x_pos = custom_map(MAR_19, 1, NUM_DAYS_YEAR, start_x, start_x+DAY_LEN_BMP_W )-MARKER_RAD_DIV_2;
	uint jun_20_x_pos = custom_map(JUN_20, 1, NUM_DAYS_YEAR, start_x, start_x+DAY_LEN_BMP_W )-MARKER_RAD_DIV_2;
	uint sep_22_x_pos = custom_map(SEP_22, 1, NUM_DAYS_YEAR, start_x, start_x+DAY_LEN_BMP_W )-MARKER_RAD_DIV_2;
	uint dec_21_x_pos = custom_map(DEC_21, 1, NUM_DAYS_YEAR, start_x, start_x+DAY_LEN_BMP_W )-MARKER_RAD_DIV_2;

	uint mar_19_y_pos = START_Y_2+DAY_LEN_BMP_H/2;
	uint jun_20_y_pos = START_Y_2+3;
	uint sep_22_y_pos = START_Y_2+DAY_LEN_BMP_H/2;
	uint dec_21_y_pos = START_Y_2+DAY_LEN_BMP_H-3;

	// ----- Draw solstice and equinox markers ----- //
	// Markers
	// _2_DRAW_MARKERS_
	myTFT.tft.fillCircle(mar_19_x_pos, mar_19_y_pos, _Z);
	myTFT.tft.fillCircle(jun_20_x_pos, jun_20_y_pos, _Z);
	myTFT.tft.fillCircle(sep_22_x_pos, sep_22_y_pos, _Z);
	myTFT.tft.fillCircle(dec_21_x_pos, dec_21_y_pos, _Z);

	// Fine tuning the y values
	mar_19_y_pos-=12;
	jun_20_y_pos-=12;
	sep_22_y_pos-=12;
	dec_21_y_pos+=20;


	// Fine tuning the x values
	mar_19_x_pos-=70;
	jun_20_x_pos-=30;
	sep_22_x_pos+=15;
	dec_21_x_pos-=40;

	date_marker_str.set_x_pos(mar_19_x_pos);
	date_marker_str.set_y_pos(mar_19_y_pos);
	date_marker_str.print_tft_no_prev_bg("MAR 19");

	day_len_marker_str.set_x_pos(mar_19_x_pos-10);
	day_len_marker_str.set_y_pos(mar_19_y_pos-23);
	day_len_marker_str.print_tft_no_prev_bg("12:07:20");

	date_marker_str.set_x_pos(jun_20_x_pos);
	date_marker_str.set_y_pos(jun_20_y_pos);
	date_marker_str.print_tft_no_prev_bg("JUN 20");

	day_len_marker_str.set_x_pos(jun_20_x_pos+10);
	day_len_marker_str.set_y_pos(jun_20_y_pos-23);
	day_len_marker_str.print_tft_no_prev_bg("14:46:32");

	date_marker_str.set_x_pos(sep_22_x_pos);
	date_marker_str.set_y_pos(sep_22_y_pos);
	date_marker_str.print_tft_no_prev_bg("SEP 22");

	day_len_marker_str.set_x_pos(sep_22_x_pos+20);
	day_len_marker_str.set_y_pos(sep_22_y_pos-23);
	day_len_marker_str.print_tft_no_prev_bg("12:07:42");

	date_marker_str.set_x_pos(dec_21_x_pos);
	date_marker_str.set_y_pos(dec_21_y_pos);
	date_marker_str.print_tft_no_prev_bg("DEC 21");

	day_len_marker_str.set_x_pos(dec_21_x_pos+10);
	day_len_marker_str.set_y_pos(dec_21_y_pos-35);
	day_len_marker_str.print_tft_no_prev_bg("09:33:12");

	// // ----------- Draw labels ----------- //
		// _2_DRAW_LABELS_
}



void scr_daylen_per_minute(uint TimeStamp){
	scr_daylen_main(TimeStamp);
}

void scr_daylen_on_enter(uint TimeStamp){
	scr_daylen_main(TimeStamp);
	return;
}

void scr_daylen_initialize(Screen* S){
	S->set_func_per_second(do_nothing);
	S->set_func_per_minute(scr_daylen_per_minute);
	S->set_func_per_hour(do_nothing);
	S->set_func_on_enter(scr_daylen_on_enter);
	S->set_func_on_exit(do_nothing);
	S->set_func_on_touch(do_nothing);

	S->show_power_info=false;

	SCR_DAYLEN_L1.begin(myTFT.tft);

}
