#ifndef _SUN_BITMAPS_H_
	#include "../Bitmaps/sun_bitmaps.h"
#endif

// ---------------------------------------------------------------------------------------------------------------------- //
// --------------------------------------------- for draw_orbital_diagram() --------------------------------------------- //
#define ORBIT_W 250
#define ORBIT_H 150

#define Y_PAD 2
#define ELLIPSE_START_X 110
#define ELLIPSE_START_Y 97
#define X_PAD 95

// Co-ordinates for markers:
// MAR19: 211, 246
// JUN20: 353, 196
// SEP22: 260, 99
// DEC21: 121, 141
#define LOE 211, 246, 260, 99	// line of equinox (x1,y1,x2,y2)
#define LOS 121, 141, 353, 196  // line of solstice (x1,y1,x2,y2)

#define MARKER_RADIUS 3
#define EARTH_RADIUS 14
#define ELLIPSE_LEN 366

uint ELLIPSE_X_VALS[]={
	15, 15, 15, 15, 15, 16, 16, 16, 16, 17, 17, 18, 18, 20, 20, 21, 22, 23, 24, 25, 26, 29,
	29, 31, 32, 34, 35, 37, 38, 40, 41, 43, 44, 46, 47, 49, 50, 52, 53, 55, 56, 58, 59, 61,
	62, 64, 65, 67, 68, 71, 73, 74, 76, 77, 79, 80, 82, 83, 85, 86, 88, 89, 91, 92, 94, 95,
	97, 100, 101, 103, 104, 106, 107, 109, 110, 112, 113, 115, 116, 118, 119, 121, 122, 124,
	125, 127, 128, 130, 131, 133, 134, 136, 137, 140, 140, 143, 144, 146, 147, 149, 150, 152,
	153, 155, 156, 158, 159, 161, 162, 164, 165, 167, 168, 170, 171, 173, 174, 176, 177, 179,
	180, 183, 185, 186, 188, 189, 191, 192, 194, 195, 197, 198, 200, 201, 203, 204, 206, 207,
	209, 212, 213, 215, 216, 218, 219, 221, 222, 224, 225, 227, 228, 230, 231, 233, 234, 236,
	237, 239, 240, 242, 243, 245, 246, 248, 249, 251, 251, 254, 255, 256, 257, 258, 259, 260,
	260, 262, 262, 263, 263, 264, 264, 264, 264, 265, 265, 265, 265, 265, 265, 265, 265, 265,
	265, 264, 264, 264, 264, 263, 263, 262, 262, 260, 260, 259, 258, 257, 256, 255, 254, 251,
	251, 249, 248, 246, 245, 243, 242, 240, 239, 237, 236, 234, 233, 231, 230, 228, 227, 225,
	224, 222, 221, 219, 218, 216, 215, 213, 212, 209, 207, 206, 204, 203, 201, 200, 198, 197,
	195, 194, 192, 191, 189, 188, 186, 185, 183, 180, 179, 177, 176, 174, 173, 171, 170, 168,
	167, 165, 164, 162, 161, 159, 158, 156, 155, 153, 152, 150, 149, 147, 146, 144, 143, 140,
	140, 137, 136, 134, 133, 131, 130, 128, 127, 125, 124, 122, 121, 119, 118, 116, 115, 113,
	112, 110, 109, 107, 106, 104, 103, 101, 100, 97, 95, 94, 92, 91, 89, 88, 86, 85, 83, 82,
	80, 79, 77, 76, 74, 73, 71, 68, 67, 65, 64, 62, 61, 59, 58, 56, 55, 53, 52, 50, 49, 47, 46,
	44, 43, 41, 40, 38, 37, 35, 34, 32, 31, 29, 29, 26, 25, 24, 23, 22, 21, 20, 20, 18, 18, 17,
	17, 16, 16, 16, 16, 15, 15, 15, 15, 15
};

