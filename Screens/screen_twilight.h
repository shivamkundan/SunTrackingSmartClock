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

#ifndef TIME_FUNCS_H
	#include "../DateTime/time_funcs.h"
#endif

#define YY yy-BASE_YEAR
#define _MM mm-1
#define _DD (day_num-1)
#define _ND NUM_ITEMS_PER_DAY

#define _Y_TOP 100
#define _Y_BOTTOM  _Y_TOP+100

// to retrieve event times
#define _LOAD_VALS_ {\
	int midnight_tomorrow = all_years[YY][_MM][(day_num)*_ND];\
	int midnight, astro_dawn, nautical_dawn, first_light, sunrise, solar_noon,\
		sunset, last_light, nautical_dusk, astro_dusk;\
		\
\}

// -----------------------------------------------------------------
void display_durations(int midnight, int astro_dawn, int nautical_dawn, int first_light, int sunrise, int solar_noon, int sunset, int last_light, int nautical_dusk, int astro_dusk, int midnight_tomorrow, int zero_line_y_pos){
	// -------------------------------------------------------------
	// Show absolute values

	// Str object for the middle string - total daylight
	Shivam_TXT day_len_TXT = Shivam_TXT(5, zero_line_y_pos+45, FreeMonoBold12pt7b, 1, CYAN, BG_COLOR);
	day_len_TXT.begin(myTFT.tft);

	// // Str object for both twilight strings
	// Shivam_TXT day_len_TXT2 = Shivam_TXT(5, 290, FreeMonoBold9pt7b, 1, LIGHTGREY, BG_COLOR);
	// day_len_TXT2.begin(myTFT.tft);

	uint8_t m,s;
	uint16_t h;


	// Calculate daylight + twilight durations
	int total_daylight    = sunset - sunrise;
	int total_light_civil = last_light - first_light;
	int total_light_naut  = nautical_dusk - nautical_dawn;
	int total_light_astro = astro_dusk - astro_dawn;

	String DL;

	// Show total daylight in the middle i.e., civil twilight
	secondsToHMS(total_daylight,h,m,s);
	DL=String(h)+"hr "+String(m)+"min";
	day_len_TXT.print_tft_middle(DL);

	day_len_TXT.set_y_pos(228);
	day_len_TXT.change_font(FreeMonoBold9pt7b);
	day_len_TXT.change_color(LIGHTGREY);

	secondsToHMS(total_light_civil,h,m,s);
	DL=String(h)+"hr "+String(m)+"min";
	day_len_TXT.increment_y_pos(28);
	day_len_TXT.print_tft_middle(DL);

	secondsToHMS(total_light_naut,h,m,s);
	DL=String(h)+"hr "+String(m)+"min";
	day_len_TXT.increment_y_pos(28);
	day_len_TXT.print_tft_middle(DL);

	// myTFT.tft.setRotation(0);
	secondsToHMS(total_light_astro,h,m,s);
	DL=String(h)+"hr "+String(m)+"min";
	day_len_TXT.increment_y_pos(28);
	// day_len_TXT.set_y_pos(28);
	day_len_TXT.print_tft_middle(DL);
	// myTFT.tft.setRotation(3);



	// // Before morning twilight
	// secondsToHMS(first_light-midnight,h,m,s);
	// String LEN1=String(h)+"hr "+String(m)+"min";
	// day_len_TXT2.print_tft(LEN1);

	// // After evening twilight
	// secondsToHMS(midnight_tomorrow-last_light,h,m,s);
	// String LEN2=String(h)+"hr "+String(m)+"min";
	// day_len_TXT2.print_tft_ralign(LEN2);
}


// ypos+0 ->
// zero_line_y_pos max = 165 -> jun 19
// zero_line_y_pos min = 107 -> jan 2

// ypos+30 ->
// zero_line_y_pos max = 192 -> jun 19
// zero_line_y_pos min = 139 -> jan 2

// ypos+15 ->
// zero_line_y_pos max = 177 -> jun 19
// zero_line_y_pos min = 124 -> jan 2



