#ifndef COMMON_H
	#include "common.h"
#endif

#define _yT _yTop+10
#define _yB _yBottom+10

#define END_Y 200
#define _DRAW_DIVIDER_(EVENT) { draw_dotted_vline(/*tft*/ myTFT.tft, /*gap_len*/5, /*segment_len*/1, /*start_y*/30, /*end_y*/__Y2+5, /*x_pos*/ _GET_POS_(EVENT) , /*color*/ WHITE); }

#define _DRAW_DIVS_(T1,T2,T3,T4) { _DRAW_DIVIDER_(T1) _DRAW_DIVIDER_(T2) _DRAW_DIVIDER_(T3) _DRAW_DIVIDER_(T4) }

// #define __Y0 zero_line_y_pos+25 // for x-axis labels
#define __Y1 __Y0+40		// for daylight %
#define __Y2 __Y1+35		// for thirds durations
#define __Y3 SCREEN_H-15	// for total day %
#define __Y4 __Y3-10	// for total day % hline ypos

#define __Y5 SCREEN_H-50 // For line2 of time display
#define __Y6 __Y5-25 // For line1 of time display
#define __Y7 __Y2+20 // For dawn and dusk duration


#define _PCT_LINE_XPAD_ 10  // for total day % hline padding



#define _DURATION_(TT, TXT, FUNC) {\
	uint8_t m,s; uint16_t h;\
	secondsToHMS(TT,h,m,s);\
	String LEN1=String(h)+"hr "+String(m)+"min";\
	TXT.FUNC(LEN1);\
}

#define _SHOW_DURATIONS_(T1, T2) { _DURATION_(T1,day_len_TXT2,print_tft_no_prev_bg) _DURATION_(T2,day_len_TXT2,print_tft_ralign_no_bg) }

