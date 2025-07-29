#ifndef COMMON_H
	#include "common.h"
#endif

#define DAY_PATH_COLOR YELLOW
#define NIGHT_PATH_COLOR BROWN
#define YEARLY_RANGE_COLOR DARKGREY
// #define YEARLY_RANGE_COLOR LIGHTBLACK

// bool DRAW_NIGHT_PATH = true; // Draws alt+az path for night time too

void draw_sun_yearly_range(uint year)
/* Draws all possible sun positions for my latitude. */
{
	// XPOS_LIST
	for (int i=0;i<LEN_LIST;i++){
		myTFT.tft.drawPixel(XPOS_LIST[i], YPOS_LIST[i], YEARLY_RANGE_COLOR);
	}
}

void draw_point(float curr_azm, int curr_elev, int radius, int color)
/* Draws pixel using angle, distance information. */
{
	int radial_dist = custom_map(curr_elev, (curr_elev>=0 ? 90 : -90), 0, 0, AZM_CIRCLE_RADIUS);

	int new_x = AZM_CIRCLE_ORIG_X + radial_dist * cos(curr_azm * _CONST);
	int new_y = AZM_CIRCLE_ORIG_Y + radial_dist * sin(curr_azm * _CONST);
	myTFT.tft.fillCircle(new_x,new_y,radius,color);
}

