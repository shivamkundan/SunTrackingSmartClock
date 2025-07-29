#ifndef SERIAL_IO_H
	#define SERIAL_IO_H
#endif

#include "pico/stdlib.h"

#ifndef ARX_DEBUGLOG_H
	#include <DebugLog.h>
#endif

// Imports
	#ifndef PROGRAM_FUNCS_H
	    #include "program_funcs.h"
	#endif

	#ifndef KEY_MAPS_H
		#include "key_maps.h"
	#endif

	#ifndef HARDWARE_H
	    #include "../Hardware/hardware.h"
	#endif

	#ifndef TIME_FUNCS_H
	    #include "DateTime/time_funcs.h"
	#endif

	#ifndef GLOBALS_H
	    #include "globals.h"
	#endif

// ----------------------------------------------------------------------------- //
void handle_serial_input(uint TimeStamp);
void parse_input(int input,uint TimeStamp);
void print_key_mappings();
void print_sys_info();


bool DIRECT_TS_SET_MODE = false;
bool DIRECT_OFFSET_SET_MODE = false;

#define IS_VALID_TS(TS) (TS>=_MIN_TS_ && TS<=_MAX_TS_)

void short_sys_info(uint TimeStamp){
	LOG_WARN("@"+String(curr_screen)+","+String(OFFSET_T_SECS)+","+get_readable_datetime_full(convert_to_local_time(TimeStamp+OFFSET_T_SECS))+","+String(TimeStamp+OFFSET_T_SECS));
}

bool incr_time_offset(long incr_val){

	long T_new=now()+OFFSET_T_SECS+incr_val;

	// if (T_new>=_MIN_TS_ && T_new<=_MAX_TS_){
	if (IS_VALID_TS(T_new)){
		OFFSET_T_SECS+=incr_val;
		check_dst_offset(now()+OFFSET_T_SECS);
		short_sys_info(now());
		scr_list[curr_screen]->func_on_enter(now()+OFFSET_T_SECS);
		global_on_enter(now()+OFFSET_T_SECS);
	}
	else{
		triple_beep();
		LOG_WARN("OUT OF RANGE!");
	}
	return true;
}

void set_TS(int new_day, uint TimeStamp){
	OFFSET_T_SECS=0;
	uint TS = TimeStamp + TIME_ZONE_DIFF_SECS;
	int today = get_day_of_year(TS);
	int diff_days =  new_day - today;
	incr_time_offset(diff_days*NUM_SECS_IN_DAY);
}

// ------------------------------------------------ //
void set_direct_TS(){
	delay(100);
	// Serial.println("DIRECT_TS_SET_MODE");
	if (Serial.available()>=1){
		int input = Serial.parseInt();
		uint TS = input;

		if (IS_VALID_TS(TS)){
			OFFSET_T_SECS=0;
			setTime(TS);
			delay(200);
			check_dst_offset(TS);
			printDateTime(TS);
		}
		else {
			triple_beep();
			LOG_WARN("OUT OF RANGE!");
		}

		DIRECT_TS_SET_MODE=false;
	}
}

void set_direct_offset(){
	delay(100);
	// Serial.println("DIRECT_OFFSET_SET_MODE");
	if (Serial.available()>=1){
		int input = Serial.parseInt();
		long NEW_OFFSET = input;
		incr_time_offset(NEW_OFFSET);
		DIRECT_OFFSET_SET_MODE=false;
	}
}

// ------------------------------- Input Handling  ----------------------------- //
void handle_serial_input(uint TimeStamp)
/* For serial keyboard input. */
{

	if (RTC_SET_MODE)
		rtc_set_loop();
	else if (DIRECT_TS_SET_MODE){
		set_direct_TS();
	}
	else if (DIRECT_OFFSET_SET_MODE){
		set_direct_offset();
	}
	else if (Serial.available()>=1){
		int input = Serial.parseInt();
		draw_time_travel_frame();

		if (input!=0) // blank message is interpreted as a 0
			parse_input(input, TimeStamp);

		// dump any extraneous input
		while (Serial.available() > 0) Serial.read();
	}
}

