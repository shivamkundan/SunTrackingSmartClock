#ifndef COMMON_H
	#include "common.h"
#endif

#define _IS_WINTER_(DNUM) {(DNUM>=1 && DNUM<=MAR_19) || (DNUM>=SEP_22 && DNUM<=NUM_DAYS_YEAR)}



void scr_azm_main(uint TimeStamp)
/* Main function for drawing azimuth diagram. */
{

	myTFT.clear_screen(BG_COLOR);
	_PRINT_TITLE_SMALL_("AZIMUTH");

	// ----------------------- Retrieve event times ----------------------- //
	time_t localTime = convert_to_local_time(TimeStamp);
	int day_of_month=get_day_of_month(localTime);
	int mm=convert_to_tmelements(localTime).Month;
	int yy=convert_to_tmelements(localTime).Year+UNIX_START_YEAR;
	uint sunrise = get_sunrise(yy,mm,day_of_month);
	uint solar_noon = get_solar_noon(yy,mm,day_of_month);
	uint sunset = get_sunset(yy,mm,day_of_month);

	// ------------- Retrieve angles ------------- //
	uint32_t sunrise_angle = SUNRISE_ANGLE_ARR[mm-1][get_day_of_month(localTime)-1];
	uint32_t noon_angle    = NOON_ANGLE_ARR   [mm-1][get_day_of_month(localTime)-1];
	uint32_t sunset_angle  = SUNSET_ANGLE_ARR [mm-1][get_day_of_month(localTime)-1];


	// ------------------ Draw cardinal direction markers ------------------ //
	_DRAW_N_MARKER_(FreeMonoBold16pt7b)

	// ------------------ Draw main circle ------------------ //
	_DRAW_MAIN_CIRCLE_

	// ------------- Show hour markers ------------- //
	_DRAW_HOUR_MARKERS_

	// ------------- Draw sunrise/sunset limits ------------- //
	_DRAW_ANGLE_LIMITS_


	// ------------- Draw sun marker ------------- //
	uint16_t today_minute=get_minute_of_day(localTime);
	uint32_t curr_azm=AZM_ARR[mm-1][day_of_month-1][(int)today_minute/AZM_MULT];
	float curr_elev = ELEV_ARR[mm-1][day_of_month-1][(int)(today_minute/AZM_MULT)];
	float x=get_xp(curr_azm,0);
	float y=get_yp(curr_azm,0);
	_MEDIUM_SUN_(x, y, ORANGE) // draws bitmap

	draw_line(sunset_angle,AZM_CIRCLE_ORIG_X, AZM_CIRCLE_ORIG_Y, YELLOW);
	draw_line(sunrise_angle,AZM_CIRCLE_ORIG_X, AZM_CIRCLE_ORIG_Y, CYAN);

	// ================================================================================== //
	// ================================================================================== //

	// ------------------ Sunset line, angle, and label ------------------ //
	blit_angle_txt(sunset, sunset_angle, AZM_CIRCLE_ORIG_X,  AZM_CIRCLE_ORIG_Y,  AZM_CIRCLE_RADIUS,  X_PADDING, YELLOW);

	// ------------------ Sunrise line, angle, and label ------------------ //
	blit_angle_txt(sunrise, sunrise_angle, AZM_CIRCLE_ORIG_X,  AZM_CIRCLE_ORIG_Y,  AZM_CIRCLE_RADIUS,  X_PADDING, CYAN);

	// ------------- Show current azimuth value ------------- //
	_SHOW_CURR_AZM_VAL_

	// // Determine y-pos
	// uint day_of_year = get_day_of_year(localTime);
	// bool W=_IS_WINTER_(day_of_year);
	// int txt_ypos = AZM_CIRCLE_ORIG_Y + (int)( W ? -1*(AZM_CIRCLE_RADIUS/2)+20 : AZM_CIRCLE_RADIUS/2 - 10);

	// Shivam_TXT azm_txt = Shivam_TXT(5, txt_ypos,  FreeMonoBold18pt7b, 1, WHITE, BG_COLOR);
	// azm_txt.begin(myTFT.tft);
	// azm_txt.print_tft_centered(String(curr_azm)+"'",AZM_CIRCLE_ORIG_X-1,AZM_CIRCLE_ORIG_X+1);

	// Shivam_TXT now_txt = Shivam_TXT(5, txt_ypos+20,  Font4x5Fixed, 2, DARKGREY, BG_COLOR);
	// now_txt.begin(myTFT.tft);
	// now_txt.print_tft_centered("NOW",AZM_CIRCLE_ORIG_X-1,AZM_CIRCLE_ORIG_X+1);


	// Shivam_TXT noon_txt = Shivam_TXT(0, 310, FreeMonoBold9pt7b, 1, LIGHTGREY, BG_COLOR);
	// noon_txt.begin(myTFT.tft); 
	// noon_txt.print_tft_middle("noon: "+get_readable_time(convert_to_local_time(solar_noon)));
}

void scr_azm_initialize(Screen* S){
	S->set_func_per_second(do_nothing);
	S->set_func_per_minute(scr_azm_main);
	S->set_func_per_hour(do_nothing);
	S->set_func_on_enter(scr_azm_main);
	S->set_func_on_exit(do_nothing);
	S->set_func_on_touch(do_nothing);
	S->show_power_info=false;
	// S->show_backlight_info=false;
	// S->show_mw_icon=false;
	// S->show_icons=false;
}