void draw_all_vlines(int astro_dawn, int nautical_dawn, int first_light, int sunrise, int solar_noon, int sunset, int last_light, int nautical_dusk, int astro_dusk, int zero_line_y_pos){


	// // calculate x positions for dividers
	// uint xpos_first_light =   _GET_POS_ (first_light);
	// uint xpos_last_light =    _GET_POS_ (last_light);

	// uint xpos_sunsrise =      _GET_POS_ (sunrise);
	// uint xpos_sunset =        _GET_POS_ (sunset);

	// uint xpos_nautical_dawn = _GET_POS_ (nautical_dawn);
	// uint xpos_nautical_dusk = _GET_POS_ (nautical_dusk);

	// uint xpos_astro_dawn =    _GET_POS_(astro_dawn);
	// uint xpos_astro_dusk =    _GET_POS_(astro_dusk);

	int incr=25;
	int top_offset=-15;
	int bottom_offset=15;

	// uint xpos_dawn[]={xpos_sunsrise, xpos_first_light, xpos_nautical_dawn, xpos_astro_dawn};
	// uint xpos_dusk[]={xpos_sunset,   xpos_last_light,  xpos_nautical_dusk, xpos_astro_dusk};

	int lengths_dawn[]={0,sunrise-first_light, first_light-nautical_dawn, nautical_dawn- astro_dawn};
	int lengths_dusk[]={0,last_light-sunset,   nautical_dusk-last_light,  astro_dusk-nautical_dusk};

	int times_dawn[]={sunrise, first_light, nautical_dawn, astro_dawn};
	int times_dusk[]={sunset, last_light, nautical_dusk, astro_dusk};

	int total_twilight_dawn = 0;
	int total_twilight_dusk = 0;

	for (int N=0;N<4;N++){
		int start_y = top_offset +  zero_line_y_pos - (N+1)*incr;
		int end_y = bottom_offset + zero_line_y_pos + (N+1)*incr;

		uint xp_dawn = _GET_POS_(times_dawn[N]);
		uint xp_dusk = _GET_POS_(times_dusk[N]);

		draw_dotted_vline(/*tft*/ myTFT.tft, /*gap_len*/5, /*segment_len*/1, /*start_y*/start_y, /*end_y*/end_y, /*x_pos*/xp_dawn, /*color*/ WHITE);
		draw_dotted_vline(/*tft*/ myTFT.tft, /*gap_len*/5, /*segment_len*/1, /*start_y*/start_y, /*end_y*/end_y, /*x_pos*/xp_dusk, /*color*/ WHITE);

		uint8_t m,s;
		uint16_t h;


		// Print dusk and dawn length
		// Shivam_TXT TGREY_TXT = Shivam_TXT(xpos_dawn[N]+10, end_y-5, Font4x5Fixed, 2, WHITE, BG_COLOR);
		Shivam_TXT TGREY_TXT = Shivam_TXT(xp_dawn+10, end_y-5, Font4x5Fixed, 2, WHITE, BG_COLOR);
		TGREY_TXT.begin(myTFT.tft);

		// Display lengths of dusks and dawns
		if (N>0) {
			secondsToHMS(lengths_dawn[N],h,m,s);
			String DAWN_LEN=String(m)+"min";
			total_twilight_dawn+=lengths_dawn[N];

			secondsToHMS(lengths_dusk[N],h,m,s);
			String DUSK_LEN=String(m)+"min";
			total_twilight_dusk+=lengths_dusk[N];

			TGREY_TXT.print_tft_no_prev_bg(DAWN_LEN);
			TGREY_TXT.print_tft_ralign2(DUSK_LEN,xp_dusk-3,/*clear_bg*/ false);
		}

		TGREY_TXT.set_y_pos(start_y);
		TGREY_TXT.print_tft_no_prev_bg(String(get_readable_time(convert_to_local_time(times_dawn[N]))));
		TGREY_TXT.print_tft_ralign2(String(get_readable_time(convert_to_local_time(times_dusk[N]))),xp_dusk-3,/*clear_bg*/ false);
	}

	uint8_t m,s;
	uint16_t h;
	uint8_t m2,s2;
	uint16_t h2;

	secondsToHMS(total_twilight_dawn,h,m,s);

	secondsToHMS(total_twilight_dusk,h2,m2,s2);

	int total_twilight=total_twilight_dawn+total_twilight_dusk;
	int total_daylight=sunset-sunrise;
	int total_nighttime=NUM_SECS_IN_DAY-total_daylight-total_twilight;

	// Show dawn and dusk lengths
	Shivam_TXT txtstr = Shivam_TXT(5, 45, Font4x5Fixed, 2, ORANGE, BG_COLOR);
	txtstr.begin(myTFT.tft);
	txtstr.print_tft_middle(String(h)+":"+String(m)+" + "+String(h2)+":"+String(m2));

	// Show total twilight length for today
	secondsToHMS(total_twilight,h,m,s);
	// secondsToHMS(total_twilight_dusk,h,m,s);
	secondsToHMS(total_twilight,h,m,s);

	txtstr.change_font(FreeMonoBold9pt7b);
	txtstr.set_font_size(1);
	txtstr.increment_y_pos(25);
	txtstr.change_color(CYAN);
	txtstr.print_tft_middle(String(h)+"hr "+String(m)+"min");

	uint xp_solar_noon = _GET_POS_(solar_noon);
	Shivam_TXT NOON_TXT = Shivam_TXT(xp_solar_noon, _Y_TOP, Font4x5Fixed, 2, WHITE, BG_COLOR);
	NOON_TXT.begin(myTFT.tft);
	NOON_TXT.print_tft_centered(String(get_readable_time(convert_to_local_time(solar_noon))),xp_solar_noon-10,xp_solar_noon+10);
}


