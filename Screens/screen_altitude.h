/**
 * This screen shows altitude (elevation) values for any given day of year
 *
 */

#ifndef COMMON_H
	#include "common.h"
#endif

#define NOON_RADIUS 120
#define NOON_X 70//SCREEN_W/2 //-NOON_RADIUS/2
#define NOON_Y 200
#define SOLAR_NOON_LABEL_Y 110
#define SOLAR_MIDNIGHT_LABEL_Y 230

#define NOON_DIAGRAM_ARC_COLOR WHITE
#define HOUR_MARKER_COLOR LIGHTGREEN

#define _PIX_(A,B){ myTFT.tft.drawPixel(A, B, NOON_DIAGRAM_ARC_COLOR);}

uint color=ORANGE;

int get_xpos(float closest_i){ return NOON_X+cos(closest_i)*NOON_RADIUS; }
int get_ypos(float closest_i){ return NOON_Y + sin(closest_i) * NOON_RADIUS; }

#define DIVIDER_COL SCREEN_W/2 + 40

#define _ARGS_ 40+SCREEN_W/2,SCREEN_W

void scr_altitude_main(uint TimeStamp)
/* Draw noon-angle diagram. */
{
	myTFT.clear_screen(BG_COLOR);
	_PRINT_TITLE_SMALL_("ALTITUDE");

	// ------------- Draw stick figure -------------//
	myTFT.tft.drawBitmap(NOON_X-20, NOON_Y, stick_figure_bmp,     20, 50, WHITE);

	// ----------------------- Retrieve event times ----------------------- //
	time_t localTime = convert_to_local_time(TimeStamp);
	int day_num=get_day_of_month(localTime);
	int mm=convert_to_tmelements(localTime).Month;
	int yyyy=convert_to_tmelements(localTime).Year+UNIX_START_YEAR;
	uint16_t today_minute=get_minute_of_day(localTime);

	int solar_noon	= get_solar_noon(yyyy,mm,day_num);
	uint32_t noon_angle    = NOON_ANGLE_ARR[mm-1][get_day_of_month(localTime)-1];
	float E_now = ELEV_ARR[mm-1][day_num-1][(int)(today_minute/AZM_MULT)];

	// ------------------------------------ Draw arc ------------------------------------ //
	float closest_point=10000;
	float closest_i=100;

	for (float i = start_angle; i < end_angle; i = i + step)
	{
		int x_pos, y_pos;
		x_pos = get_xpos(i); //NOON_X + cos(i) * NOON_RADIUS;
		y_pos = get_ypos(i);//NOON_Y + sin(i) * NOON_RADIUS;

		_PIX_(x_pos-1, y_pos); _PIX_(x_pos, y_pos); _PIX_(x_pos+1, y_pos);
		_PIX_(x_pos, y_pos-1); _PIX_(x_pos, y_pos+1);

		float i_deg=(i/RADIAN_MULT)-ANGLE_OFFSET;
		float i_map=map(i_deg,270,360,90,0);  // Used for remapping angles

		if (abs(noon_angle-i_map)<closest_point){
			closest_point=abs(noon_angle-i_map);
			closest_i=i;
		}
		// sprintf(buf,"i: %.2f, i_deg:%.3f, i_map:%.4f, x_pos= %d, y_pos=%d",i,i_deg,i_map,x_pos,y_pos);
		// LOG_DEBUG(buf);
	}

	// ----------------------- Text ----------------------- //
	GFXfont angle_font=ANGLE_FONT;
	GFXfont label_font=LABEL_FONT;

	// -------------------- Print solar noon & solar midnight angles + times -------------------- //

	int MIN = MIN_ELEV_ARRAY[mm-1][get_day_of_month(localTime)-1];
	int MAX = MAX_ELEV_ARRAY[mm-1][get_day_of_month(localTime)-1];

	Shivam_TXT angle_str = Shivam_TXT(1, SOLAR_NOON_LABEL_Y-30, angle_font, 1, color, BG_COLOR);
	angle_str.begin(myTFT.tft);
	angle_str.print_tft_centered(String(MAX)+String('\''),_ARGS_);

	Shivam_TXT label_str = Shivam_TXT(1,SOLAR_NOON_LABEL_Y, label_font, 1, color, BG_COLOR);
	label_str.begin(myTFT.tft);
	label_str.print_tft_centered("SOLAR NOON",_ARGS_);

	Shivam_TXT time_str = Shivam_TXT(1,SOLAR_NOON_LABEL_Y+30, FreeMonoBold9pt7b, 1, LIGHTGREY, BG_COLOR);
	time_str.begin(myTFT.tft);
	time_str.print_tft_centered(get_readable_time(convert_to_local_time(solar_noon)),_ARGS_);

	angle_str.change_color(CYAN);
	angle_str.set_y_pos(SOLAR_MIDNIGHT_LABEL_Y-30);
	angle_str.print_tft_centered(String(MIN)+String('\''),_ARGS_);

	label_str.change_color(CYAN);
	label_str.set_y_pos(SOLAR_MIDNIGHT_LABEL_Y);
	label_str.print_tft_centered("SOLAR MIDNIGHT",_ARGS_);

	time_str.set_y_pos(SOLAR_MIDNIGHT_LABEL_Y+30);
	time_str.print_tft_centered(get_readable_time(convert_to_local_time(solar_noon+NUM_SECS_IN_DAY/2)),_ARGS_);

	LOG_DEBUG("Min: "+String(MIN)+" / Max:"+String(MAX)+" / Diff:"+String(MAX-MIN));
	// ------------------------------------------------------------------------------------------ //

	// -------------------------------------- Show hour markers -------------------------------------- //
	// Draw hour markers for 00:00 to 12:00
	for (int hour=5; hour <13; hour++){
		int E = ELEV_ARR[mm-1][day_num-1][(int)hour*60/AZM_MULT];

		if (E>0){
			float Ci = find_closest_i(E);
			// LOG_DEBUG(String(hour)+": "+String(E)+" deg | closest_i: "+String(Ci)+" | ("+String(get_xpos(Ci))+", "+String(get_ypos(Ci))+")");
			myTFT.tft.fillCircle(get_xpos(Ci), get_ypos(Ci), 3, HOUR_MARKER_COLOR);

			Shivam_TXT label_str = Shivam_TXT(get_xpos(Ci)+10, get_ypos(Ci)-10, Font4x5Fixed, 2, DARKGREY, BG_COLOR);
			label_str.begin(myTFT.tft);
			label_str.print_tft_no_prev_bg(String(hour)+"A");
		}
	}
	// Draw hour markers for 12:00 to 00:00
	for (int hour=13; hour <24; hour++){
		int E = ELEV_ARR[mm-1][day_num-1][(int)hour*60/AZM_MULT];

		if (E>0){
			float Ci = find_closest_i(E);
			// LOG_DEBUG(String(hour)+": "+String(E)+" deg | closest_i: "+String(Ci)+" | ("+String(get_xpos(Ci))+", "+String(get_ypos(Ci))+")");
			myTFT.tft.fillCircle(get_xpos(Ci), get_ypos(Ci), 3, HOUR_MARKER_COLOR);

			Shivam_TXT label_str = Shivam_TXT(get_xpos(Ci)+10+20, get_ypos(Ci)-10, Font4x5Fixed, 2, DARKGREY, BG_COLOR);
			label_str.begin(myTFT.tft);
			label_str.print_tft_no_prev_bg(" / "+String(hour)+"P");
		}
	}
	// ----------------------------------------------------------------------------------------------- //

	// Draw current position
	float Ce = find_closest_i(E_now);
	LOG_DEBUG("today_minute: "+String(today_minute)+" | E_now: "+String(E_now)+" | Ce: "+String(Ce));

	// Draw line from stick figure head to current altitude
	int now_x = get_xpos(Ce);
	int now_y = get_ypos(Ce);
	myTFT.tft.drawLine(NOON_X, NOON_Y, now_x, now_y, LIGHTGREY);



	// Show current altitude value
	Shivam_TXT now_str = Shivam_TXT(NOON_X+10,NOON_Y+80, FreeMonoBold14pt7b, 1, WHITE, BG_COLOR);
	now_str.begin(myTFT.tft);
	now_str.print_tft_no_prev_bg("now: "+String(E_now)+"\'");

	// ----------------------- Mark min & max angles ----------------------- //

	int yp_min = get_ypos(find_closest_i(NOON_MIN_ANGLE));
	int yp_max = get_ypos(find_closest_i(NOON_MAX_ANGLE));

	myTFT.tft.fillCircle(get_xpos(find_closest_i(NOON_MAX_ANGLE)), yp_max, 5, ORANGE);
	myTFT.tft.fillCircle(get_xpos(find_closest_i(NOON_MIN_ANGLE)), yp_min, 5, ORANGE);

	draw_dotted_vline(myTFT.tft, /*gap_len*/ 2, /*segment_len*/ 2, /*start_y*/ yp_max-25, /*end_y*/ yp_max+30, /*x_pos*/ get_xpos(find_closest_i(NOON_MAX_ANGLE)), ORANGE);
	draw_dotted_vline(myTFT.tft, /*gap_len*/ 2, /*segment_len*/ 2, /*start_y*/ yp_min-25, /*end_y*/ yp_min+30, /*x_pos*/ get_xpos(find_closest_i(NOON_MIN_ANGLE)), ORANGE);

	// Draw curr-position sun marker
	_SMALL_SUN_(now_x, now_y, YELLOW);
}

void scr_altitude_initialize(Screen* S){
	S->set_func_per_second(do_nothing);
	S->set_func_per_minute(scr_altitude_main);
	S->set_func_per_hour(do_nothing);
	S->set_func_on_enter(scr_altitude_main);
	S->set_func_on_exit(do_nothing);
	S->set_func_on_touch(do_nothing);
}