uint ELLIPSE_Y_VALS[]={
	171, 172, 174, 175, 176, 177, 178, 180, 181, 182, 183, 185, 186, 190, 192, 193, 194, 197, 198,
	200, 201, 204, 205, 207, 208, 210, 211, 212, 213, 215, 216, 217, 218, 219, 220, 221, 222, 223,
	224, 225, 226, 227, 227, 228, 229, 230, 230, 231, 231, 233, 233, 234, 234, 235, 235, 236, 236,
	237, 237, 238, 238, 238, 239, 239, 240, 240, 240, 241, 241, 242, 242, 242, 242, 243, 243, 243,
	243, 243, 244, 244, 244, 244, 244, 244, 244, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245,
	245, 245, 245, 245, 245, 245, 245, 245, 244, 244, 244, 244, 244, 244, 244, 243, 243, 243, 243,
	243, 242, 242, 242, 242, 241, 241, 240, 240, 240, 239, 239, 238, 238, 238, 237, 237, 236, 236,
	235, 235, 234, 234, 233, 233, 231, 231, 230, 230, 229, 228, 227, 227, 226, 225, 224, 223, 222,
	221, 220, 219, 218, 217, 216, 215, 213, 212, 211, 210, 208, 207, 205, 204, 201, 200, 198, 197,
	194, 193, 192, 190, 186, 185, 183, 182, 181, 180, 178, 177, 176, 175, 174, 172, 171, 169, 168,
	166, 165, 164, 163, 162, 160, 159, 158, 157, 155, 154, 150, 148, 147, 146, 143, 142, 140, 139,
	136, 135, 133, 132, 130, 129, 128, 127, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115,
	114, 113, 113, 112, 111, 110, 110, 109, 109, 107, 107, 106, 106, 105, 105, 104, 104, 103, 103,
	102, 102, 102, 101, 101, 100, 100, 100, 99, 99, 98, 98, 98, 98, 97, 97, 97, 97, 97, 96, 96, 96,
	96, 96, 96, 96, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 96, 96,
	96, 96, 96, 96, 96, 97, 97, 97, 97, 97, 98, 98, 98, 98, 99, 99, 100, 100, 100, 101, 101, 102, 102,
	102, 103, 103, 104, 104, 105, 105, 106, 106, 107, 107, 109, 109, 110, 110, 111, 112, 113, 113, 114,
	115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 127, 128, 129, 130, 132, 133, 135, 136, 139,
	140, 142, 143, 146, 147, 148, 150, 154, 155, 157, 158, 159, 160, 162, 163, 164, 165, 166, 168, 169
};

// ---------------------- Artwork ---------------------- //
#define _DRAW_ORBIT_ {\
	draw_ellipse(ELLIPSE_START_X-1, ELLIPSE_START_Y-1, ELLIPSE_START_X+ORBIT_W+1, ELLIPSE_START_Y+ORBIT_H+1, RED);\
	draw_ellipse(ELLIPSE_START_X  , ELLIPSE_START_Y  , ELLIPSE_START_X+ORBIT_W  , ELLIPSE_START_Y+ORBIT_H  , RED);\
	draw_ellipse(ELLIPSE_START_X+1, ELLIPSE_START_Y+1, ELLIPSE_START_X+ORBIT_W-1, ELLIPSE_START_Y+ORBIT_H-1, RED);\
}

#define _DRAW_ORBIT_LABELS_ {\
	Shivam_TXT mar19_str= Shivam_TXT(ELLIPSE_X_VALS [MAR_19-1]+X_PAD-20, ELLIPSE_Y_VALS [MAR_19-1]+Y_PAD+18, FreeMonoBold9pt7b, 1, MINI_TXT_COLOR, BG_COLOR);\
	mar19_str.begin(myTFT.tft);\
	mar19_str.print_tft_no_prev_bg("MAR 19");\
\
	Shivam_TXT jun20_str= Shivam_TXT(ELLIPSE_X_VALS [JUN_20-1]+X_PAD+7, ELLIPSE_Y_VALS [JUN_20-1]+Y_PAD+10, FreeMonoBold9pt7b, 1, MINI_TXT_COLOR, BG_COLOR);\
	jun20_str.begin(myTFT.tft);\
	jun20_str.print_tft_no_prev_bg("JUN 20");\
