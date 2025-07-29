/*
* EoT: how many minutes fast or slow the Sun is compared to our clocks and watches.
* A negative number means the Sun is running slow; a positive number means it is running fast
* Values for: 0 deg lat, 0 deg long .
*/

#ifndef SCREEN_CLASS_H
	#include "ScreenClass.h"
#endif

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

// for scr_EoT()
#define min_EoT -854
#define max_EoT 990
const int EoT_vals[] = {-200, -228, -256, -283, -311, -337, -364, -389, -414, -439, -463, -487, -510, -532, -554, -575, -595, -615, -634, -652, -670, -687, -703, -718, -732, -746, -759, -771, -782, -793, -802, -811, -819, -826, -832, -838, -842, -846, -849, -852, -853, -854, -854, -853, -851, -849, -846, -842, -837, -832, -826, -819, -812, -804, -796, -787, -777, -767, -756, -745, -733, -721, -708, -694, -681, -667, -652, -637, -622, -607, -591, -574, -558, -541, -524, -507, -490, -472, -455, -437, -419, -401, -383, -365, -347, -329, -311, -293, -275, -257, -239, -221, -204, -186, -169, -152, -135, -118, -102, -85, -69, -54, -38, -23, -9, 6, 20, 33, 47, 60, 72, 84, 95, 107, 117, 127, 137, 146, 155, 163, 170, -29, -11, 177, 184, 190, 195, 200, 204, 208, 211, 214, 216, 217, 218, 219, 218, 218, 216, 214, 212, 209, 205, 201, 196, 191, 185, 179, 173, 166, 158, 150, 142, 133, 123, 114, 104, 93, 83, 72, 60, 49, 37, 25, 13, 0, -12, -25, -38, -51, -64, -77, -90, -103, -116, -129, -142, -155, -167, -180, -192, -205, -217, -228, -240, -251, -262, -273, -283, -293, -303, -312, -321, -329, -337, -344, -351, -358, -364, -369, -374, -379, -383, -386, -389, -391, -392, -393, -394, -394, -393, -391, -389, -387, -383, -380, -375, -370, -365, -358, -351, -344, -336, -327, -318, -308, -298, -287, -276, -264, -252, -239, -225, -211, -197, -182, -167, -151, -135, -118, -101, -84, -66, -48, -193, 8, 28, 47, 67, 87, 108, 128, 149, 170, 191, 212, 233, 254, 275, 297, 318, 340, 361, 383, 404, 425, 446, 467, 488, 509, 530, 550, 570, 590, 610, 630, 649, 668, 686, 704, 722, 739, 756, 773, 789, 804, 819, 834, 848, 861, 874, 887, 898, 909, 920, 930, 939, 947, 955, 962, 968, 973, 978, 982, 985, 987, 989, 990, 989, 988, 987, 984, 980, 976, 971, 965, 958, 950, 941, 932, 921, 910, 898, 885, 872, 857, 842, 826, 809, 791, 772, 753, 733, 713, 691, 669, 647, 624, 600, 575, 551, 525, 499, 473, 446, 419, 391, 363, 335, 306, 277, 248, 219, 189, 160, 130, 100, 71, 41, 11, -19, -48, -78, -107, -136, -165};
#define NOV_2 31+29+31+30+31+30+31+31+30+31+2 // Max EoT val day# 307
#define FEB_12 31+12 // Min EoT val day# 43

#define _EOT_TITLE_ {\
	Shivam_TXT title_str = Shivam_TXT(INFO_COL, 95,      FreeMonoBold12pt7b, 1, TERTIARY_TXT_COLOR,    BG_COLOR);\
	title_str.begin(myTFT.tft);\
	title_str.print_tft_no_prev_bg("EQUATION OF TIME");\
}
// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 46160)
const int epd_bitmap_allArray_LEN = 6;
const unsigned char* epd_bitmap_allArray[epd_bitmap_allArray_LEN] = {
	epd_bitmap_EoT_Curve,
	epd_bitmap_EoT_may_july,
	epd_bitmap_EoT_min_max,
	epd_bitmap_EoT_zero_line,
	epd_bitmap_EoT_zero_vals,
	epd_bitmap_EoT_times
};
// -----------------


