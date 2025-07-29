#ifndef HARDWARE_H
	#define HARDWARE_H
#endif

// Imports
	#ifndef TS_PARAMS_H
		#include "ts_params.h"
	#endif

	#ifndef TFT_LCD_H
		#include "tft_lcd.h"
	#endif

	#ifndef SENSOR_CURRENT_H
		#include "sensor_current.h"
	#endif

	#ifndef PIEZO_STUFF_H
		#include "piezo_stuff.h"
	#endif

	#ifndef PUSH_BUTTONS_H
		#include "push_buttons.h"
	#endif

	#ifndef SENSOR_TEMP_HUMID_H
		#include "sensor_temp_humid.h"
	#endif

	#ifndef SLIDE_SWITCHES_H
		#include "slide_switches.h"
	#endif

	#ifndef PHOTORESISTOR_H
		#include "photoresistor.h"
	#endif

	#ifndef SENSOR_MW_H
		#include "sensor_mw.h"
	#endif

	#ifndef PWM_BACKLIGHT_H
		#include "pwm_backlight.h"
	#endif

	#ifndef RTC_H
		#include "rtc.h"
	#endif

	#ifndef EEPROM_STUFF_H
		#include "eeprom_stuff.h"
	#endif
// ------------------------------------------------------------------ //
#define _EEPROM_COMMIT_ {\
	if (EEPROM.commit())\
		LOG_WARN("\nEEPROM successfully committed");\
	else\
		LOG_WARN("\nERROR! EEPROM commit failed");\
}

#define _TOGGLE_PIEZO_ {\
	PIEZO_MUTE = !PIEZO_MUTE;\
	LOG_WARN("PIEZO_MUTE: "+String(PIEZO_MUTE));\
	EEPROM.write(PIEZO_MUTE_ADDR, (int)PIEZO_MUTE);\
	delay(50);\
	_EEPROM_COMMIT_\
}

#define _TOGGLE_AUTO_BL_ {\
	auto_backlight = !auto_backlight;\
	LOG_WARN("auto_backlight: "+String(auto_backlight));\
	EEPROM.write(AUTO_BL_ADDR,auto_backlight);\
	delay(50);\
	_EEPROM_COMMIT_\
}

#define _RESTORE_BACKLIGHT_ {\
	set_pwm_val(4000);\
	writeEepromInt(4000, PWM_LVL_ADDR);\
	delay(50);\
	_EEPROM_COMMIT_\
}

#define _VALID_TOUCH_ (p.z > ts.pressureThreshhold && p.z<MAX_PRESSURE) && (ay>-10) && (ax>-8)

#define LEFT_BUTTON ax<TOUCH_LIM_X1 && ay>TOUCH_LIM_Y1
#define RIGHT_BUTTON ax>TOUCH_LIM_X2 && ay>TOUCH_LIM_Y1
#define MIDDLE_BUTTON ay>TOUCH_LIM_Y1 && ax>TOUCH_LIM_X1 && ax<TOUCH_LIM_X2

// ------------------------------------------------------------------ //
// Declare TFT LCD module
Shivam_PicoW_TFT myTFT = Shivam_PicoW_TFT(INITIAL_PWM_VAL,SCR_ROT);

// Declare current sensor
Adafruit_INA219 ina219;

// Declare Temperature & humidity sensor
Adafruit_SHT31 sht31 = Adafruit_SHT31();

// Declare resistive touch overlay
TouchScreen ts = TouchScreen(XP, YP, XM, YM, TS_RESISTANCE);

// Declare RTC
DS3232RTC myRTC;
bool RTC_SET_MODE = false;
// ------------------------------------------------------------------ //
void init_hardware()
/* Initializes all hardware-related stuff. */
{
	// Init lcd module
	myTFT.begin();

	// Init real-time clock
	init_rtc(&myRTC);

	// Retrieve stored settings
	init_eeprom();

	// Set screen brightness
	if (!auto_backlight) set_pwm_val(PWM_LVL);

	// Init I/O pin related stuff
	init_piezo();
	init_photoresistor();
	init_push_buttons();
	init_slide_switches();
	init_mw_sensor();

	// Init current sensor
	ina219.begin();

	// Init temp/humidity sensor
	init_temp_humid_sensor(&sht31);

	// Init touch overlay
	ts.pressureThreshhold=TOUCH_PRESSURE_THRESHOLD; // tocuhscreen pressure

}

// =============================================================================
// =============================================================================
// For setting RTC through serial
// =============================================================================
// =============================================================================

#include <DS3232RTC.h>      // https://github.com/JChristensen/DS3232RTC
#include <Streaming.h>      // https://github.com/janelia-arduino/Streaming

#define RTC_SET_MODE_KEY 12345

void printDateTime(time_t t);
void printTime(time_t t);
void printDate(time_t t);
void printI00(int val, char delim);

void rtc_set_loop()
{
    static time_t tLast;
    time_t t;
    tmElements_t tm;

    int avail=Serial.available();

    // check for input to set the RTC, minimum length is 12, i.e. yy,m,d,h,m,s
    if (avail >= 12) {
        // note that the tmElements_t Year member is an offset from 1970,
        // but the RTC wants the last two digits of the calendar year.
        // use the convenience macros from the Time Library to do the conversions.
        int y = Serial.parseInt();
        if (y >= 100 && y < 1000)
            Serial << F("Error: Year must be two digits or four digits!") << endl;
        else {
            if (y >= 1000)
                tm.Year = CalendarYrToTm(y);
            else    // (y < 100)
                tm.Year = y2kYearToTm(y);
            tm.Month = Serial.parseInt();
            tm.Day = Serial.parseInt();
            tm.Hour = Serial.parseInt();
            tm.Minute = Serial.parseInt();
            tm.Second = Serial.parseInt();
            t = makeTime(tm);
            myRTC.set(t);   // use the time_t value to ensure correct weekday is set
            setTime(t);
            Serial << F("rtcsetloop: RTC set to: ");
            printDateTime(t);
            Serial << endl;

            // Return from rtc to normal mode
            RTC_SET_MODE = false;

            // dump any extraneous input
            while (Serial.available() > 0) Serial.read();
        }
    }

    else if (avail>=1){
    	int input = Serial.parseInt();
    	if (input!=0)
			if (input==RTC_SET_MODE_KEY){
				RTC_SET_MODE=false;
				LOG_WARN("HW.H: RTC_SET_MODE: "+String(RTC_SET_MODE));
				SWITCH_SCR=true;
			}
    }

    t = now();
    if (t != tLast) {
        tLast = t;
        printDateTime(t);
        if (second(t) == 0) {
            float c = myRTC.temperature() / 4.;
            float f = c * 9. / 5. + 32.;
            Serial << F("  ") << c << F(" C  ") << f << F(" F");
        }
        Serial << endl;
    }
}
// print date and time to Serial
void printDateTime(time_t t)
{
    printDate(t);
    Serial << ' ';
    printTime(t);
    Serial << " yy,m,d,h,m,s";

}

// print time to Serial
void printTime(time_t t)
{
    printI00(hour(t), ':');
    printI00(minute(t), ':');
    printI00(second(t), ' ');
}

// print date to Serial
void printDate(time_t t)
{
    printI00(day(t), 0);
    Serial << monthShortStr(month(t)) << _DEC(year(t));
}

// Print an integer in "00" format (with leading zero),
// followed by a delimiter character to Serial.
// Input value assumed to be between 0 and 99.
void printI00(int val, char delim)
{
    if (val < 10) Serial << '0';
    Serial << _DEC(val);
    if (delim > 0) Serial << delim;
    return;
}