\
	Shivam_TXT sep22_str= Shivam_TXT(ELLIPSE_X_VALS [SEP_22-1]+X_PAD+10, ELLIPSE_Y_VALS [SEP_22-1]+Y_PAD-5, FreeMonoBold9pt7b, 1, MINI_TXT_COLOR, BG_COLOR);\
	sep22_str.begin(myTFT.tft);\
	sep22_str.print_tft_no_prev_bg("SEP 22");\
\
	Shivam_TXT dec21_str= Shivam_TXT(ELLIPSE_X_VALS [DEC_21-1]+X_PAD-65, ELLIPSE_Y_VALS [DEC_21-1]+Y_PAD-8, FreeMonoBold9pt7b, 1, MINI_TXT_COLOR, BG_COLOR);\
	dec21_str.begin(myTFT.tft);\
	dec21_str.print_tft_no_prev_bg("DEC 21");\
\
	Shivam_TXT jan2_str= Shivam_TXT(ELLIPSE_X_VALS [JAN_2-1]+X_PAD-65, ELLIPSE_Y_VALS [JAN_2-1]+Y_PAD+5, FreeMonoBold9pt7b, 1, TXT_COLOR, BG_COLOR);\
	jan2_str.begin(myTFT.tft);\
	jan2_str.print_tft_no_prev_bg("JAN 2");\
\
\
	Shivam_TXT jul5_str= Shivam_TXT(ELLIPSE_X_VALS [JUL_5-1]+X_PAD+8, ELLIPSE_Y_VALS [JUL_5-1]+Y_PAD, FreeMonoBold9pt7b, 1, TXT_COLOR, BG_COLOR);\
	jul5_str.begin(myTFT.tft);\
	jul5_str.print_tft_no_prev_bg("JUL 5");\
}

#define _DRAW_AXIS_ {\
	myTFT.tft.drawLine(pos_x_start-2, pos_y_start, pos_x_end-2, pos_y_end, WHITE);\
	myTFT.tft.drawLine(pos_x_start-1, pos_y_start, pos_x_end-1, pos_y_end, RED);\
	myTFT.tft.drawLine(pos_x_start,   pos_y_start, pos_x_end,   pos_y_end, RED);\
	myTFT.tft.drawLine(pos_x_start+1, pos_y_start, pos_x_end+1, pos_y_end, RED);\
	myTFT.tft.drawLine(pos_x_start+2, pos_y_start, pos_x_end+2, pos_y_end, WHITE);\
}

#define _DRAW_NORTH_MARKER_ {\
	north_marker.set_y_pos(pos_y_start-10);\
	north_marker.set_x_pos(pos_x_start);\
	north_marker.print_tft_no_prev_bg("N");\
}

#define _DRAW_EQUATOR_SMALL_ {\
	pos_x_start = curr_earth_x-EARTH_RADIUS;\
	pos_x_end = curr_earth_x+EARTH_RADIUS;\
	pos_y_start = curr_earth_y+4;\
	pos_y_end = curr_earth_y-4;\
	myTFT.tft.drawLine(pos_x_start, pos_y_start, pos_x_end, pos_y_end, RED);\
}

#define _DRAW_LARGE_SUN_ myTFT.tft.drawBitmap(ELLIPSE_START_X+(int)ORBIT_W/2-(int)(0.6*SUN_LARGE_W),ELLIPSE_START_Y+(int)ORBIT_H/2 - (int)SUN_LARGE_H/2,sun_large_bmp, SUN_LARGE_W, SUN_LARGE_H, YELLOW);

