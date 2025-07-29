#ifndef COMMON_H
	#define COMMON_H
#endif

// imports
	#ifndef SCREEN_CLASS_H
	    #include "ScreenClass.h"
	#endif

	#ifndef GRID_FUNCS_H
		#include "grid_funcs.h"
	#endif

	#ifndef Shivam_PicoW_TFT_H
		#include <Shivam_PicoW_TFT.h>
	#endif

	#ifndef SHIVAM_TXT_H
		#include <Shivam_TXT.h>
	#endif

	#ifndef BITMAPS_H
		#include "../Bitmaps/bitmaps.h"
	#endif

	#ifndef TIME_FUNCS_H
		#include "../DateTime/time_funcs.h"
	#endif

	#ifndef HARDWARE_H
	    #include "../Hardware/hardware.h"
	#endif

	#ifndef MY_FONTS_H
	    #include "../MyFonts/my_fonts.h"
	#endif

	#ifndef COLORS_H
	    #include "../colors.h"
	#endif

	#ifndef GLOBALS_H
		#include "../globals.h"
	#endif

	#ifndef STRING_DEFS_H
	    #include "../string_defs.h"
	#endif

	#ifndef UTILS_H
	  #include "../utils.h"
	#endif

uint8_t NUM_SCREENS;

#define NUM_INFO_SCREENS 7
#define NUM_REG_SCREENS 15 + NUM_INFO_SCREENS//NUM_SCREENS2-NUM_MENU_SCREENS
#define NUM_MENU_SCREENS 5

#define NUM_SCREENS2 NUM_REG_SCREENS+NUM_MENU_SCREENS//27

Screen* scr_list[NUM_SCREENS2];
String scr_list_names[NUM_REG_SCREENS]; // Holds the names for each screen

#define SCREEN_MENU 22//NUM_SCREENS2-NUM_MENU_SCREENS
#define SCREEN_MENU_SCREENS 23 //NUM_SCREENS2-NUM_MENU_SCREENS + 2
#define SCREEN_MENU_SETTINGS 24//NUM_SCREENS2-NUM_MENU_SCREENS + 1
#define SCREEN_BACKLIGHT 25 //NUM_SCREENS2 -NUM_MENU_SCREENS +2
#define SCREEN_MENU_INFO 26 //NUM_SCREENS2 -NUM_MENU_SCREENS +2

// Program assumes batt/power screen will be last reg screen
#define SCREEN_TEMP_HUMID  15
#define SCREEN_BATT_POWER NUM_REG_SCREENS - 2

#define SCREEN_GREEN 0
#define SCREEN_ERROR 21
// =============================================================================
// =============================================================================

// -------------------------------
#define _PRINT_TITLE_SMALL_(TITLE) {Shivam_TXT title = Shivam_TXT(5, 21, FreeMonoBold12pt7b, 1, RED, BG_COLOR);  title.begin(myTFT.tft); title.print_tft_middle(TITLE);}

#define _PRINT_TITLE_MEDIUM_(TITLE) {Shivam_TXT title = Shivam_TXT(5, 105, FreeMonoBold12pt7b, 1, TERTIARY_TXT_COLOR, BG_COLOR);  title.begin(myTFT.tft); title.print_tft(TITLE);}


// ---------- grphics related ---------- //
#define RADIAN_MULT 0.0174533
#define ANGLE_OFFSET -90*RADIAN_MULT  // I want to count angles from 0 deg at 12'o clock position
#define AZM_MULT 3 // since only 480 azm values but 1440 mins in day

// -------------------------- Diagrams -------------------------- //
// Diagram colors
#define SUN_MARKER_COLOR YELLOW
#define SUN_PATH_COLOR RED

#define ELEV_DIAG_HEIGHT 100
const int _yTop=15;
const int _yBottom=_yTop+ELEV_DIAG_HEIGHT;


int base_y_pos=65; // formerly zero_line_y_pos
const int vspace1=75, vspace2=75, vspace3=40;
const int L1_pos=base_y_pos+vspace1;
const int hrs_remain_yPos=L1_pos+vspace2;
const int mins_remaining_yPos=hrs_remain_yPos+vspace3;