void scr_detailed_main(time_t TimeStamp)
/* Draw both elevation and azimuth diagrams */
{

	myTFT.clear_screen(BG_COLOR);

	// -------------------- Retrieve current date/time -------------------- //
	time_t localTime = convert_to_local_time(TimeStamp);
	int day_num=get_day_of_month(localTime);
	int mm=convert_to_tmelements(localTime).Month;
	int yy=convert_to_tmelements(localTime).Year+UNIX_START_YEAR;
	uint16_t today_minute=get_minute_of_day(localTime);

	// --------------------------- Draw diagram --------------------------- //
	// int zero_line_y_pos = draw_elevation_diagram (day_num,mm,yy,today_minute,_yT,_yB);
	int day_of_year = get_day_of_year(localTime);
	int yT=_yT;
	int yB=_yB;

	/*Mar 3 to Nov 1*/
	if (day_of_year<=MAR_3 || day_of_year>=NOV_1){
		yT=35; yB=yT+ELEV_DIAG_HEIGHT;
	}
	int zero_line_y_pos = draw_elevation_diagram (day_num,mm,yy,today_minute,yT,yB);
	
	// --------------------------- Draw x-axis labels --------------------------- //
	draw_x_labels(zero_line_y_pos);


	// ----------------------- Retrieve event times ----------------------- //
	int midnight, astro_dawn, nautical_dawn, first_light, sunrise, solar_noon,
		sunset, last_light, nautical_dusk, astro_dusk;
	get_today_events(yy, mm, day_num, midnight, astro_dawn, nautical_dawn, first_light,
		sunrise, solar_noon, sunset, last_light, nautical_dusk, astro_dusk);
	int midnight_tomorrow = midnight+NUM_SECS_IN_DAY;

	// ------------------------ Draw dividing lines ----------------------- //
	_DRAW_DIVS_(first_light, last_light, sunrise, sunset)

	// ------------------------ Calculate duration ------------------------ //
	int elapsed_light=TimeStamp-first_light;
	int total_light=last_light-first_light;

	// ------------------------ Print pct of daylight remaining ------------------------ //
	Shivam_TXT SSS_TXT = Shivam_TXT(5, __Y1, FreeMonoBold20pt7b, 1, YELLOW, BG_COLOR);
	SSS_TXT.begin(myTFT.tft);
	if (elapsed_light>0 && TimeStamp<last_light){
		SSS_TXT.print_tft_middle(String(100*(float)elapsed_light/total_light)+"%");
	}
	else
		SSS_TXT.print_tft_middle("--%");


	// ------------------------ Print % of total day remaining ------------------------ //
	draw_dotted_hline(/*tft*/ myTFT.tft, /*gap_len*/5, /*segment_len*/1, /*start_x*/_PCT_LINE_XPAD_, /*end_x*/SCREEN_W-_PCT_LINE_XPAD_, /*y_pos*/__Y4 , /*color*/ LIGHTGREY);
	SSS_TXT.set_y_pos(__Y3);
	SSS_TXT.print_tft_middle(String(100*((float)today_minute/NUM_MINS_IN_DAY))+"%");

	// ------------------------- Show durations of thirds ------------------------- //
	Shivam_TXT day_len_TXT = Shivam_TXT(5, __Y2, FreeMonoBold12pt7b, 1, CYAN, BG_COLOR);
	day_len_TXT.begin(myTFT.tft);

	_DURATION_(total_light, day_len_TXT, print_tft_middle)

	Shivam_TXT day_len_TXT2 = Shivam_TXT(0, __Y2-15, FreeMonoBold9pt7b, 1, LIGHTGREY, BG_COLOR);
	day_len_TXT2.begin(myTFT.tft);

	_SHOW_DURATIONS_(first_light-midnight, midnight_tomorrow-last_light)

	// -------------------------------------------------------------
	// Print sun elevation angle
	int now_x_pos=custom_map (today_minute,0,NUM_MINS_IN_DAY-1,0,SCREEN_W-1);
	Shivam_TXT elevation_TXT = Shivam_TXT(5, 13, FreeMonoBold9pt7b, 1, WHITE, BG_COLOR);
	elevation_TXT.begin(myTFT.tft);
	elevation_TXT.print_tft_middle("now: "+String(ELEV_ARR[mm-1][day_num-1][now_x_pos])+" deg");

	// -------------------------------------------------------------
	uint8_t m,s; uint16_t h;
	secondsToHMS(sunrise-first_light,h,m,s);
	String DAWN_LEN=String(m)+"min";
	// LOG_DEBUG(DAWN_LEN);

	secondsToHMS(last_light-sunset,h,m,s);
	String DUSK_LEN=String(m)+"min";
	// LOG_DEBUG(DUSK_LEN);

	// -------------------------------------------------------------

	Shivam_TXT T_TXT = Shivam_TXT(0, __Y5, FreeMonoBold9pt7b, 1, RED, BG_COLOR);
	T_TXT.begin(myTFT.tft);

	T_TXT.print_tft(get_readable_time(convert_to_local_time(first_light)));
	T_TXT.print_tft_middle(get_readable_time(convert_to_local_time(solar_noon)));
	T_TXT.print_tft_ralign2(get_readable_time(convert_to_local_time(last_light)),SCREEN_W-5,false);

	T_TXT.set_y_pos(__Y6);
	T_TXT.print_tft_centered(get_readable_time(convert_to_local_time(sunrise)),30,SCREEN_W/2);
	T_TXT.print_tft_centered(get_readable_time(convert_to_local_time(sunset)),SCREEN_W/2,SCREEN_W-30);


	// Print dusk and dawn length
	Shivam_TXT TGREY_TXT = Shivam_TXT(0, __Y7, Font4x5Fixed, 2, DARKGREY, BG_COLOR);
	TGREY_TXT.begin(myTFT.tft);
	TGREY_TXT.print_tft_centered(DAWN_LEN, (uint) _GET_POS_(first_light) , (uint) _GET_POS_(sunrise) );
	TGREY_TXT.print_tft_centered(DUSK_LEN, (uint) _GET_POS_(sunset) , (uint) _GET_POS_(last_light));



}

void scr_detailed_per_minute(uint TimeStamp){
	scr_detailed_main(TimeStamp);
}

void scr_detailed_on_enter(uint TimeStamp){
	scr_detailed_main(TimeStamp);
}

void scr_detailed_initialize(Screen* S){
	S->set_func_per_second(do_nothing);
	S->set_func_per_minute(scr_detailed_per_minute);
	S->set_func_per_hour(do_nothing);
	S->set_func_on_enter(scr_detailed_on_enter);
	S->set_func_on_exit(do_nothing);
	S->set_func_on_touch(do_nothing);

	S->show_power_info=false;
	// S->show_mw_icon=false;
	// S->show_icons=false;
}