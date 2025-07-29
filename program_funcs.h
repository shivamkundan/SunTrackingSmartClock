#ifndef PROGRAM_FUNCS_H
	#define PROGRAM_FUNCS_H
#endif

#ifndef TIME_FUNCS_H
	#include "DateTime/time_funcs.h"
#endif

#ifndef STRING_DEFS_H
    #include "string_defs.h"
#endif

#ifndef GLOBALS_H
    #include "globals.h"
#endif

#ifndef SCREENS_H
    #include "Screens/screens.h"
#endif

#ifndef HARDWARE_H
	#include "Hardware/hardware.h"
#endif

#ifndef COLORS_H
    #include "colors.h"
#endif

#ifndef BITMAPS_H
    #include "Bitmaps/bitmaps.h"
#endif

// #ifndef SERIAL_IO_H
//     #include "SerialIO/serial_io.h"
// #endif

#include <math.h>       /* log */


// For time travel
#define FRAME_THICKNESS 1
bool TOUCH_INIT=true;  //This is to prevent erroneous touch at startup

// ------------------------------------- //
void switch_screen(time_t TS);
// ------------------------------------- //
void display_small_ss(time_t TS);
// ------------------------------------- //
void backlight_manager();
// ------------------------------------- //
void global_on_second(time_t TS);
void global_on_minute(time_t TS);
void global_on_hour(time_t TS);
void global_on_enter(time_t TS);
// ------------------------------------- //
void increment_screen();
void decrement_screen();
// ------------------------------------- //
void touch_controller();
// ------------------------------------- //
void draw_time_travel_frame();
void reset_time_travel_frame(time_t TS);
// ------------------------------------- //
void icon_manager();


// ----------------------------------------------------------- //
// ----------------------------------------------------------- //
void switch_screen(time_t TS)
/* Prepare new screen */
{
	LOG_TRACE("");
	touch_countdown=25;  // debounce
	scr_list[prev_screen]->func_on_exit(TS);
	// myTFT.clear_screen(BG_COLOR);
	LOG_DEBUG("entering screen#: "+String(curr_screen)+" | "+scr_list[curr_screen]->name);
	scr_list[curr_screen]->func_on_enter(TS);
	global_on_enter(TS);
}

// ---------------------------------------- //
void display_small_ss(time_t TS)
/* Shows current time in small font */
{
	// Print current time
	char buf[20];
	time_t localTime = convert_to_local_time(TS);
	sprintf(buf, "%02d",get_curr_seconds(localTime));
	sec_str_small.print_tft_tight(String(buf));

	// This is updated every second
	// if (OFFSET_T_SECS>0)
	if (!(isAM(localTime))){
		// myTFT.tft.fillCircle(476,2,2,ORANGE);
		SHOW_PM=true;
	}
	else {
		SHOW_PM=false;
	}
}

void display_small_HH_MM(time_t TS)
/* Show current hours and minutes */
{
	LOG_TRACE("");
    // These vars save current time vals
    uint16_t _DDD=1;
    uint8_t _HHH, _MMM, _sss;
    char _am_pm;
    bool _AMM=false;

    get_individual_time(TS, _DDD, _HHH, _MMM, _sss, _AMM);

    char buf[20];
    sprintf(buf, "%02d:%02d",_HHH,_MMM);
    timestr_small.print_tft(buf);

    time_t localTime = convert_to_local_time(TS);
    if (!_AMM)
        myTFT.tft.fillCircle(476,2,2,ORANGE);
}
// ---------------------------------------- //
void backlight_manager()
/* Read ambient light level and adjust lcd backlight automatically */
{
	LOG_TRACE("");
	read_photocell();
	if (delay_countdown==0){
		for (uint8_t i=0;i<numBrightnessReadings;i++)
			// if (abs(readings[numReadings-1]- readings[i]) >= 7){
			if (abs(brightness_readings[numBrightnessReadings-1]- brightness_readings[i]) >= 6){
				delay_countdown = DELAY_TIME;
				set_auto_light_lvl();
				set_pwm_val(PWM_LVL);
			}
	}
	else
		delay_countdown-=1;
}

