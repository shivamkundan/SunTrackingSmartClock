#ifndef SCREEN_CLASS_H
	#include "ScreenClass.h"
#endif

#ifndef COLORS_H
    #include "../colors.h"
#endif

#ifndef BITMAPS_H
	#include "../Bitmaps/bitmaps.h"
#endif


#ifndef GLOBALS_H
	#include "../globals.h"
#endif

// Show title
#define _TTLE_(TITLE){\
Shivam_TXT title_str = Shivam_TXT(1, 95,      FreeMonoBold12pt7b, 1, TERTIARY_TXT_COLOR,    BG_COLOR);\
title_str.begin(myTFT.tft);\
title_str.print_tft(TITLE);\
}

// ---------------------------------------------------------------------------------------------------------------------- //
// --------------------------------------------- for screen_daylight_diff() --------------------------------------------- //
#define MARKER_RAD 4
#define MARKER_RAD_DIV_2 MARKER_RAD/2
#define START_Y 135
#define START_X 0

// ..........................................................................................................
// Mapped vals for markers
// uint mar_19_x_pos = custom_map(MAR_19, 1, NUM_DAYS_YEAR, START_X, START_X+DAY_DIFF_BMP_W) - MARKER_RAD_DIV_2;
// uint jun_20_x_pos = custom_map(JUN_20, 1, NUM_DAYS_YEAR, START_X, START_X+DAY_DIFF_BMP_W) - MARKER_RAD_DIV_2;
// uint sep_22_x_pos = custom_map(SEP_22, 1, NUM_DAYS_YEAR, START_X, START_X+DAY_DIFF_BMP_W) - MARKER_RAD_DIV_2;
// uint dec_21_x_pos = custom_map(DEC_21, 1, NUM_DAYS_YEAR, START_X, START_X+DAY_DIFF_BMP_W) - MARKER_RAD_DIV_2;
#define MAR_19_X_POS 116
#define JUN_20_X_POS 224
#define SEP_22_X_POS 333
#define DEC_21_X_POS 438

// uint mar_19_y_pos = START_Y;
// uint jun_20_y_pos = zero_line_y_pos;
// uint sep_22_y_pos = START_Y+DAY_DIFF_BMP_H;
// uint dec_21_y_pos = zero_line_y_pos;
#define MAR_19_Y_POS 130
#define JUN_20_Y_POS 190
#define SEP_22_Y_POS 251
#define DEC_21_Y_POS 190

// #define _X1 MAR_19_X_POS-MARKER_RAD_DIV_2
// #define _Y1 MAR_19_Y_POS-MARKER_RAD_DIV_2
// #define _X2 JUN_20_X_POS-MARKER_RAD_DIV_2
// #define _Y2 JUN_20_Y_POS-MARKER_RAD_DIV_2
// #define _X3 SEP_22_X_POS-MARKER_RAD_DIV_2
// #define _Y3 SEP_22_Y_POS-MARKER_RAD_DIV_2
// #define _X4 DEC_21_X_POS-MARKER_RAD_DIV_2
// #define _Y4 DEC_21_Y_POS-MARKER_RAD_DIV_2
#define _X1 114
#define _Y1 128
#define _X2 222
#define _Y2 188
#define _X3 331
#define _Y3 249
#define _X4 436
#define _Y4 188

#define _Z MARKER_RAD, MINI_TXT_COLOR
#define _Z1 MINI_TXT_FONT, 1, MINI_TXT_COLOR, BG_COLOR

#define _DRAW_MARKERS_ {\
	myTFT.tft.fillCircle(_X1, _Y1, _Z);\
	myTFT.tft.fillCircle(_X2, _Y2, _Z);\
	myTFT.tft.fillCircle(_X3, _Y3, _Z);\
	myTFT.tft.fillCircle(_X4, _Y4, _Z);\
}

#define _DRAW_MARKER_LABELS_ {\
	Shivam_TXT mar19_str= Shivam_TXT(MAR_19_X_POS-20, MAR_19_Y_POS-12, _Z1);\
	mar19_str.begin(myTFT.tft);\
	mar19_str.print_tft_no_prev_bg("MAR 19");\
	\
	Shivam_TXT jun20_str= Shivam_TXT(JUN_20_X_POS+10, JUN_20_Y_POS-12, _Z1);\
	jun20_str.begin(myTFT.tft);\
	jun20_str.print_tft_no_prev_bg("JUN 20");\
	\
	Shivam_TXT sep22_str= Shivam_TXT(SEP_22_X_POS-25, SEP_22_Y_POS+20, _Z1);\
	sep22_str.begin(myTFT.tft);\
	sep22_str.print_tft_no_prev_bg("SEP 22");\
	\
	Shivam_TXT dec21_str= Shivam_TXT(DEC_21_X_POS-30, DEC_21_Y_POS-12, _Z1);\
	dec21_str.begin(myTFT.tft);\
	dec21_str.print_tft_no_prev_bg("DEC 21");\
}

#define DAY_DIFF_CURVE_COLOR RED