void parse_input(int input, uint TimeStamp)
/* Match key to actions */
{

	// For direct screen change
	if (input>=400 && input<427){
		LOG_WARN("setting to "+String(input));
		set_screen(input-400);
		return;
	}

	switch (input){

	case (REBOOT_KEY):{rp2040.reboot(); break;}

	case (SHORT_STATUS_KEY):{
		// LOG_WARN("@"+String(curr_screen)+","+String(OFFSET_T_SECS)+","+get_readable_datetime_full(convert_to_local_time(TimeStamp+OFFSET_T_SECS))+","+String(TimeStamp+OFFSET_T_SECS));
		short_sys_info(TimeStamp);
		break;
	}
	// -------------------------//
	case (SET_TIME_FILM):{LOG_WARN("SET_TIME_FILM");
		time_t t;
		tmElements_t tm;
		tm.Year = 2024-1970;
		tm.Month = 7;
		tm.Day = 11;
		tm.Hour = 7+6;
		tm.Minute = 45;
		tm.Second = 10;
		t = makeTime(tm);
		delay(200);
		// myRTC.set(t);   // use the time_t value to ensure correct weekday is set
		setTime(t);
		check_dst_offset(TimeStamp);
		delay(200);
		break;
	}
	// -------------------------//

	case (RTC_SET_MODE_KEY):{
		RTC_SET_MODE=!RTC_SET_MODE;
		LOG_WARN("RTC_SET_MODE: "+String(RTC_SET_MODE));

		if (RTC_SET_MODE){
			curr_screen=SCREEN_ERROR;
			SWITCH_SCR=true;
		}
		break;
	}
	case (SET_DIRECT_TS_KEY):{ DIRECT_TS_SET_MODE=!DIRECT_TS_SET_MODE; LOG_WARN("@DIRECT_TS_SET_MODE:"+String(DIRECT_TS_SET_MODE)); break;}
	case (SET_DIRECT_OFFSET_KEY):{ DIRECT_OFFSET_SET_MODE=!DIRECT_OFFSET_SET_MODE; LOG_WARN("@DIRECT_OFFSET_SET_MODE:"+String(DIRECT_OFFSET_SET_MODE)); break; }
	// -------------------------//

	case (TOGGLE_MANUAL_MODE): {
		MANUAL_T=!MANUAL_T;
		LOG_WARN("MANUAL_T: "+String(MANUAL_T));
		if (!MANUAL_T) OFFSET_T_SECS = 0;
		break;
	}
	case (TOGGLE_MANUAL_MODE_DECR): {
		MANUAL_T_DECR=!MANUAL_T_DECR;
		LOG_WARN("MANUAL_T_DECR: "+String(MANUAL_T_DECR));
		if (!MANUAL_T_DECR) OFFSET_T_SECS = 0;
		break;
	}

	case (PRINT_INFO_KEY):{
		print_sys_info();
		print_key_mappings();
		break;
	}
	// -------------------------//
	case (NEXT_SCREEN_KEY):{ increment_screen(); break;}
	// -------------------------//
	case (PREV_SCREEN_KEY):{ decrement_screen(); break;}
	// -------------------------//
	case (TOGGLE_MUTE_KEY):{ _TOGGLE_PIEZO_ break;}
	// -------------------------//
	case (TOGGLE_AUTO_BKLT):{ _TOGGLE_AUTO_BL_ break;}
	// -------------------------//
	case (TOGGLE_SCREEN_CYCLE):{
		cycle_screens = !cycle_screens;
		LOG_WARN("cycle_screens: "+String(cycle_screens));
		break;
	}
	// -------------------------//
	case (TOGGLE_GRID):{
		SHOW_GRID=!SHOW_GRID;
		if (!SHOW_GRID)
			SWITCH_SCR=true;
		break;
	}

	case (INCR_INDEX_OFFSET):{
		INDEX_OFFSET+=1;
		SWITCH_SCR=true;
		LOG_WARN("INDEX_OFFSET = "+String(INDEX_OFFSET));
		break;
	}

	case (DECR_INDEX_OFFSET):{
		INDEX_OFFSET-=1;
		SWITCH_SCR=true;
		LOG_WARN("INDEX_OFFSET = "+String(INDEX_OFFSET));
		break;
	}

	case (RESET_INDEX_OFFSET):{
		INDEX_OFFSET=0;
		SWITCH_SCR=true;
		LOG_WARN("INDEX_OFFSET = "+String(INDEX_OFFSET));
		break;
	}

	// Set specific dates
	case(SET_JAN1): {// New year
		// if (IS_VALID_TS(JAN_1_24_00_00_TS)){
		// 	// OFFSET_T_SECS=0;
		// 	// setTime(JAN_1_24_00_00_TS);
		// 	// delay(200);
		// 	// check_dst_offset(JAN_1_24_00_00_TS);
		// 	// printDateTime(JAN_1_24_00_00_TS);

		// 	// if (IS_VALID_TS(newTS)){
		// 	// 	OFFSET_T_SECS = newTS;
		// 	// 	check_dst_offset(newTS);
		// 	// }
		// }
		int diff = JAN_1_24_00_00_TS - TimeStamp;
		LOG_WARN("@diff="+String(diff));
		incr_time_offset(diff);


		break;
	}
	// Set specific dates
	case(SET_JAN1_7AM): {// New year
		int diff = JAN_1_24_07_09_TS - TimeStamp;
		LOG_WARN("@diff="+String(diff));
		incr_time_offset(diff);
		break;
	}
	case(SET_JAN2): {set_TS(JAN_2, TimeStamp); break;}		// Perihelion (closest point)
	case(SET_MAR19):{set_TS(MAR_19,TimeStamp); break;}		// Vernal equinox
	case(SET_JUN20):{set_TS(JUN_20,TimeStamp); break;}		// Summer solstice
	case(SET_JUL5): {set_TS(JUL_5, TimeStamp); break;}		// Aphelion (furthest point)
	case(SET_SEP22):{set_TS(SEP_22,TimeStamp); break;}		// Autumnal equinox
	case(SET_DEC21):{set_TS(DEC_21,TimeStamp); break;}		// Winter solstice

	// -------------------------//
	// Time travel related      //
	// -------------------------//
	case (RESET_OFFSET_T_SECS):{
		OFFSET_T_SECS=0;
		clear_frame=true;
		LOG_WARN("reset");
		check_dst_offset(TimeStamp+OFFSET_T_SECS);
		scr_list[curr_screen]->func_on_enter(TimeStamp+OFFSET_T_SECS);
		break;
	}
	case (TOGGLE_INCR_DECR_OFFSET_T):{
		OFFSET_T_INCR_DECR=!OFFSET_T_INCR_DECR;
		LOG_WARN("OFFSET_T_INCR_DECR: "+String(OFFSET_T_INCR_DECR));
		break;
	}

	case (OFFSET_T_1_MIN):{
		OFFSET_T_INCR_DECR ? incr_time_offset(_MINUTES_(1)) : incr_time_offset(_MINUTES_(-1)); break;}

	case (OFFSET_T_3_MIN):{
		OFFSET_T_INCR_DECR ? incr_time_offset(_MINUTES_(3)) : incr_time_offset(_MINUTES_(-3)); break;}

	case (OFFSET_T_5_MIN):{
		OFFSET_T_INCR_DECR ? incr_time_offset(_MINUTES_(5)) : incr_time_offset(_MINUTES_(-5)); break;}

	case (OFFSET_T_10_MIN):{
		OFFSET_T_INCR_DECR ? incr_time_offset(_MINUTES_(10)) : incr_time_offset(_MINUTES_(-10)); break;}

	case (OFFSET_T_1_HOUR):{
		OFFSET_T_INCR_DECR ? incr_time_offset(_MINUTES_(60)) : incr_time_offset(_MINUTES_(-60)); break;}

	case (OFFSET_T_12_HOUR):{ incr_time_offset(_HOURS_(12)); break;}

	case (OFFSET_T_1_DAY):{
		OFFSET_T_INCR_DECR ? incr_time_offset(_DAYS_(1)) : incr_time_offset(_DAYS_(-1)); break;}

	case (OFFSET_T_3_DAYS):{
		OFFSET_T_INCR_DECR ? incr_time_offset(_DAYS_(3)) : incr_time_offset(_DAYS_(-3)); break;}

	case (OFFSET_T_10_DAYS):{
		OFFSET_T_INCR_DECR ?  incr_time_offset(_DAYS_(10)) : incr_time_offset(_DAYS_(-10)); break;}

	// ------------------ for video making ------------------ //
	case (OFFSET_T_MINUS_1_MIN):{ incr_time_offset(_MINUTES_(-1)); break;}

	case (OFFSET_T_MINUS_3_MIN):{ incr_time_offset(_MINUTES_(-3)); break;}

	case (OFFSET_T_MINUS_5_MIN):{ incr_time_offset(_MINUTES_(-5)); break;}

	case (OFFSET_T_MINUS_10_MIN):{ incr_time_offset(_MINUTES_(-10)); break;}

	case (OFFSET_T_MINUS_1_HOUR):{ incr_time_offset(_MINUTES_(-60)); break;}





	case (OFFSET_T_MINUS_1_DAY):{ incr_time_offset(_DAYS_(-1)); break;}

	case (OFFSET_T_MINUS_3_DAYS):{ incr_time_offset(_DAYS_(-3)); break;}



	case (OFFSET_T_MINUS_10_DAYS):{ incr_time_offset(_DAYS_(-10)); break;}

	// For video making
	case (OFFSET_T_CUSTOM): {incr_time_offset( 10*86400+40*60 ); break;} // 10 days and 40 mins
	case (MINUS_OFFSET_T_CUSTOM): {incr_time_offset( -1*(10*86400+40*60)); break;}
	case (OFFSET_T_CUSTOM2): {incr_time_offset( 10*86400+955 ); break;} // 10 days and 40 mins
	case (OFFSET_T_CUSTOM3): {incr_time_offset( 86636 ); break;} // 1 days	0 hours	3 minutes	56 seconds
	case (OFFSET_T_CUSTOM4): {incr_time_offset( 63*60 ); break;} // 1 hour 3 mins [for scr12 next5]
	// ------------------------------------------------------ //


		default: {
			if (!auto_backlight){
				if (input>=0 && input<=PWM_LIMIT){
					set_pwm_val(input);

					writeEepromInt(input, PWM_LVL_ADDR);
					_EEPROM_COMMIT_

					LOG_WARN("B: "+String(MAX_ADC_VAL-avg_brightness)+", PWM: "+String(PWM_LVL)+"\n");
					delay(1000);
					PWM_LVL=readEepromInt(PWM_LVL_ADDR);
					LOG_WARN("EEPROM PWM_LVL: "+String(PWM_LVL));
				}
			}
			LOG_WARN("input: "+String(input));
		}
	}
}