// Draw visual indicator for exit
#define _DRAW_X_ {\
	Shivam_TXT       clb = Shivam_TXT(225,     300,  FreeSansBold15pt7b, 1, LIGHTGREY, BG_COLOR);\
	clb.begin(myTFT.tft);\
	clb.print_tft(" X ");\
}

// -------------------------------------------------------------------------------------------------------------
// --------------------------------------- Sun bitmaps  ------------------------------------------------------
#define _SMALL_SUN_(XP, YP, COLOR) {myTFT.tft.drawBitmap(XP-SUN_SMALL_W/2,  YP-SUN_SMALL_H/2,sun_small_bmp, SUN_SMALL_W, SUN_SMALL_H, COLOR);}

#define _MEDIUM_SUN_(XP, YP, COLOR) {myTFT.tft.drawBitmap(XP-SUN_MID_W/2,  YP-SUN_MID_H/2,sun_medium_bmp, SUN_MID_W, SUN_MID_H, COLOR);}

// -------------------------------------------------------------------------------------------------------------
// --------------------------------------- String objects ------------------------------------------------------

#define SCR_DAYLIGHT_COL 5
#define SCR_DAYLIGHT_START_ROW 265
Shivam_TXT    SCR_DAYLIGHT_L1 = Shivam_TXT(20, SCR_DAYLIGHT_START_ROW-30, FreeMonoBold9pt7b, 1, SECONDARY_TXT_COLOR, BG_COLOR);
Shivam_TXT    SCR_DAYLIGHT_L2 = Shivam_TXT(0, SCR_DAYLIGHT_START_ROW+30, FreeMonoBold14pt7b, 1, TXT_COLOR, BG_COLOR);
Shivam_TXT          label_str = Shivam_TXT(265, 1, Font4x5Fixed,      2, RED, BG_COLOR);
Shivam_TXT    date_marker_str = Shivam_TXT(0,0, FreeMonoBold9pt7b, 1, MINI_TXT_COLOR, BG_COLOR);
Shivam_TXT day_len_marker_str = Shivam_TXT(0,0, Font4x5Fixed, 2, DARKGREY, BG_COLOR);
// -------------------------------------------------------------------------------------------------------------

#define INFO_COL 5

#define _GET_POS_(IN) { (uint) custom_map(get_minute_of_day(convert_to_local_time(IN)),0,NUM_MINS_IN_DAY,0,SCREEN_W) }

// ---------------------------------------- //
String info_scr_list_names[NUM_INFO_SCREENS]; // Holds the names for each screen
uint8_t start_index=SCREEN_TEMP_HUMID;
uint8_t end_index=SCREEN_BATT_POWER;

void make_name_list(Screen* scr_list[NUM_REG_SCREENS])
/* Stores screen names as array of strings */
{
	LOG_TRACE("\nmake_name_list");
	for (uint8_t i=0;i<NUM_REG_SCREENS;i++){
		scr_list_names[i]=scr_list[i]->name;
		LOG_DEBUG(String(i)+": "+scr_list_names[i]);
	}
}

void make_name_list_info_screens(Screen* scr_list[NUM_REG_SCREENS], uint8_t num_screens)
/* Stores screen names as array of strings */
{
	for (uint8_t i=start_index;i<end_index+1;i++){
		info_scr_list_names[i-start_index]=scr_list[i]->name;
		LOG_DEBUG(info_scr_list_names[i-start_index]);
	}
}

// ------------------------------------------------------------------------------------------------------------------- //
int retrieve_time_from_index(time_t TimeStamp, uint16_t index)
/* Fetch data from array */
{
	int mm=convert_to_tmelements(convert_to_local_time(TimeStamp)).Month;
	int yy=convert_to_tmelements(convert_to_local_time(TimeStamp)).Year+UNIX_START_YEAR;
	int next = all_years[yy-BASE_YEAR][mm-1][index];
	return next;
}

// ------------------------------------------------------------------------------------------------------------------- //
void draw_time_marker(int inTime, int mm, int day_num, int minVal,int maxVal,int yBottom,int yTop, int color, int radius)
/* For x-y plots */
{
	uint16_t min_of_day=get_minute_of_day(convert_to_local_time(inTime));
	int xpos=(int) custom_map(min_of_day,0,NUM_MINS_IN_DAY-1,0,SCREEN_W-1);
	int ypos=(int) custom_map(ELEV_ARR[mm-1][day_num-1][xpos],minVal,maxVal,yBottom,yTop);
	myTFT.tft.fillCircle(xpos, ypos-1, radius, color);
}