void scr_EoT(time_t TimeStamp){
/*EoT: how many minutes fast or slow the Sun is compared to our clocks and watches.
A negative number means the Sun is running slow; a positive number means it is running fast
Values for: 0 deg lat, 0 deg long .*/

	myTFT.clear_screen(BG_COLOR);
	time_t localTime = convert_to_local_time(TimeStamp);

	_EOT_TITLE_

	myTFT.tft.drawBitmap(EOT_BMP_START_X, EOT_BMP_START_Y, epd_bitmap_EoT_Curve,     EOT_BMP_W, EOT_BMP_H, DARKGREEN);
	myTFT.tft.drawBitmap(EOT_BMP_START_X, EOT_BMP_START_Y, epd_bitmap_EoT_zero_line, EOT_BMP_W, EOT_BMP_H, LIGHTGREY);
	myTFT.tft.drawBitmap(EOT_BMP_START_X, EOT_BMP_START_Y, epd_bitmap_EoT_zero_vals, EOT_BMP_W, EOT_BMP_H, LIGHTGREY);
	myTFT.tft.drawBitmap(EOT_BMP_START_X, EOT_BMP_START_Y, epd_bitmap_EoT_min_max,   EOT_BMP_W, EOT_BMP_H, CYAN);
	myTFT.tft.drawBitmap(EOT_BMP_START_X, EOT_BMP_START_Y, epd_bitmap_EoT_may_july,  EOT_BMP_W, EOT_BMP_H, ORANGE);
	myTFT.tft.drawBitmap(EOT_BMP_START_X, EOT_BMP_START_Y, epd_bitmap_EoT_times,     EOT_BMP_W, EOT_BMP_H, DARKGREY);

	// Retrieve EoT value for today
	uint16_t curr_day_num=get_day_of_year(localTime);
	int curr_EoT_val=EoT_vals[curr_day_num-1];
	uint8_t m,s;
	uint16_t h;
	secondsToHMS(abs(curr_EoT_val),h,m,s);

	// Construct sentence
	String DL;
	if (s==0){
		DL=String(m)+" minute";
		if (m>1)
			DL+="s";
	}
	else if (m==0)
		DL=String(s)+" seconds";
	else
	  DL=String(m)+"min "+String(s)+"s";

	SCR_DAYLIGHT_L2.print_tft_middle("Sundial is "+String(DL)+String((curr_EoT_val>0) ? " faster" : " slower"));

	// Calculate position for today
	int now_x_pos = custom_map(curr_day_num,1,NUM_DAYS_YEAR,EOT_BMP_START_X,EOT_BMP_START_X+EOT_BMP_W);
	int now_y_pos = (int) custom_map(curr_EoT_val,min_EoT,max_EoT,EOT_BMP_START_Y+EOT_BMP_H-16,EOT_BMP_START_Y+16);

	// Confirm values
	LOG_DEBUG("curr_day_num: "+String(curr_day_num));
	LOG_DEBUG("now_x_pos: "+String(now_x_pos));
	LOG_DEBUG("now_y_pos: "+String(now_y_pos));
	LOG_DEBUG("EoT: "+String(curr_EoT_val)+" s");
	LOG_DEBUG(" ");

	// Draw vertical line marker for today
	myTFT.tft.drawLine(now_x_pos, now_y_pos-50, now_x_pos, now_y_pos+50, LIGHTGREY);
	Shivam_TXT today_str= Shivam_TXT(now_x_pos-20, now_y_pos+40, FreeMonoBold9pt7b, 1, TXT_COLOR, BG_COLOR);
	today_str.begin(myTFT.tft);
	int mm=convert_to_tmelements(localTime).Month;

	if (curr_day_num>346)
		today_str.print_tft_ralign(get_month_name(mm)+" "+String(get_day_of_month(localTime)));
	else
		if (curr_day_num<15)
			today_str.set_x_pos(1);
		today_str.print_tft_no_prev_bg(get_month_name(mm)+" "+String(get_day_of_month(localTime)));

	_SMALL_SUN_(now_x_pos, now_y_pos, SUN_MARKER_COLOR);
}

void scr_EoT_per_minute(uint TimeStamp){
		scr_EoT(TimeStamp);
}

void scr_EoT_per_hour(uint TimeStamp){
	return;
}
void scr_EoT_on_enter(uint TimeStamp){
	scr_EoT(TimeStamp);
}

void scr_EoT_initialize(Screen* S){
	S->set_func_per_second(do_nothing);
	S->set_func_per_minute(scr_EoT_per_minute);
	S->set_func_per_hour(do_nothing);
	S->set_func_on_enter(scr_EoT_on_enter);
	S->set_func_on_exit(do_nothing);
	S->set_func_on_touch(do_nothing);

	// S->show_power_info=false;
	// S->show_mw_icon=false;
	// S->show_icons=false;
}