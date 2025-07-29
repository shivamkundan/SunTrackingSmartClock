#ifndef Shivam_PicoW_TFT_H
	#include <Shivam_PicoW_TFT.h>
#endif

#ifndef COLORS_H
	#include "../colors.h"
#endif

#ifndef SCREEN_CLASS_H
	#include "ScreenClass.h"
#endif

#ifndef BITMAPS_H
    #include "../Bitmaps/bitmaps.h"
#endif

#ifndef TIME_VALS_H
	#include "../DateTime/time_vals.h"
#endif

#ifndef GLOBALS_H
    #include "../globals.h"
#endif

#ifndef _SUN_BITMAPS_H_
	#include "../Bitmaps/sun_bitmaps.h"
#endif

#include "../Bitmaps/world_map_bitmaps_exact.h"

#ifndef TIME_FUNCS_H
	#include "../DateTime/time_funcs.h"
#endif

// https://academo.org/demos/day-night-terminator/

// MAP
#define WORLD_MAP_COLOR      LIGHTBLACK
#define PRIME_MERIDIAN_COLOR ORANGE
#define SUN_COLOR YELLOW

// // alaska edge coords: 52.4282519890161, -171.19179995773774
// // nz edge coords: -49.64, 176.305
// // Argentina drake passage: -55.987, -69.101
// // Greenland arctic coast: 83.69, -34.92
// // Mumbai: 18.987, 72.7599
// // Sydney -33.978, 151.121
#define MAP_LBOUND -178.59
#define MAP_RBOUND 176.306
#define MAP_TOP_BOUND 83.693
#define MAP_BOTTOM_BOUND -55.987

#define MIN_LON -180
#define MAX_LON 180

#define DEG_HH 15  // Earth rotates 15 deg each hour
#define DEG_MM 0.25 // Earth rotates .25 deg each minute


#define TDIFF_IST 19800 //Indian standard time (UTC+5:30)

#define HD NUM_SECS_IN_DAY/2 // "Half Day"
// #define _ALL_TZs_ TS+HD;tz>TS+(-1*HD);tz-=NUM_SECS_IN_HOUR


#define CHI_TZ_NAME_POS_X 130
#define CHI_TZ_NAME_POS_Y 150-10
#define    CHI_TIME_POS_X 110+20
#define    CHI_TIME_POS_Y 170-10

#define CHI_MARKER_POS 120, 145-10
// ------------------------------------------------------------------------------------------------------------
#define _DRAW_BMP_ myTFT.tft.drawBitmap
#define _TM_ convert_to_tmelements
#define _CIRC_ myTFT.tft.fillCircle
#define _P_ print_tft
#define _P_NO_BG_ print_tft_no_prev_bg
#define _GET_T_ get_readable_time
// ------------------------------------------------------------------------------------------------------------
#define _SUN_(XPOS,COLOR){_DRAW_BMP_(XPOS-20, SCREEN_H/2, sun_medium_bmp, SUN_MID_W, SUN_MID_H, COLOR);}
#define _ERASE_SUN_  _SUN_(prev_sun_x,BG_COLOR)
#define _DRAW_SUN_   _SUN_(sun_x,SUN_COLOR)
// ------------------------------------------------------------------------------------------------------------
#define _DRAW_MAP_ 6+tz_xpos[i], tz_ypos[i]-10, WorldMap[i], tz_widths[i], tz_heights[i]

#define _TZ_(X,Y,STR) {\
	tZoneStr.set_pos(X,Y);\
	tZoneStr.print_tft_no_prev_bg(STR);\
}

#define _SHOW_TZ_NAMES_ {\
	_TZ_(CHI_TZ_NAME_POS_X, CHI_TZ_NAME_POS_Y, (DST? "CDT":"CST"))\
	_TZ_(SCREEN_W/2 -15 ,120-10,(DST? "BST" : "GMT"));\
	_TZ_(340,170-10,"IST");\
}

#define _SHOW_MARKERS_ {\
	_CIRC_(CHI_MARKER_POS, 4, YELLOW);\
	_CIRC_(SCREEN_W/2 - 23, 133-10, 3, ORANGE);\
	_CIRC_(340, 190-10, 3, YELLOW);\
}

#define _SHOW_TIMES_(T) {\
	_SHOW_TZ_NAMES_; _SHOW_MARKERS_;\
	TXT1._P_(_GET_T_(convert_to_local_time(T)));\
	TXT2._P_(_GET_T_((DST? T+3600: T)));\
	TXT3._P_(_GET_T_(T+TDIFF_IST));\
}

#define _SHOW_TIMES_NO_BG_(T) {\
	_SHOW_TZ_NAMES_; _SHOW_MARKERS_;\
	TXT1._P_NO_BG_(_GET_T_(convert_to_local_time(T)));\
	TXT2._P_NO_BG_(_GET_T_((DST? T+3600: T)));\
	TXT3._P_NO_BG_(_GET_T_(T+TDIFF_IST));\
}

// ------------------------------------------------------------------------------------------------------------

#define _DRAW_PM_ {\
	float greenwich_lon= custom_map (0,MAP_LBOUND,MAP_RBOUND,1,SCREEN_W)-23;\
	draw_dotted_vline(myTFT.tft,3, 6, WORLD_MAP_y_POS, SCREEN_H, (int)greenwich_lon, PRIME_MERIDIAN_COLOR);\
}