void print_key_mappings()
/* Shows numerical codes for each serial I/O function. */
{
	Serial.println("============================================================");
	Serial.println("======================= KEY MAPPINGS =======================");
	Serial.println("      READ_BKLT_LVL: "+String(READ_BKLT_LVL));
	Serial.println("     PRINT_INFO_KEY: "+String(PRINT_INFO_KEY));

	Serial.println("TOGGLE_SCREEN_CYCLE: "+String(TOGGLE_SCREEN_CYCLE));
	Serial.println("    TOGGLE_MUTE_KEY: "+String(TOGGLE_MUTE_KEY));
	Serial.println("   TOGGLE_AUTO_BKLT: "+String(TOGGLE_AUTO_BKLT));
	Serial.println("        TOGGLE_GRID: "+String(TOGGLE_GRID));
	Serial.println("    PREV_SCREEN_KEY: "+String(PREV_SCREEN_KEY));
	Serial.println("    NEXT_SCREEN_KEY: "+String(NEXT_SCREEN_KEY));
	Serial.println("     PRINT_TEMP_ARR: "+String(PRINT_TEMP_ARR));
	Serial.println("    PRINT_HUMID_ARR: "+String(PRINT_HUMID_ARR));
	Serial.println("---");
	Serial.println("  INCR_INDEX_OFFSET: "+String(INCR_INDEX_OFFSET));
	Serial.println("  DECR_INDEX_OFFSET: "+String(DECR_INDEX_OFFSET));
	Serial.println(" RESET_INDEX_OFFSET: "+String(RESET_INDEX_OFFSET));
	Serial.println();
	Serial.println("   RTC_SET_MODE_KEY: "+String(RTC_SET_MODE_KEY));
	Serial.println();

	Serial.println("-----------------------------------------------------");
	Serial.println("----------------- Time Travel------------------------");
	Serial.println("      RESET_OFFSET_T_SECS: "+String(RESET_OFFSET_T_SECS));
	Serial.println("TOGGLE_INCR_DECR_OFFSET_T: "+String(TOGGLE_INCR_DECR_OFFSET_T));
	Serial.println("           OFFSET_T_1_MIN: "+String(OFFSET_T_1_MIN));
	Serial.println("           OFFSET_T_3_MIN: "+String(OFFSET_T_3_MIN));
	Serial.println("           OFFSET_T_5_MIN: "+String(OFFSET_T_5_MIN));
	Serial.println("          OFFSET_T_10_MIN: "+String(OFFSET_T_10_MIN));
	Serial.println("          OFFSET_T_1_HOUR: "+String(OFFSET_T_1_HOUR));
	Serial.println("           OFFSET_T_1_DAY: "+String(OFFSET_T_1_DAY));
	Serial.println("         OFFSET_T_10_DAYS: "+String(OFFSET_T_10_DAYS));
}