// ---------------------------------------- //
void global_on_second(time_t TS)
/* Displays (large) seconds and debug info. */
{
	if (scr_list[curr_screen]->name=="DAYLEN")
		LOG_DEBUG("");

	// Display seconds (switch is faster than if else)
	switch(scr_list[curr_screen]->time_disp){
		case (LARGE):{
			display_large_ss(convert_to_local_time(TS)); break;}
		case (MEDIUM):{
			 display_small_ss(convert_to_local_time(TS)); break;}
		case (SMALL):{
			 display_small_ss(convert_to_local_time(TS)); break;}
	}

	// Display debug info
	if (scr_list[curr_screen]->show_power_info)
		current_str.print_tft(print_current_byref(&ina219));

	// Display backlight pwm level and ambient brightness reading
	if (scr_list[curr_screen]->show_backlight_info)
		pwm_str.print_tft_ralign(String(MAX_ADC_VAL-avg_brightness)+" "+String(PWM_LVL));

	// Show status icons
	if (scr_list[curr_screen]->show_icons)
		icon_manager();
}

void global_on_minute(time_t TS)
/* Executes at each new minute. */
{
	LOG_TRACE("");
	temp_humid_manager(TS,&sht31);

	LOG_DEBUG("TS: "+get_readable_datetime(TS));
	LOG_DEBUG("curr_screen: "+String(curr_screen));
	LOG_DEBUG("scr_list[curr_screen]->time_disp: "+String(scr_list[curr_screen]->time_disp));
	// Show HH:MM
	switch(scr_list[curr_screen]->time_disp){
		case (LARGE):{
			display_large_HH_MM(convert_to_local_time(TS));
			display_day_date(convert_to_local_time(TS));
			break;}
		case (MEDIUM):{
			 display_small_HH_MM(convert_to_local_time(TS));
			 display_day_date(convert_to_local_time(TS));
			 break;}
		case (SMALL):{
			 display_small_HH_MM(convert_to_local_time(TS));
			 display_day_date_small(convert_to_local_time(TS));
			 break;}
	}

	// Display screen#
	if (scr_list[curr_screen]->show_scr_num)
		scr_num_str.print_tft(String(curr_screen));
}

void global_on_hour(time_t TS)
/* Executes at each new clock hour. */
{
	return;
}

void global_on_enter(time_t TS)
/* Executed once on entering screen. */
{
	LOG_TRACE("");
	SHOW_PM=false;
	global_on_second(TS);
	global_on_minute(TS);
	global_on_hour(TS);
}

// ---------------------------------------- //
void increment_screen()
/* Circular increment */
{
	LOG_TRACE("");
	prev_screen=curr_screen;
	if (curr_screen<NUM_REG_SCREENS-1)
		curr_screen+=1;
	else if (curr_screen==NUM_REG_SCREENS-1)
		curr_screen=0;
	SWITCH_SCR=true;

	// if (prev_screen==0 && curr_screen==1)
	// 	set_pwm_val(3000);

}

void decrement_screen()
/* Circular decrement */
{
	LOG_TRACE("");
	prev_screen=curr_screen;
	curr_screen==0 ? curr_screen=NUM_REG_SCREENS-1 : curr_screen-=1;
	SWITCH_SCR=true;
}

void set_screen(uint8_t new_scr_num){
	prev_screen=curr_screen;
	curr_screen=new_scr_num;
	SWITCH_SCR=true;
}

void screen_cycle()
/* Cycles screens every SCR_CHANGE_TIME seconds */
{
	scr_cycle_currentMillis=millis();
	if (scr_cycle_currentMillis-scr_cycle_prevMillis > SCR_CHANGE_TIME){
		scr_cycle_prevMillis=scr_cycle_currentMillis;
		increment_screen();
	}
}

// ---------------------------------------- //

void menu_touch_controller(){
	LOG_TRACE("");
	if (MIDDLE_BUTTON)
	{
		prev_screen=curr_screen;
		SWITCH_SCR=true;

		if (curr_screen==SCREEN_MENU || curr_screen==SCREEN_BACKLIGHT)
			curr_screen=return_screen; // restore previous screen
		else if (curr_screen==SCREEN_MENU_SCREENS || curr_screen==SCREEN_MENU_SETTINGS || curr_screen==SCREEN_MENU_INFO)
			curr_screen=SCREEN_MENU;

	}
}

void on_valid_touch(time_t TS){
	LOG_TRACE("\n");


	if (curr_screen<NUM_REG_SCREENS){

		if (LEFT_BUTTON)
			decrement_screen();
		else if (RIGHT_BUTTON)
			increment_screen();
		else if (MIDDLE_BUTTON){
				prev_screen=curr_screen;
				return_screen=curr_screen;
				curr_screen=SCREEN_MENU;
				SWITCH_SCR=true;
			}
	}
	else {
		menu_touch_controller();
	}

	// // For visualizing the touch point
	// if (SHOW_TOUCH_SQUARE)
	// 	show_touch_point(p.x, p.y, p.z,myTFT.tft);
}

