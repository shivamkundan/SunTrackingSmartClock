#ifndef Shivam_PicoW_TFT_H
	#include <Shivam_PicoW_TFT.h>
#endif

#ifndef COLORS_H
	#include "../colors.h"
#endif

#ifndef SCREEN_CLASS_H
	#include "ScreenClass.h"
#endif

#ifndef TIME_FUNCS_H
	#include "../DateTime/time_funcs.h"
#endif



#define ANALOG_CLK_ORIGIN_X  240
#define ANALOG_CLK_ORIGIN_Y 160
#define ANALOG_CLK_RADIUS 140
#define ANALOG_CLK_RADIAL_OFFSET_PX 15

#define DEG_PER_HOUR 30  // Deg swept by hand in one hour
#define DEG_PER_MIN 6 	// Deg swept by hand in one minute

#define A (ANALOG_CLK_RADIUS-ANALOG_CLK_RADIAL_OFFSET_PX)
#define B RADIAN_MULT+ANGLE_OFFSET

#define CENTER_CIRC_RAD 6

void scr_analog_clk_on_enter(uint TimeStamp);


void draw_markers(){

	float xx=0;
	float yy=0;

	// minute markers
	for (int ang=0;ang<360;ang+=DEG_PER_MIN){
		xx=ANALOG_CLK_ORIGIN_X+A*cos(ang*B);
		yy=ANALOG_CLK_ORIGIN_Y+A*sin(ang*B);
		myTFT.tft.fillCircle(xx,yy,1,RED);
	}

	// hour markers
	for (int ang=0;ang<360;ang+=DEG_PER_HOUR){
		xx=ANALOG_CLK_ORIGIN_X+A*cos(ang*B);
		yy=ANALOG_CLK_ORIGIN_Y+A*sin(ang*B);
		myTFT.tft.fillCircle( xx, yy, 3 ,LIGHTGREY);

		if (ang==90){
			Shivam_TXT T = Shivam_TXT(xx-30, yy+6,      FreeMonoBold12pt7b, 1, TERTIARY_TXT_COLOR,    BG_COLOR);
			T.begin(myTFT.tft);
			T.print_tft_no_prev_bg("3");
		}
	}
}

void draw_minute_hand(uint8_t MM, uint color){
	uint16_t minute_angle = (uint16_t) MM*DEG_PER_MIN;
	float xx=ANALOG_CLK_ORIGIN_X+(A-20)*cos(minute_angle*B);
	float yy=ANALOG_CLK_ORIGIN_Y+(A-20)*sin(minute_angle*B);
	myTFT.tft.drawLine(ANALOG_CLK_ORIGIN_X, ANALOG_CLK_ORIGIN_Y, xx, yy, color);		// draw minute hand
	// LOG_DEBUG("minute_angle= "+String(minute_angle)+" deg");
}

void draw_hour_hand(uint8_t HH, uint8_t MM, uint color){
	uint16_t hour_angle = HH*DEG_PER_HOUR + (uint16_t) MM/2;
	float xx=ANALOG_CLK_ORIGIN_X+(ANALOG_CLK_RADIUS-50)*cos(hour_angle*B);
	float yy=ANALOG_CLK_ORIGIN_Y+(ANALOG_CLK_RADIUS-50)*sin(hour_angle*B);
	// myTFT.tft.drawLine(ANALOG_CLK_ORIGIN_X, ANALOG_CLK_ORIGIN_Y, xx, yy, color);		// draw hour hand
	// myTFT.tft.drawLine(ANALOG_CLK_ORIGIN_X, ANALOG_CLK_ORIGIN_Y+1, xx, yy, color);		// draw hour hand
	// myTFT.tft.drawLine(ANALOG_CLK_ORIGIN_X, ANALOG_CLK_ORIGIN_Y-1, xx, yy, color);		// draw hour hand
	// myTFT.tft.drawLine(ANALOG_CLK_ORIGIN_X+1, ANALOG_CLK_ORIGIN_Y, xx, yy, color);		// draw hour hand
	// myTFT.tft.drawLine(ANALOG_CLK_ORIGIN_X+1, ANALOG_CLK_ORIGIN_Y, xx, yy, color);		// draw hour hand

	int x1=ANALOG_CLK_ORIGIN_X;
	int x2=ANALOG_CLK_ORIGIN_X;
	int x3=xx;

	int y1=ANALOG_CLK_ORIGIN_Y-CENTER_CIRC_RAD/2 -3;
	int y2=ANALOG_CLK_ORIGIN_Y+CENTER_CIRC_RAD/2 +3;
	int y3=yy;
	myTFT.tft.fillTriangle(x1, y1, x2, y2, x3, y3,color);
	// LOG_DEBUG("hour_angle= "+String(hour_angle)+" deg");
}