int zero_line_y_pos=START_Y+(int)DAY_DIFF_BMP_H/2;

void disp_time_diff(int localTime)
/* Show diff from yesterday */
{
	// Calc day len
	uint day_of_year=get_day_of_year(localTime);
	int mm=convert_to_tmelements(localTime).Month;

	int32_t DAY_LEN=DAY_LENGTH_ARR[day_of_year];
	uint8_t m,s;
	uint16_t h;
	secondsToHMS(DAY_LEN,h,m,s);
	String total_DL=String(h)+"hr "+String(m)+"min "+String(s)+"s";
	// SCR_DAYLIGHT_L1.set_x_pos(20);
	SCR_DAYLIGHT_L1.print_tft(total_DL);

	// ------ Calc day diff ------ //
	int32_t DAY_DIFF = DAY_LENGTH_ARR[day_of_year] - DAY_LENGTH_ARR[day_of_year-1];

	// ------ Display day diff ------ //
	secondsToHMS(abs(DAY_DIFF),h,m,s);
	String DL= (m==0 ? String(s)+"s" : String(m)+"min "+String(s)+"s");
	SCR_DAYLIGHT_L2.print_tft_no_prev_bg(DL+ (DAY_DIFF<0 ? " shorter" : " longer") +" than yesterday");

	// ------ Draw marker showing today ------ //
	int now_x_pos=custom_map (day_of_year,0,NUM_DAYS_YEAR-1,START_X,START_X+DAY_DIFF_BMP_W);
	int now_y_pos=(int) custom_map(DAY_DIFF,MIN_DAY_DIFF,MAX_DAY_DIFF,START_Y+DAY_DIFF_BMP_H,START_Y);
	_SMALL_SUN_(now_x_pos, now_y_pos, SUN_MARKER_COLOR);

	// ------ Draw vertical line to mark today ------ //
	Shivam_TXT today_str= Shivam_TXT(0, 0, FreeMonoBold12pt7b, 1, TXT_COLOR, BG_COLOR);
		today_str.begin(myTFT.tft);
	if (day_of_year<JUN_20){
		today_str.set_pos(now_x_pos-20, zero_line_y_pos+20);
		myTFT.tft.drawLine(now_x_pos, START_Y, now_x_pos, zero_line_y_pos, LIGHTGREY);
	}
	else{
		today_str.set_pos(now_x_pos-20, zero_line_y_pos - 30);
		myTFT.tft.drawLine(now_x_pos, zero_line_y_pos, now_x_pos, now_y_pos, LIGHTGREY);
	}

	label_str.set_pos(1,265);
	label_str.print_tft_no_prev_bg("TODAY IS:");
	today_str.print_tft_no_prev_bg(get_month_name(mm)+" "+String(get_day_of_month(localTime)));


	// =================================================================
	// --------------------------- Draw matkers --------------------------- //
	uint mar_19_x_pos = custom_map(MAR_19, 1, NUM_DAYS_YEAR, START_X, START_X+DAY_DIFF_BMP_W) - MARKER_RAD_DIV_2;
	uint jun_20_x_pos = custom_map(JUN_20, 1, NUM_DAYS_YEAR, START_X, START_X+DAY_DIFF_BMP_W) - MARKER_RAD_DIV_2;
	uint sep_22_x_pos = custom_map(SEP_22, 1, NUM_DAYS_YEAR, START_X, START_X+DAY_DIFF_BMP_W) - MARKER_RAD_DIV_2;
	uint dec_21_x_pos = custom_map(DEC_21, 1, NUM_DAYS_YEAR, START_X, START_X+DAY_DIFF_BMP_W) - MARKER_RAD_DIV_2;

	// LOG_DEBUG("MAR_19_X_POS: "+String(mar_19_x_pos));
	// LOG_DEBUG("JUN_20_X_POS: "+String(jun_20_x_pos));
	// LOG_DEBUG("SEP_22_X_POS: "+String(sep_22_x_pos));
	// LOG_DEBUG("DEC_21_X_POS: "+String(dec_21_x_pos));

	uint mar_19_y_pos = START_Y;
	uint jun_20_y_pos = zero_line_y_pos;
	uint sep_22_y_pos = START_Y+DAY_DIFF_BMP_H;
	uint dec_21_y_pos = zero_line_y_pos;
	// LOG_DEBUG("MAR_19_Y_POS: "+String(mar_19_y_pos));
	// LOG_DEBUG("JUN_20_Y_POS: "+String(jun_20_y_pos));
	// LOG_DEBUG("SEP_22_Y_POS: "+String(sep_22_y_pos));
	// LOG_DEBUG("DEC_21_Y_POS: "+String(dec_21_y_pos));

	// LOG_DEBUG("_X1: " +String(mar_19_x_pos-MARKER_RAD_DIV_2));
	// LOG_DEBUG("_Y1: " +String(mar_19_y_pos-MARKER_RAD_DIV_2));

	// LOG_DEBUG("_X2: " +String(jun_20_x_pos-MARKER_RAD_DIV_2));
	// LOG_DEBUG("_Y2: " +String(jun_20_y_pos-MARKER_RAD_DIV_2));

	// LOG_DEBUG("_X3: " +String(sep_22_x_pos-MARKER_RAD_DIV_2));
	// LOG_DEBUG("_Y3: " +String(sep_22_y_pos-MARKER_RAD_DIV_2));

	// LOG_DEBUG("_X4: " +String(dec_21_x_pos-MARKER_RAD_DIV_2));
	// LOG_DEBUG("_Y4: " +String(dec_21_y_pos-MARKER_RAD_DIV_2));

	myTFT.tft.fillCircle(mar_19_x_pos-MARKER_RAD_DIV_2, mar_19_y_pos-MARKER_RAD_DIV_2, MARKER_RAD, MINI_TXT_COLOR);
	myTFT.tft.fillCircle(jun_20_x_pos-MARKER_RAD_DIV_2, jun_20_y_pos-MARKER_RAD_DIV_2, MARKER_RAD, MINI_TXT_COLOR);
	myTFT.tft.fillCircle(sep_22_x_pos-MARKER_RAD_DIV_2, sep_22_y_pos-MARKER_RAD_DIV_2, MARKER_RAD, MINI_TXT_COLOR);
	myTFT.tft.fillCircle(dec_21_x_pos-MARKER_RAD_DIV_2, dec_21_y_pos-MARKER_RAD_DIV_2, MARKER_RAD, MINI_TXT_COLOR);

	Shivam_TXT mar19_str= Shivam_TXT(mar_19_x_pos-20, mar_19_y_pos-12, _Z1);
	mar19_str.begin(myTFT.tft);
	mar19_str.print_tft_no_prev_bg("MAR 19");
	day_len_marker_str.set_pos(mar_19_x_pos+55, mar_19_y_pos-13);
	day_len_marker_str.print_tft_no_prev_bg("+ 2m 26s");

	Shivam_TXT jun20_str= Shivam_TXT(jun_20_x_pos+10, jun_20_y_pos-12, _Z1);
	jun20_str.begin(myTFT.tft);
	jun20_str.print_tft_no_prev_bg("JUN 20");
	day_len_marker_str.set_pos(jun_20_x_pos+83, jun_20_y_pos-14);
	day_len_marker_str.print_tft_no_prev_bg("+ 0s");
	// + 1s longer

	Shivam_TXT sep22_str= Shivam_TXT(sep_22_x_pos-25, sep_22_y_pos+20, _Z1);
	sep22_str.begin(myTFT.tft);
	sep22_str.print_tft_no_prev_bg("SEP 22");
	day_len_marker_str.set_pos(sep_22_x_pos+50, sep_22_y_pos+18);
	day_len_marker_str.print_tft_no_prev_bg("- 2m 24s");

	Shivam_TXT dec21_str= Shivam_TXT(dec_21_x_pos-60, dec_21_y_pos-12, _Z1);
	dec21_str.begin(myTFT.tft);
	dec21_str.print_tft_no_prev_bg("DEC 21");
	day_len_marker_str.set_pos(dec_21_x_pos-95, dec_21_y_pos-14);
	day_len_marker_str.print_tft_no_prev_bg("- 0s");
	// 0 seconds longer

	// =================================================================
}