int64_t init_touch(alarm_id_t id, void *user_data)
/* This is to prevent erroneous touch at startup */
{
	TOUCH_INIT=true;
	return 0;
}
void touch_controller(time_t TS)
/* Manages resistive touch panel input: global ax and global ay is updated. */
{
	LOG_TRACE("");
	if (touch_countdown==0 && touch_en && TOUCH_INIT){

		// Get touch point
		TSPoint p = ts.getPoint();

		// Translate TS co-ords to current LCD orientation
		translate_coords(p.x,p.y);


		if (_VALID_TOUCH_){
			touch_countdown=5;  // debounce

			if (curr_screen==SCREEN_BACKLIGHT) slider();
			else LOG_DEBUG("----------> (p.z): "+String(p.z)+", ax: "+String(ax)+", ay: "+String(ay));

			// In case of accidental backlight off
			if (PWM_LVL==0){ _RESTORE_BACKLIGHT_}
			else
				on_valid_touch(TS);

		}
		else
			ax=ay=-1;

	}

	// Debouncing
	if (touch_countdown>0){touch_countdown-=1; delay(10);}
}

void push_button_controller(uint TimeStamp){
/*  */
	if (push_btn_countdown==0){
		// if (digitalRead(BTN1_PIN==LOW)){
		if (digitalRead(BTN1_PIN)==LOW){
			LOG_DEBUG("BTN1_PIN");
			OFFSET_T_SECS=0;
			// clear_frame=true;
			check_dst_offset(TimeStamp+OFFSET_T_SECS);
			SWITCH_SCR=true;
			push_btn_countdown=PUSH_BTN_DEBOUNCE_T;  // debounce
		}
	}

	// Debouncing
	if (push_btn_countdown>0){push_btn_countdown-=1; delay(10);}
}

// ---------------------------------------- //
void draw_time_travel_frame()
/* Shows a visual marker if datetime!=now, i.e. not the live time */
{
	// Future dates
	if (OFFSET_T_SECS>0){
		for (int i=0;i<FRAME_THICKNESS;i++)
			myTFT.tft.drawRect(i,  i, SCREEN_W-i,   SCREEN_H-i,   FUTURE_FRAME_COLOR);
	}

	// Past dates
	else if (OFFSET_T_SECS<0){
		for (int i=0;i<FRAME_THICKNESS;i++)
			myTFT.tft.drawRect(0,  0, SCREEN_W,   SCREEN_H,   PAST_FRAME_COLOR);
	}

	// PM indicator
	if (SHOW_PM && (scr_list[curr_screen]->time_disp==SMALL || scr_list[curr_screen]->time_disp==MEDIUM))
		myTFT.tft.fillCircle(476,2,2,ORANGE);

}

void reset_time_travel_frame(time_t TS)
/* Erase frame if datetime==now */
{
	LOG_TRACE("");
		clear_frame=false;
		myTFT.tft.drawRect(0,  0, SCREEN_W,   SCREEN_H,   BG_COLOR);
		unsigned long adj_TS=TS+OFFSET_T_SECS;
		init_previous_vals(adj_TS);
		global_on_minute(adj_TS);
		global_on_hour(adj_TS);
}

// ---------------------------------------- //
void icon_manager()
/* Display status icons */
{
	if (scr_list[curr_screen]->show_icons){

		// Mute icon
		myTFT.tft.drawBitmap(ICON_STRIP_XPOS,    SCREEN_H-MUTE_ICON_H,   bitmap_mute,   MUTE_ICON_W,   MUTE_ICON_H, 	(PIEZO_MUTE ? STATUS_ICON_COLOR : BG_COLOR));

		// Cycle screens icon
		myTFT.tft.drawBitmap(ICON_STRIP_XPOS+30, SCREEN_H-CYCLE_ICON_H,  bitmap_cycle,  CYCLE_ICON_W,  CYCLE_ICON_H,  (cycle_screens ? STATUS_ICON_COLOR : BG_COLOR));

		// Auto backlight icon
		myTFT.tft.drawBitmap(ICON_STRIP_XPOS+60, SCREEN_H-AUTOBG_ICON_H, bitmap_autobg, AUTOBG_ICON_W, AUTOBG_ICON_H, (!auto_backlight ? STATUS_ICON_COLOR : BG_COLOR));

	}
}