void draw_ellipse(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color)
/* Draw ellipse for earth orbit. */
{
  long a = abs(x1 - x0);
  long b = abs(y1 - y0);

  long bb1 = b & 1; /* values of diameter */

  long dx = 4 * (1 - a) * b * b, dy = 4 * (bb1 + 1) * a * a; /* error increment */
  long err = dx + dy + bb1 * a * a, e2; /* error of 1.step */

  if (x0 > x1) { x0 = x1; x1 += a; } /* if called with swapped points */
  if (y0 > y1) y0 = y1; /* .. exchange them */

  y0 += (b + 1) / 2; /* starting pixel */
  y1 = y0 - bb1;
  a *= 8 * a;
  bb1 = 8 * b * b;

  do {
    myTFT.tft.drawPixel(x1, y0, color); /*   I. Quadrant */
    myTFT.tft.drawPixel(x0, y0, color); /*  II. Quadrant */
    myTFT.tft.drawPixel(x0, y1, color); /* III. Quadrant */
    myTFT.tft.drawPixel(x1, y1, color); /*  IV. Quadrant */

    e2 = 2 * err;
    if (e2 >= dx) { x0++; x1--; err += dx += bb1; } /* x step */
    if (e2 <= dy) { y0++; y1--; err += dy += a; }  /* y step */
  } while (x0 <= x1);

  while (y0 - y1 < b) {  /* too early stop of flat ellipses a=1 */
    myTFT.tft.drawPixel(x0 - 1, ++y0, color); /* -> complete tip of ellipse */
    myTFT.tft.drawPixel(x0 - 1, --y1, color);
  }
}

// ======================================================================================================================== //
// ======================================================================================================================== //

void DRW(int day_num){
	day_num-=1;
	int xpos =   ELLIPSE_X_VALS [day_num-1]+X_PAD;
	int ystart = ELLIPSE_Y_VALS [day_num-1]+Y_PAD - 5;
	int yend =   ELLIPSE_Y_VALS [day_num-1]+Y_PAD + 5;

	myTFT.tft.drawLine(xpos,   ystart, xpos,   yend, DARKGREY);
}


#ifndef SCREEN_CLASS_H
	#include "ScreenClass.h"
#endif

#define SUN_DIST_COL 5
Shivam_TXT SUN_DIST_TITLE = Shivam_TXT(  0, 280,    FreeMonoBold9pt7b,  1, TERTIARY_TXT_COLOR, BG_COLOR);
Shivam_TXT    SUN_DIST_L1 = Shivam_TXT(  0, 310,    FreeMonoBold14pt7b, 1, TXT_COLOR,          BG_COLOR);
Shivam_TXT    SUN_DIST_L2 = Shivam_TXT(300, 310,    FreeMonoBold14pt7b, 1, TXT_COLOR, 		   BG_COLOR);
Shivam_TXT   north_marker = Shivam_TXT(300, 310,    FreeMonoBold9pt7b,  1, DARKGREY, 		   BG_COLOR);