void print_sys_info()
/* Print program information to serial monitor. */
{
	Serial.println();
	Serial.println("============================================================");
	Serial.println("======================== Prog Info =========================");
	Serial.println("program_start_time: "+String(get_readable_datetime(convert_to_local_time(program_start_time))));
	Serial.println("OFFSET_T_SECS: "+String(OFFSET_T_SECS));
	Serial.println("OFFSET_T_INCR_DECR: "+String(OFFSET_T_INCR_DECR));
	Serial.println("---------------------------------------------------------");
	Serial.println("   curr_screen: "+String(curr_screen));
	Serial.println("   screen name: "+String(scr_list[curr_screen]->name));
	Serial.println("---------------------------------------------------------");
	Serial.println("    PIEZO_MUTE: "+String(PIEZO_MUTE));
	Serial.println("auto_backlight: "+String(auto_backlight));
	Serial.println(" cycle_screens: "+String(cycle_screens));
	Serial.println("---------------------------------------------------------");
	Serial.println("Avg brightness: "+String(MAX_ADC_VAL-avg_brightness));
	Serial.println("           PWM: "+String(PWM_LVL));
	Serial.println("---------------------------------------------------------");
	Serial.println("  RTC_SET_MODE: "+String(RTC_SET_MODE));
	Serial.println();
}