#define _DRAW_EQUATOR_ {\
	float equator_lat= custom_map (0,MAP_TOP_BOUND,MAP_BOTTOM_BOUND,WORLD_MAP_y_POS,320)+23;\
	draw_dotted_hline(myTFT.tft, 5, 10, 1, SCREEN_W, equator_lat, DARKCYAN);\
}

// ------------------------------------------------------------------------------------------------------------
#define _T_(X,Y){ Shivam_TXT(X, Y, MINI_TXT_FONT, 1, MINI_TXT_COLOR, BG_COLOR) }

// =========================================================================================
// Color gradient
const int shades[] = {RED_L11, RED_L10, RED_L9, RED_L8, RED_L7,RED_L6, RED_L5, RED_L4,RED_L3, RED_L2, RED_L1,
								  LIGHTBLACK,RED_L1, RED_L2, RED_L3, RED_L4, RED_L5, RED_L6, RED_L7 ,RED_L8, RED_L9, RED_L10, RED_L11,
								  RED_L10,RED_L9,RED_L8,RED_L7,RED_L6,RED_L5,RED_L4,RED_L3,RED_L2,RED_L1,LIGHTBLACK};

int prev_sun_x=0; // for erasing previous sun

// Declare text objects
Shivam_TXT tZoneStr = Shivam_TXT(110,150-10, Font4x5Fixed, 2, CYAN, BG_COLOR);
Shivam_TXT curr_lon_txt= Shivam_TXT(20,SCREEN_H-3, FreeMonoBold9pt7b, 1, DARKGREY, BG_COLOR);
Shivam_TXT TXT1 = _T_(CHI_TIME_POS_X, CHI_TIME_POS_Y);
Shivam_TXT TXT2 = _T_(SCREEN_W/2 -15 ,102-10);
Shivam_TXT TXT3 = _T_(340,152-10);

// =========================================================================================

void find_sun_pos(uint TS)
/* Figure out where the sun is right now (longitude) */
{

	uint start_t=millis();

	int HA=0; //hour angle
	float Lon=HA;
	int sun_x=0;

	uint sun_index=numTZs-1;
	uint tz;
	// Start from left-most side of array. Timestamp is for utc -> left-most TZ is behind half a day (12hrs)
	for (tz=TS+HD; tz>TS+(-1*HD); tz-=NUM_SECS_IN_HOUR){
		uint HH=_TM_(tz).Hour;
		uint MM=_TM_(tz).Minute;
		// LOG_DEBUG("HH:"+String(HH)+"| tz-utcTS:"+String((TS>tz? TS-tz : tz-TS)/3600));

		if (HH==12) break;
		sun_index-=1;
	}

	int32_t diff=tz-TS; // needs to be signed int
	uint HH=_TM_(tz).Hour;
	uint MM=_TM_(tz).Minute;
	HA=(diff/NUM_SECS_IN_HOUR)*DEG_HH;
	float MA=MM*DEG_MM;
	Lon=( HA>0 && HA<180 ? HA+MA : HA-MA);   // determine east or west hemisphere

	sun_x=custom_map(Lon,MIN_LON,MAX_LON,1,SCREEN_W); // map longitude to pixel xpos

	_ERASE_SUN_;
	_DRAW_SUN_;

	_SHOW_TIMES_(TS);

	curr_lon_txt.print_tft("curr: "+String(Lon)+" deg");

	// Draw each timezone with appropriate colors
	for (int i=sun_index; i<numTZs; i++)
		_DRAW_BMP_(_DRAW_MAP_, shades[i-sun_index]);

	for (int i=sun_index-1; i>=0; i--)
		_DRAW_BMP_(_DRAW_MAP_, shades[sun_index-1-i]);

	_SHOW_TIMES_NO_BG_(TS);


	LOG_DEBUG((String(millis()-start_t)+" ms"));

	// Show sun
	prev_sun_x=sun_x;
	_DRAW_SUN_;

	LOG_DEBUG(String(millis()-start_t)+" ms");
}

void update_map()
/* day-night-terminator */
{
  // Prime meridian
  _DRAW_PM_;

  // Draw equator
  _DRAW_EQUATOR_;
}

// =========================================================================================
void scr_wclk_per_minute(uint TimeStamp){
		find_sun_pos(TimeStamp);
		update_map();
}


void scr_wclk_on_enter(uint TimeStamp){
	myTFT.clear_screen(BG_COLOR);
	scr_wclk_per_minute(TimeStamp);
}

void scr_wclk_initialize(Screen* S){
	S->set_func_per_second(do_nothing);
	S->set_func_per_minute(scr_wclk_per_minute);
	S->set_func_per_hour(do_nothing);
	S->set_func_on_enter(scr_wclk_on_enter);
	S->set_func_on_exit(do_nothing);
	S->set_func_on_touch(do_nothing);

	S->show_power_info=false;
	S->show_backlight_info=false;
	S->show_mw_icon=false;
	// S->show_icons=false;
	curr_lon_txt.begin(myTFT.tft);
	TXT1.begin(myTFT.tft);
	TXT2.begin(myTFT.tft);
	TXT3.begin(myTFT.tft);
	tZoneStr.begin(myTFT.tft);
}