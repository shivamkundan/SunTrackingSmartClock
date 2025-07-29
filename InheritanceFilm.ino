#include "libs.h"
#include "pico/stdlib.h"
#include "hardware/divider.h"

// https://arduino-pico.readthedocs.io/en/latest/sdk.html

// #define MANUAL_T // Time mode


long t_start;
long t_end;
uint T1=0;
uint T2=0;

// ----------------------------------------------------------- //
void setup(){
	Serial.begin(115200);

	// LOG_SET_LEVEL(DebugLogLevel::LVL_INFO); // 0: NONE, 1: ERROR, 2: WARN, 3: INFO, 4: DEBUG, 5: TRACE
	LOG_SET_LEVEL(DebugLogLevel::LVL_WARN); // 0: NONE, 1: ERROR, 2: WARN, 3: INFO, 4: DEBUG, 5: TRACE

	init_hardware();

	// --------------- for video making -------------- //
	if (digitalRead(SLIDE_SWITCH_PIN)){
		curr_screen=SCREEN_GREEN;
		set_pwm_val(3000);
	}
	// if (curr_screen==1)
	// 	set_pwm_val(3000);
	// ----------------------------------------------- //

	myTFT.clear_screen(BG_COLOR);

	// Init custom string objects
	init_TXTs(myTFT.tft);

	// time_t t;
	// tmElements_t tm;
	// tm.Year = 2024-UNIX_START_YEAR;
	// tm.Month = 7;
	// tm.Day = 11;
	// tm.Hour = 7+6;
	// tm.Minute = 45;
	// tm.Second = 10;
	// t = makeTime(tm);
	// delay(200);
	// myRTC.set(t);   // use the time_t value to ensure correct weekday is set
	// delay(200);

	// Initialize timestamp
	TimeStamp=now();


	if (TimeStamp<_MIN_TS_ || TimeStamp>_MAX_TS_)
		curr_screen=SCREEN_ERROR;

	program_start_time=TimeStamp;
	init_previous_vals(TimeStamp);

	delay(500);
	check_dst_offset(TimeStamp);

	LOG_INFO("\n||||||||||||||||||||||||||||||||||||||||||||||\nprogram_start_time: "+get_readable_datetime(convert_to_local_time(program_start_time)));

	// Init screens
	init_screens();

	// Initialize global stuff
	global_on_hour(TimeStamp);
	global_on_minute(TimeStamp);

	// Initialize screen stuff
	scr_list[curr_screen]->func_on_enter(TimeStamp);
	global_on_enter(TimeStamp);

	t_start=millis();
	t_end=t_start;

	// // delay(2000);




	// LOG_INFO("\n------------ EEPROM stored stettings ------------");
	// LOG_INFO("auto_backlight: "+String(auto_backlight));
	// LOG_INFO("PIEZO_MUTE: "+String(PIEZO_MUTE));
	// LOG_INFO("PWM_LVL: "+String(PWM_LVL));
	// LOG_INFO("EEPROM PWM_LVL: "+String(readEepromInt(PWM_LVL_ADDR)));
	// LOG_INFO();

	// LOG_INFO("Sizes:");
	// // LOG_INFO("char:    "+String(sizeof(char)));
	// // LOG_INFO("bool:    "+String(sizeof(bool)));
	// // LOG_INFO("uint8_t: "+String(sizeof(uint8_t)));
	// LOG_INFO("int:     "+String(sizeof(int)));
	// LOG_INFO("uint16_t:"+String(sizeof(uint16_t)));
	// LOG_INFO("uint:    "+String(sizeof(uint)));
	// LOG_INFO("uint32_t:"+String(sizeof(uint32_t)));
	// LOG_INFO("int32_t:"+String(sizeof(int32_t)));
	// LOG_INFO("time_t:  "+String(sizeof(time_t)));
	// LOG_INFO("float:   "+String(sizeof(float)));
	// // LOG_INFO("double:  "+String(sizeof(double)));

	// Init temp/humid sensor and arrays
	temp_humid_manager(TimeStamp-61, &sht31);
	temp_humid_manager(TimeStamp, &sht31);

	// For preventing erroneous touch at startup
	add_alarm_in_ms(3*1000, init_touch, NULL, false);

	// print_mem_stats();
}

// ---------------------------------------- //
void loop(){



	#ifdef MANUAL_T
		// Update time manually/
		if (t_end-t_start>=50){
			TimeStamp+=1;
		}
	#endif

	#ifndef MANUAL_T
		// Update using rtc
		TimeStamp=now();
	#endif

	if (TimeStamp<_MIN_TS_ || TimeStamp>_MAX_TS_){
		curr_screen=SCREEN_ERROR;
		RTC_SET_MODE=true;
		// LOG_DEBUG(get_readable_datetime(TimeStamp));
	}

	unsigned long adj_TS=TimeStamp+OFFSET_T_SECS;

	// TS control
	touch_controller(adj_TS);

	// Btn control
	push_button_controller(TimeStamp);

	// Check for serial input
	handle_serial_input(TimeStamp);

	// Check for initialize signal
	if (SWITCH_SCR){ SWITCH_SCR=false; switch_screen(adj_TS);}

	// Cycle screens
	if (cycle_screens) screen_cycle();

	// Used only for time travel
	if (clear_frame) reset_time_travel_frame(TimeStamp);

	// Some screens need immediate interaction, i.e., can't wait for ss!=ss
	scr_list[curr_screen]->func_on_touch(adj_TS);

	// Main loop
	if (TimeStamp!=prev_timestamp){
		t_start=millis();

		// These vars save current time vals
		uint16_t DD=1; char am_pm; bool AM=false;
		uint8_t HH,MM,ss;
		get_individual_time(convert_to_local_time(adj_TS), DD, HH, MM, ss, AM);
		prev_timestamp=TimeStamp;

		if (DD!=prev_DD)
			LOG_DEBUG("New day");

		if (HH!=prev_HH){
			single_beep();
			scr_list[curr_screen]->func_per_hour(adj_TS);
			global_on_hour(adj_TS);
		}
		if (MM!=prev_MM){
			scr_list[curr_screen]->func_per_minute(adj_TS);
			global_on_minute(adj_TS);
		}
		if (ss!=prev_ss){  // A bit redundant but just in case milli/micro seconds are counted in timestamp
			touch_en=digitalRead(TOUCH_EN_PIN);
			scr_list[curr_screen]->func_per_second(adj_TS);
			global_on_second(adj_TS);
		}

		if (SHOW_GRID)
			draw_grid(BG_GRID_SIZE);

		// Show marker if there is a time offset, i.e. not the live time
		draw_time_travel_frame();
		update_previous_vals(DD, HH, MM, ss);

	}

	t_end=millis();

	T2=millis();

	if (T2-T1>99){
		if (auto_backlight)
			backlight_manager();
		else
			read_photocell();
		T1=millis();
	}

}