// ------------------------------------------------------------------------------------------------------------------- //
uint16_t get_text_width(String in_text, GFXfont in_font){
    int16_t x1,y1;
    uint16_t w1,h1;
    myTFT.tft.setFont(&in_font);
    myTFT.tft.setTextSize(1);
    myTFT.tft.getTextBounds(in_text, 0, 0, &x1, &y1, &w1, &h1);
    return w1;
}

uint16_t get_text_height(String in_text, GFXfont in_font){
    int16_t x1,y1;
    uint16_t w1,h1;
    myTFT.tft.setFont(&in_font);
    myTFT.tft.setTextSize(1);
    myTFT.tft.getTextBounds(in_text, 0, 0, &x1, &y1, &w1, &h1);
    return h1;
}

// ------------------------------------------------------------------------------------------------------------------- //
#define __Y0 zero_line_y_pos+25 // for x-axis labels
#define _XTICK_LEN_ 12 	// size of xtick lines

void draw_x_labels(int zero_line_y_pos){
	Shivam_TXT xlabel = Shivam_TXT(0, __Y0, Font4x5Fixed, 2, DARKGREY, BG_COLOR);
	xlabel.begin(myTFT.tft);
	for (int i=0;i<NUM_HOURS_IN_DAY;i+=3){
		int xp=custom_map (i*60,1,NUM_MINS_IN_DAY-1,0,SCREEN_W);
		myTFT.tft.drawLine(xp,zero_line_y_pos,xp,zero_line_y_pos+_XTICK_LEN_,DARKGREY);
		xlabel.set_x_pos(xp);
		if (i==0)       xlabel.print_tft_no_prev_bg("12AM");
		else if (i==12) xlabel.print_tft_no_prev_bg("12PM");
		else if (i<12)  xlabel.print_tft_no_prev_bg(String (i));
		else			xlabel.print_tft_no_prev_bg(String (i-12));
	}
	myTFT.tft.drawLine(SCREEN_W-1,zero_line_y_pos,SCREEN_W-1,zero_line_y_pos+_XTICK_LEN_,DARKGREY);
	xlabel.print_tft_ralign2("12",SCREEN_W,false);
}

// ------------------------------------------------------------------------------------------------------------------- //
// ---------------------------------- For screen altitude & azm & alt/azm -------------------------------------------- //
float start_angle =1.5*3.1415, end_angle = 2*3.1415;
float step=0.05;
float find_closest_i(int in_angle)
/* Used for calculating x,y positions for given angle. */
{
	float closest_point=10000;
	float closest_i=100;

	for (float i = start_angle; i < end_angle; i = i + step)
	{
		float i_deg=(i/RADIAN_MULT)-ANGLE_OFFSET;
		float i_map = custom_map(i_deg,270,360,90,0);  // Used for remapping angles

		if (abs(in_angle-i_map)<closest_point){
			closest_point=abs(in_angle-i_map);
			closest_i=i;
		}
	}
	return closest_i;
}