void scr_alt_azm_main(uint TimeStamp){
	myTFT.clear_screen(BG_COLOR);
	_PRINT_TITLE_SMALL_("ALT / AZM");

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

	// ------------- Draw concentric circles ------------- //
	_DRAW_CIRCLES_

	// ------------- Draw sun pos range for year ------------- //
	draw_sun_yearly_range(yy);

	// ------------------ Draw cardinal direction markers ------------------ //
	_DRAW_N_MARKER_(FreeMonoBold16pt7b)

	// ------------------ Draw main circle ------------------ //
	_DRAW_MAIN_CIRCLE_

	// ------------- Show hour markers ------------- //
	_DRAW_HOUR_MARKERS_

	// ------------- Draw altitude path for today ------------- //
	for (int i=0;i<480;i++){
		float curr_elev = ELEV_ARR[mm-1][day_of_month-1][i];
		int curr_azm=AZM_ARR[mm-1][day_of_month-1][i];
		draw_point(curr_azm, curr_elev, 1, (curr_elev>=0 ? DAY_PATH_COLOR : NIGHT_PATH_COLOR));
	}

	// ------------- Draw sunrise/sunset limits ------------- //
	_DRAW_ANGLE_LIMITS_

	// ------------- Show solar noon point ------------- //
	uint16_t SN = get_minute_of_day(convert_to_local_time(solar_noon));
	float elev = ELEV_ARR[mm-1][day_of_month-1][(int)(SN/AZM_MULT)];
	float azm=AZM_ARR[mm-1][day_of_month-1][(int)(SN/AZM_MULT)];
	draw_point(azm,elev,4,RED);

	int radial_dist = custom_map(elev, (elev>=0 ? 90 : -90), 0, 0, AZM_CIRCLE_RADIUS);
	int new_x = AZM_CIRCLE_ORIG_X + radial_dist * cos(azm * _CONST);
	int new_y = AZM_CIRCLE_ORIG_Y + radial_dist * sin(azm * _CONST);
	Shivam_TXT label_str = Shivam_TXT(new_x, new_y+25, FreeSansBold10pt7b, 1, ORANGE, BG_COLOR);
	label_str.begin(myTFT.tft);
	label_str.print_tft_centered(String((int)round(elev)),new_x-1,new_x+1);
	label_str.print_tft_centered(String(elev,0),new_x-1,new_x+1);

	// ------------- Draw sun marker ------------- //
	uint16_t today_minute=get_minute_of_day(localTime);
	uint32_t curr_azm=AZM_ARR[mm-1][day_of_month-1][(int)today_minute/AZM_MULT];
	float curr_elev = ELEV_ARR[mm-1][day_of_month-1][(int)(today_minute/AZM_MULT)];
	// float x=get_xp(curr_azm,0);
	// float y=get_yp(curr_azm,0);
	int now_radial_dist = custom_map(curr_elev, (curr_elev>=0 ? 90 : -90), 0, 0, AZM_CIRCLE_RADIUS);
	int now_x = AZM_CIRCLE_ORIG_X + now_radial_dist * cos(curr_azm * _CONST);
	int now_y = AZM_CIRCLE_ORIG_Y + now_radial_dist * sin(curr_azm * _CONST);
	_MEDIUM_SUN_(now_x,  now_y, ORANGE);

	draw_line(sunset_angle,AZM_CIRCLE_ORIG_X, AZM_CIRCLE_ORIG_Y, YELLOW);
	draw_line(sunrise_angle,AZM_CIRCLE_ORIG_X, AZM_CIRCLE_ORIG_Y, CYAN);

	// ------------------ Sunset line, angle, and label ------------------ //
	blit_angle_txt(sunset, sunset_angle, AZM_CIRCLE_ORIG_X,  AZM_CIRCLE_ORIG_Y,  AZM_CIRCLE_RADIUS,  X_PADDING, YELLOW);

	// ------------------ Sunrise line, angle, and label ------------------ //
	blit_angle_txt(sunrise, sunrise_angle, AZM_CIRCLE_ORIG_X,  AZM_CIRCLE_ORIG_Y,  AZM_CIRCLE_RADIUS,  X_PADDING, CYAN);

	// ================================================================================== //

	// ------------- Show current azimuth value ------------- //
	_SHOW_CURR_AZM_VAL_

	Shivam_TXT azm_txt = Shivam_TXT(5, 50,  FreeMonoBold9pt7b, 1, ORANGE, BG_COLOR);
	azm_txt.begin(myTFT.tft);
	// azm_txt.print_tft_middle("NOW: "+String(curr_azm));

	azm_txt.change_color(LIGHTGREY);
	azm_txt.set_y_pos(310);
	azm_txt.print_tft_middle("noon: "+get_readable_time(convert_to_local_time(solar_noon)));

	// // Shivam_TXT lbl = Shivam_TXT(0,70, FreeMonoBold8pt7b, 1, RED, BG_COLOR);
	// Shivam_TXT lbl = Shivam_TXT(0,70, Font4x5Fixed, 2, RED, BG_COLOR);

	// lbl.begin(myTFT.tft);
	// lbl.print_tft_no_prev_bg("FIRST LIGHT");

	// lbl.increment_y_pos(50); lbl.print_tft_no_prev_bg("SUNRISE");
	// lbl.increment_y_pos(50); lbl.print_tft_no_prev_bg("SOLAR NOON");
	// lbl.increment_y_pos(50); lbl.print_tft_no_prev_bg("SUNSET");
	// lbl.increment_y_pos(50); lbl.print_tft_no_prev_bg("LAST LIGHT");

	// Shivam_TXT val = Shivam_TXT(0,70+16, FreeMonoBold8pt7b, 1, YELLOW, BG_COLOR); val.begin(myTFT.tft);
	// val.print_tft_no_prev_bg("XXXX");
	// val.increment_y_pos(50); val.print_tft_no_prev_bg(get_readable_time(convert_to_local_time(sunrise)));
	// val.increment_y_pos(50); val.print_tft_no_prev_bg(get_readable_time(convert_to_local_time(solar_noon)));
	// val.increment_y_pos(50); val.print_tft_no_prev_bg(get_readable_time(convert_to_local_time(sunset)));
	// val.increment_y_pos(50); val.print_tft_no_prev_bg("XXXX");

}


void scr_alt_azm_initialize(Screen* S){
	S->set_func_per_second(do_nothing);
	S->set_func_per_minute(scr_alt_azm_main);
	S->set_func_per_hour(do_nothing);
	S->set_func_on_enter(scr_alt_azm_main);
	S->set_func_on_exit(do_nothing);
	S->set_func_on_touch(do_nothing);
	S->show_power_info=false;
	// S->show_backlight_info=false;
	// S->show_mw_icon=false;
	// S->show_icons=false;
}