void draw_seconds_hand(uint8_t ss, uint color){
	uint16_t second_angle = (uint16_t) ss*DEG_PER_MIN;
	float xx=ANALOG_CLK_ORIGIN_X+A*cos(second_angle*B);
	float yy=ANALOG_CLK_ORIGIN_Y+A*sin(second_angle*B);
	myTFT.tft.drawLine(ANALOG_CLK_ORIGIN_X, ANALOG_CLK_ORIGIN_Y, xx, yy, color);		// draw minute hand
	// LOG_DEBUG("second_angle: "+String(second_angle));
	if (second_angle%DEG_PER_HOUR!=0)
		myTFT.tft.fillCircle( xx, yy, 2 ,YELLOW);  								// draw minute marker
	else
		myTFT.tft.fillCircle( xx, yy, 3 ,RED);
}
// ----------------------------------------------------

void scr_analog_clk_per_second(uint TimeStamp){

	// These vars save current time vals
	uint16_t DD=1; char am_pm; bool AM=false;
	uint8_t HH,MM,ss;
	get_individual_time(convert_to_local_time(TimeStamp), DD, HH, MM, ss, AM);

	// Draw seconds hand
	draw_seconds_hand(ss, RED);

	// Erase previous seconds hand
	draw_seconds_hand(ss-1, BG_COLOR);

	// Draw center circle
	myTFT.tft.fillCircle(ANALOG_CLK_ORIGIN_X,ANALOG_CLK_ORIGIN_Y,CENTER_CIRC_RAD,RED);

	// Re-draw minute hand
	if (ss-1==MM)
		draw_minute_hand(MM,WHITE);
	
	// Re-draw hour hand
	if (ss-1==HH)
		draw_hour_hand(HH, MM, LIGHTGREY);

	// if (prev_MM!=MM){
	// 	myTFT.tft.fillCircle(ANALOG_CLK_ORIGIN_X,ANALOG_CLK_ORIGIN_Y,ANALOG_CLK_RADIUS,BG_COLOR);
	// 	scr_analog_clk_on_enter( TimeStamp);
	// 	// scr_analog_clk_per_minute(TimeStamp);
	// }
}


void scr_analog_clk_per_minute(uint TimeStamp){
	myTFT.clear_screen(BG_COLOR);
	uint16_t DD=1; char am_pm; bool AM=false;
	uint8_t HH,MM,ss;
	get_individual_time(convert_to_local_time(TimeStamp), DD, HH, MM, ss, AM);

	draw_markers();

	// Draw hour hand
	draw_hour_hand(HH, MM, LIGHTGREY);

	// Draw minute hand
	draw_minute_hand(MM,WHITE);
}

void scr_analog_clk_on_enter(uint TimeStamp){


	scr_analog_clk_per_minute(TimeStamp);
	// // These vars save current time vals
	// uint16_t DD=1; char am_pm; bool AM=false;
	// uint8_t HH,MM,ss;
	// get_individual_time(convert_to_local_time(TimeStamp), DD, HH, MM, ss, AM);

	// draw_markers();

	// // Draw hour hand
	// draw_hour_hand(HH, MM, LIGHTGREY);

	// // Draw minute hand
	// draw_minute_hand(MM,WHITE);


}

void scr_analog_clk_initialize(Screen* S){
	S->set_func_per_second(scr_analog_clk_per_second);
	S->set_func_per_minute(scr_analog_clk_per_minute);
	S->set_func_per_hour(do_nothing);
	S->set_func_on_enter(scr_analog_clk_on_enter);
	S->set_func_on_exit(do_nothing);
	S->set_func_on_touch(do_nothing);
	S->show_power_info=false;
	S->show_backlight_info=false;
}