// ---------------------------------------------------------------------------------------------------- //
// ---------------------------------- For multiple screens -------------------------------------------- //
int draw_elevation_diagram(int day_num,int mm,int yy,int today_minute, int yTop, int yBottom)
/* Draws elevation diagram for the given day */
{
 	// Retrieve min and max elevation
 	int maxVal=MAX_ELEV_ARRAY[mm-1][day_num-1];
 	int minVal=MIN_ELEV_ARRAY[mm-1][day_num-1];


 	// Lim: before Jan 21 / after nov 21
 	// This is the line for horizon (i.e, 0 deg elevation)
 	int zero_line_y_pos=(int) custom_map(0,minVal,maxVal,yBottom,yTop);

	// Draw actual curve with thickness=3
	for (uint x_pos=0;x_pos<SCREEN_W;x_pos++){
		int y_pos= (int) custom_map(ELEV_ARR[mm-1][day_num-1][x_pos],minVal,maxVal,yBottom,yTop);
		myTFT.tft.drawPixel(x_pos, y_pos-1, SUN_PATH_COLOR);
		myTFT.tft.drawPixel(x_pos, y_pos,   SUN_PATH_COLOR);
		myTFT.tft.drawPixel(x_pos, y_pos+1, SUN_PATH_COLOR);
		myTFT.tft.drawPixel(x_pos, zero_line_y_pos, HORIZON_COLOR);
	}

	// Draw sun marker showing current elevation
	int now_x_pos=custom_map (today_minute,0,NUM_MINS_IN_DAY-1,0,SCREEN_W-1);
	int now_y_pos=(int) custom_map(ELEV_ARR[mm-1][day_num-1][now_x_pos],minVal,maxVal,yBottom,yTop);
	_MEDIUM_SUN_(now_x_pos, now_y_pos, SUN_MARKER_COLOR);

	// Draw sun center marker
	myTFT.tft.fillCircle(now_x_pos, now_y_pos, 1, SUN_PATH_COLOR);

	// For twilight (i.e., for -6 deg elevation)
	int twi_y_pos=(int) custom_map(-6,minVal,maxVal,yBottom,yTop);
	myTFT.tft.drawLine(0, twi_y_pos, SCREEN_W-1, twi_y_pos, DARKGREY);

	// int nadir_y_pos=(int) custom_map(minVal,minVal,maxVal,yBottom,yTop);
	// LOG_DEBUG("nadir_y_pos="+String(nadir_y_pos));

	int noon_y_pos=(int) custom_map(maxVal,minVal,maxVal,yBottom,yTop);

	// Draw noon position marker
	int solar_noon  =    all_years[yy-BASE_YEAR][mm-1][(day_num-1)*NUM_ITEMS_PER_DAY+SOLAR_NOON_OFFSET];
	draw_time_marker(solar_noon,   mm,day_num,minVal,maxVal,yBottom,yTop,WHITE,2);


	return zero_line_y_pos;
}

// ----------------------------------------------------------------------------------------------- //
#define AZM_CIRCLE_RADIUS 100
#define AZM_CIRCLE_ORIG_X SCREEN_W/2
#define AZM_CIRCLE_ORIG_Y 175
#define AZM_CIRCLE_WIDTH 3
#define X_PADDING 50

// Max and min azimuths
#define SUMMER_SUNRISE_ANGLE 60
#define SUMMER_SUNSET_ANGLE 300
#define WINTER_SUNRISE_ANGLE 120
#define WINTER_SUNSET_ANGLE  240

#define NOON_MAX_ANGLE 76
#define NOON_MIN_ANGLE 29

#define ANGLE_FONT FreeMonoBold20pt7b
#define LABEL_FONT FreeMonoBold9pt7b

#define _CONST RADIAN_MULT+ANGLE_OFFSET

#define _COND1 input_angle>330 && input_angle<=30
#define _COND2 input_angle>150 && input_angle<=210

#define _DRAW_ANGLE_LIMITS_ {\
	draw_angle_marker(SUMMER_SUNRISE_ANGLE,1, WHITE);\
	draw_angle_marker(SUMMER_SUNSET_ANGLE,-1, WHITE);\
	draw_angle_marker(WINTER_SUNRISE_ANGLE,2, WHITE);\
	draw_angle_marker(WINTER_SUNSET_ANGLE,-1, WHITE);\
}

// Draw concentric circles / altitude axis
#define _DRAW_CIRCLES_ {\
	for (int i=0;i<90;i+=10)\
		myTFT.tft.drawCircle(AZM_CIRCLE_ORIG_X,AZM_CIRCLE_ORIG_Y, AZM_CIRCLE_RADIUS-i, LIGHTBLACK);\
}

#define _DRAW_N_MARKER_(FONT) {\
	uint16_t w1=get_text_width("N", FONT);\
	uint16_t h1=get_text_height("N", FONT);\
	Shivam_TXT north = Shivam_TXT(AZM_CIRCLE_ORIG_X-(int)w1/2, AZM_CIRCLE_ORIG_Y-AZM_CIRCLE_RADIUS+h1+AZM_CIRCLE_WIDTH+2, FONT, 1, RED, BG_COLOR);\
	north.begin(myTFT.tft);\
	north.print_tft("N");\
}

#define _DRAW_MAIN_CIRCLE_ {for (int r=AZM_CIRCLE_RADIUS;r<(AZM_CIRCLE_RADIUS+AZM_CIRCLE_WIDTH);r++) myTFT.tft.drawCircle(AZM_CIRCLE_ORIG_X, AZM_CIRCLE_ORIG_Y, r, RED);}