void scr_twilight_main(time_t TimeStamp)
/* Draw both elevation and azimuth diagrams */
{
	time_t localTime = convert_to_local_time(TimeStamp);

	myTFT.clear_screen(BG_COLOR);

	_PRINT_TITLE_SMALL_("TWILIGHT");

	// LOG_DEBUG("_Y_TOP,_Y_BOTTOM: "+String(_Y_TOP)+", "+String(_Y_BOTTOM));

	// myTFT.tft.fillRect(0,_Y_TOP,SCREEN_W,_Y_BOTTOM-_Y_TOP,LIGHTBLACK);


	// Retrieve current date/time
	int day_num=get_day_of_month(localTime);
	int mm=convert_to_tmelements(localTime).Month;
	int yy=convert_to_tmelements(localTime).Year+UNIX_START_YEAR;
	uint16_t today_minute=get_minute_of_day(localTime);

	// Retrieve min and max elevation
	int maxVal=MAX_ELEV_ARRAY[mm-1][day_num-1];
	int minVal=MIN_ELEV_ARRAY[mm-1][day_num-1];

	// This is the line for horizon (i.e, 0 deg elevation)
	int zero_line_y_pos=(int) custom_map(0,minVal,maxVal,_Y_BOTTOM,_Y_TOP);
	// LOG_DEBUG("before zero_line_y_pos: "+String(zero_line_y_pos));

	int new_starty=_Y_TOP+(SCREEN_H/2-zero_line_y_pos)+15;

	// Draw elevation diagram
	zero_line_y_pos = draw_elevation_diagram (day_num,mm,yy,today_minute,new_starty,new_starty+100);
	draw_x_labels(zero_line_y_pos);

	// LOG_DEBUG("after zero_line_y_pos: "+String(zero_line_y_pos));

	// -------------------------------------------------------------
	// Calc info
	int now_x_pos=custom_map (today_minute,0,NUM_MINS_IN_DAY-1,0,SCREEN_W-1);

	// Retrieve event times
	int midnight_tomorrow = all_years[YY][_MM][(day_num)*_ND];
	int midnight, astro_dawn, nautical_dawn, first_light, sunrise, solar_noon,
		sunset, last_light, nautical_dusk, astro_dusk;
	get_today_events(yy, mm, day_num, midnight, astro_dawn, nautical_dawn, first_light,
		sunrise, solar_noon, sunset, last_light, nautical_dusk, astro_dusk);

	// Calculate
	int elapsed_light=TimeStamp-first_light;

	// Show absolute values
	display_durations(midnight, astro_dawn, nautical_dawn, first_light, sunrise, solar_noon, sunset, last_light, nautical_dusk, astro_dusk, midnight_tomorrow, zero_line_y_pos);

	draw_all_vlines(astro_dawn, nautical_dawn, first_light, sunrise, solar_noon, sunset, last_light, nautical_dusk, astro_dusk, zero_line_y_pos);

}

void scr_twilight_per_minute(uint TimeStamp){
	scr_twilight_main(TimeStamp);
}

void scr_twilight_on_enter(uint TimeStamp){
	scr_twilight_main(TimeStamp);
}

void scr_twilight_initialize(Screen* S){
	S->set_func_per_second(do_nothing);
	S->set_func_per_minute(scr_twilight_per_minute);
	S->set_func_per_hour(do_nothing);
	S->set_func_on_enter(scr_twilight_on_enter);
	S->set_func_on_exit(do_nothing);
	S->set_func_on_touch(do_nothing);

	S->show_power_info=false;
	// S->show_mw_icon=false;
	// S->show_icons=false;
}