void scr_daylight_diff_main(uint TimeStamp){

	int localTime = convert_to_local_time(TimeStamp);

	myTFT.clear_screen(BG_COLOR);
	_TTLE_("DAYLIGHT CHANGE")

	// Draw  dotted line for y=0
	draw_dotted_hline( myTFT.tft,5, 10, START_X, START_X+DAY_DIFF_BMP_W, zero_line_y_pos, DARKGREY);

	// Draw difference plot
	myTFT.tft.drawBitmap(START_X,START_Y,epd_bitmap_daydiff2024, DAY_DIFF_BMP_W, DAY_DIFF_BMP_H, DAY_DIFF_CURVE_COLOR);

	disp_time_diff(localTime);
}

// -------------------------------------------------------------------------

void scr_daylight_diff_on_exit(uint TimeStamp){
	LOG_TRACE("Exiting");
}

// -------------------------------------------------------------------------
void scr_daylight_diff_initialize(Screen* S){
	S->set_func_per_second(do_nothing);
	S->set_func_per_minute(scr_daylight_diff_main);
	S->set_func_per_hour(do_nothing);
	S->set_func_on_enter(scr_daylight_diff_main);
	S->set_func_on_exit(scr_daylight_diff_on_exit);
	S->set_func_on_touch(do_nothing);

	SCR_DAYLIGHT_L1.begin(myTFT.tft);
	SCR_DAYLIGHT_L2.begin(myTFT.tft);
	label_str.begin(myTFT.tft);
	date_marker_str.begin(myTFT.tft);
	day_len_marker_str.begin(myTFT.tft);

	// S->show_power_info=false;
	// S->show_mw_icon=false;
	// S->show_icons=false;
}