#define _DRAW_HOUR_MARKERS_ {for (int hour=0; hour <24; hour++) draw_time_label(hour, AZM_ARR[mm-1][day_of_month-1][(int)hour*60/AZM_MULT], DARKGREY);}

#define _SHOW_CURR_AZM_VAL_ {\
	uint day_of_year = get_day_of_year(localTime);\
	bool W=_IS_WINTER_(day_of_year);\
	int txt_ypos = AZM_CIRCLE_ORIG_Y + (int)( W ? -1*(AZM_CIRCLE_RADIUS/2)+20 : AZM_CIRCLE_RADIUS/2 + 20);\
	Shivam_TXT azm_txt = Shivam_TXT(5, txt_ypos,  FreeMonoBold18pt7b, 1, WHITE, BG_COLOR);\
	azm_txt.begin(myTFT.tft);\
	azm_txt.print_tft_centered_no_bg(String(curr_azm)+"'",AZM_CIRCLE_ORIG_X-1,AZM_CIRCLE_ORIG_X+1);\
	Shivam_TXT now_txt = Shivam_TXT(5, (W ? txt_ypos-20-12 : txt_ypos+20),  Font4x5Fixed, 2, DARKGREY, BG_COLOR);\
	now_txt.begin(myTFT.tft);\
	now_txt.print_tft_centered_no_bg("NOW",AZM_CIRCLE_ORIG_X-1,AZM_CIRCLE_ORIG_X+1);\
	Shivam_TXT noon_txt = Shivam_TXT(0, 310, FreeMonoBold9pt7b, 1, LIGHTGREY, BG_COLOR);\
	noon_txt.begin(myTFT.tft);\
	noon_txt.print_tft_middle("noon: "+get_readable_time(convert_to_local_time(solar_noon)));\
}


float get_xp(int angle,  int offset){ return AZM_CIRCLE_ORIG_X + (AZM_CIRCLE_RADIUS + offset) * cos(angle * _CONST); }
float get_yp(int angle,  int offset){ return AZM_CIRCLE_ORIG_Y + (AZM_CIRCLE_RADIUS + offset) * sin(angle * _CONST); }

void draw_angle_marker(int angle, int x_offset, int COLOR)
/* For marking min/max sunrise/sunset angles on azm circle. */
{
	float x = get_xp(angle,0)+x_offset;
	float y = get_yp(angle,0);
	myTFT.tft.fillCircle( x, y, 3 ,COLOR);
}

void draw_time_label(int hour, int input_angle, int COLOR)
/* For hour markers. */
{
	float x1 = get_xp(input_angle, -5);
	float y1 = get_yp(input_angle, -5);

	float x2 = get_xp(input_angle, 5);
	float y2 = get_yp(input_angle, 5);

	myTFT.tft.drawLine(x1, y1, x2, y2, COLOR);

	// if (_COND1) y2-=3;
	if ( _COND2) y2+=8;


	Shivam_TXT label_str = Shivam_TXT(get_xp(input_angle, 15), get_yp(input_angle, 15), Font4x5Fixed, 2, DARKGREY, BG_COLOR);
	label_str.begin(myTFT.tft);
	if (input_angle<180)
		label_str.print_tft_no_prev_bg(String(hour));
	else
		label_str.print_tft_ralign2(String(hour),x2-5,false);
}


void draw_line(uint32_t IN_ANGLE,float orig_x, float orig_y, uint color){

	GFXfont angle_font=ANGLE_FONT;
	GFXfont label_font=LABEL_FONT;

	// Draw sunset/sunrise angle line
	float x=orig_x+AZM_CIRCLE_RADIUS*cos(IN_ANGLE*RADIAN_MULT+ANGLE_OFFSET);
	float y=orig_y+AZM_CIRCLE_RADIUS*sin(IN_ANGLE*RADIAN_MULT+ANGLE_OFFSET);
	// myTFT.tft.drawLine(ORIG_X, ORIG_Y, x-1, y-1, color);
	myTFT.tft.drawLine(orig_x, orig_y, x, y, color);

	// myTFT.tft.drawLine(ORIG_X, ORIG_Y, x+1, y+1, color);

	myTFT.tft.fillCircle( x+2, y, 4 ,color);
}