void draw_orbital_diagram(time_t localTime)
/* Draw elliptical orbit, sun, earth */
{
	// Simplified quadrant-day mapping
	// Day   1 to  94: bottom left arc -> 94 days
	// Day  95 to 189: bottom right -> 95 days
	// Dat 190 to 278: top right -> 89 days
	// Day 279 to 366: top left -> 88 days
	// 94+95+89+88 = 366 days

	// Draw orbit ellipse with width of 3
	_DRAW_ORBIT_

	// ------------------------------------------------------------------------------------------------ //
	uint16_t curr_day_num=get_day_of_year(localTime);
	uint curr_earth_x = ELLIPSE_X_VALS [curr_day_num-1]+X_PAD;
	uint curr_earth_y = ELLIPSE_Y_VALS [curr_day_num-1]+Y_PAD;
	// LOG_DEBUG("Day#= "+String(curr_day_num)+" / earth x,y ="+String(curr_earth_x)+", "+String(curr_earth_y));

	// ------ Markers for apsides ------ //
	myTFT.tft.fillCircle(ELLIPSE_X_VALS [JAN_2-1]+X_PAD, ELLIPSE_Y_VALS [JAN_2-1]+Y_PAD, MARKER_RADIUS, TXT_COLOR); // Jan 2 -> Perihelion
	myTFT.tft.fillCircle(ELLIPSE_X_VALS [JUL_5-1]+X_PAD, ELLIPSE_Y_VALS [JUL_5-1]+Y_PAD, MARKER_RADIUS, TXT_COLOR); // Jul 5 -> Aphelion

	// ------  Draw monthly markers ------  //
	DRW(FEB_1); DRW(MAR_1); DRW(APR_1); DRW(MAY_1); DRW(JUN_1); /* DRW(JUL_1);*/ DRW(AUG_1);DRW(SEP_1);DRW(OCT_1);DRW(NOV_1);DRW(DEC_1);

	// ------ Draw markers ------ //
	for (uint D=0;D<NUM_REF_DAYS;D++){
		curr_day_num=ref_days[D];
		myTFT.tft.fillCircle(ELLIPSE_X_VALS [curr_day_num-1]+X_PAD, ELLIPSE_Y_VALS [curr_day_num-1]+Y_PAD, MARKER_RADIUS, MINI_TXT_COLOR);
	}

	// ------ Draw solstice/equinox lines ------ //
	myTFT.tft.drawLine(LOE, DARKGREY);  // Line of equinox
	myTFT.tft.drawLine(LOS, DARKGREY); // Line of solstice

	// ------ Draw sun ------ //
	_DRAW_LARGE_SUN_

	// ------ Draw labels ------ //
	_DRAW_ORBIT_LABELS_

	// ------------------------------ Draw earth ------------------------------ //
	myTFT.tft.fillCircle(curr_earth_x, curr_earth_y, EARTH_RADIUS, CYAN);

	int pos_x_start = curr_earth_x-5;
	int pos_x_end = curr_earth_x+5;
	int pos_y_start = curr_earth_y-EARTH_RADIUS-6;
	int pos_y_end = curr_earth_y+EARTH_RADIUS+6;

	// Draw axis of tilt with width=5
	_DRAW_AXIS_

	// Draw north marker
	_DRAW_NORTH_MARKER_

	// Draw equator
	_DRAW_EQUATOR_SMALL_
	// ------------------------------------------------------------------------ //
}

void scr_earth_orbit_per_minute(uint TimeStamp){

	int localTime=convert_to_local_time(TimeStamp);

	myTFT.clear_screen(BG_COLOR);
	display_large_HH_MM(localTime);
	display_day_date(localTime);

	SUN_DIST_TITLE.print_tft("DIST TO SUN");
	SUN_DIST_TITLE.print_tft_ralign("DIFF");

	// Retrieve distance, calc diff
	int day_num=get_day_of_year(localTime);
	float sun_dist_today     = SUN_DIST_ARR[day_num]*1000000;
	float sun_dist_yesterday     = SUN_DIST_ARR[day_num-1]*1000000;
	float diff = sun_dist_today - sun_dist_yesterday; // Kilo thousand miles

	// Display distance values
	String out=printfcomma((int)abs(diff))+" miles";
	SUN_DIST_L2.print_tft_ralign((diff < 0 ? "-" :"+")+out);
	SUN_DIST_L1.print_tft(printfcomma((int)sun_dist_today)+" miles");

	// Draw main diagram
	draw_orbital_diagram(localTime);
}

void scr_earth_orbit_initialize(Screen* S){
	S->set_func_per_second(do_nothing);
	S->set_func_per_minute(scr_earth_orbit_per_minute);
	S->set_func_per_hour(do_nothing);
	S->set_func_on_enter(scr_earth_orbit_per_minute);
	S->set_func_on_exit(do_nothing);
	S->set_func_on_touch(do_nothing);

	SUN_DIST_TITLE.begin(myTFT.tft);
	SUN_DIST_L1.begin(myTFT.tft);
	SUN_DIST_L2.begin(myTFT.tft);
	north_marker.begin(myTFT.tft);
	S->show_power_info=false;
	S->show_backlight_info=false;
	S->show_scr_num=false;
	S->show_mw_icon=false;
	S->show_icons=false;
}