// ------------------------------------------------------------------------------------------------------------------- //
void blit_angle_txt(time_t sunrise_sunset_t, uint32_t IN_ANGLE,float orig_x, float orig_y, uint8_t radius, uint8_t x_padding, uint color)
/* Draw lines & text for sunrise and sunset angles. */
{
	GFXfont angle_font=ANGLE_FONT;
	GFXfont label_font=LABEL_FONT;

	// draw_line(IN_ANGLE,orig_x, orig_y, color);

	// // Draw sunset/sunrise angle line
	float x=orig_x+AZM_CIRCLE_RADIUS*cos(IN_ANGLE*RADIAN_MULT+ANGLE_OFFSET);
	float y=orig_y+AZM_CIRCLE_RADIUS*sin(IN_ANGLE*RADIAN_MULT+ANGLE_OFFSET);
	// // myTFT.tft.drawLine(ORIG_X, ORIG_Y, x-1, y-1, color);
	// myTFT.tft.drawLine(orig_x, orig_y, x, y, color);

	// // myTFT.tft.drawLine(ORIG_X, ORIG_Y, x+1, y+1, color);

	// myTFT.tft.fillCircle( x+2, y, 4 ,color);

	// Blit sunset/sunrise angle text
	uint16_t w1=get_text_width(String(IN_ANGLE), angle_font);
	uint16_t h1=get_text_height(String(IN_ANGLE), angle_font);
	uint y_pos=y+(int)h1/2;

	uint x_pos;
	String label;
	if (IN_ANGLE>180){
		x_pos=x-w1-x_padding-20;
		label="SUNSET";
		// myTFT.tft.fillCircle( x-2, y, 4 ,color);
	}
	else{
		x_pos=x+x_padding;
		label="SUNRISE";
		// myTFT.tft.fillCircle( x+2, y, 4 ,color);
	}

	// Print angle
	Shivam_TXT curr_angle_str = Shivam_TXT(x_pos, y_pos, angle_font, 1, color, BG_COLOR);
	curr_angle_str.begin(myTFT.tft);
	curr_angle_str.print_tft(String(IN_ANGLE));

	// Display actual sunrise/sunset time
	Shivam_TXT T_TXT = Shivam_TXT(x_pos, y_pos+30, FreeMonoBold9pt7b, 1, LIGHTGREY, BG_COLOR);
	T_TXT.begin(myTFT.tft);
	T_TXT.print_tft_no_prev_bg(get_readable_time(convert_to_local_time(sunrise_sunset_t)));

	// --------------------------------------------------------------------------------
	// Degree sign
	uint8_t deg_radius=4;
	myTFT.tft.drawCircle(x_pos+w1+deg_radius*2+2, y+ (int)h1/2 - h1+deg_radius+2, deg_radius, color);
	deg_radius=3;
	myTFT.tft.drawCircle(x_pos+w1+deg_radius*2+2+2, y+ (int)h1/2 - h1+deg_radius+2+1, deg_radius, color);

	// deg_sign(angle_font, IN_ANGLE, x_pos, orig_y, color);


	// // Degree sign
	// uint8_t deg_radius=4;
	// int _x = x_pos + w1 + deg_radius*2 + 2;
	// int _y = y + (int)h1/2 - h1 + deg_radius + 2;
	// myTFT.tft.drawCircle(_x, _y, deg_radius, color);

	// deg_radius=3;
	// myTFT.tft.drawCircle(_x+2, _y+1, deg_radius, color);
	// --------------------------------------------------------------------------------

	// Blit sunrise/sunset label
	uint x_pos2;
	if (IN_ANGLE>180){
		uint16_t w2=get_text_width(label, label_font);
		x_pos2=x-w2-x_padding-20;
	}
	else
		x_pos2=x_pos;

	Shivam_TXT curr_label_str = Shivam_TXT(x_pos2, y-h1, label_font, 1, color, BG_COLOR);
	curr_label_str.begin(myTFT.tft);
	curr_label_str.print_tft(label);
}


// #define _TXT_(VAR,X,Y,FONT,SIZE,COLOR,BG) {Shivam_TXT VAR = Shivam_TXT(X,Y,FONT,SIZE,COLOR,BG); VAR.begin(myTFT.tft);} // doesnt work