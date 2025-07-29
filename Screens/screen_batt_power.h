#ifndef Shivam_PicoW_TFT_H
	#include <Shivam_PicoW_TFT.h>
#endif

#ifndef COLORS_H
	#include "../colors.h"
#endif

#ifndef SCREEN_CLASS_H
	#include "ScreenClass.h"
#endif

#ifndef HARDWARE_H
	#include "../Hardware/hardware.h"
#endif

#ifndef MY_FONTS_H
	#include "../MyFonts/my_fonts.h"
#endif

#ifndef BITMAPS_H
    #include "../Bitmaps/bitmaps.h"
#endif

#define INACTIVE_COLOR LIGHTBLACK

// ------------------------------------------------------------------------------------------ //
#define PLUGGED_IN_AND_CHARGED avg_current<1.0 && avg_current>=-0.5
#define PLUGGED_IN_AND_CHARGING avg_current < -0.5
#define ON_BATTERY_POWER avg_current>=1.0

// ------------------------------------------------------------------------------------------ //
// For bitmap drawing
#define BMP myTFT.tft.drawBitmap
#define _DRAW_BATT_(COLOR) ( BMP(BATT_X_POS, BATT_Y_POS,     BATT_BMP,     BATT_W,     BATT_H,     COLOR))
#define _DRAW_VBUS_(COLOR)     (BMP(VBUS_X_POS,     VBUS_Y_POS,     VBUS_BMP,     VBUS_W,     VBUS_H,     COLOR))
#define _DRAW_USB_(COLOR)      (BMP(USB_IN_X_POS,   USB_IN_Y_POS,   USB_IN_BMP,   USB_IN_W,   USB_IN_H,   COLOR))

#define _DRAW_CHARGING_(COLOR) (BMP(CHARGING_X_POS, CHARGING_Y_POS, CHARGING_BMP, CHARGING_W, CHARGING_H, COLOR))
#define _DRAW_DRAINING_(COLOR) (BMP(DRAINING_X_POS, DRAINING_Y_POS, DRAINING_BMP, DRAINING_W, DRAINING_H, COLOR))

#define _DRAW_INA219_CHARGING_(COLOR) (BMP(INA219_CHARGING_X_POS, INA219_CHARGING_Y_POS, INA219_CHARGING_BMP, INA219_CHARGING_W, INA219_CHARGING_H, COLOR))
#define _DRAW_INA219_DRAINING_(COLOR) (BMP(INA219_DRAINING_X_POS, INA219_DRAINING_Y_POS, INA219_DRAINING_BMP, INA219_DRAINING_W, INA219_DRAINING_H, COLOR))

#define _DRAW_CKT_(C1,C2,C3,C4,C5) { \
	_DRAW_BATT_(C1);\
	_DRAW_VBUS_(C2); \
	_DRAW_USB_(C3);\
	_DRAW_CHARGING_(C4);\
	_DRAW_DRAINING_(C5);\
}
// ------------------------------------------------------------------------------------------ //
enum STATE {CHARGING, DISCHARGING, CHARGED};
STATE curr_state;
STATE prev_state;


// Last connected T
// Last disconnected


// ------------------------------------------------------------------------------------------ //
Shivam_TXT BATT_CURRENT_CHARGING_TXT = Shivam_TXT(SX+85,  SY+90 , FreeMonoBold10pt7b, 1, ORANGE, BG_COLOR);
Shivam_TXT BATT_CURRENT_DRAINING_TXT = Shivam_TXT(SX+170, SY+10,  FreeMonoBold10pt7b, 1, ORANGE, BG_COLOR);
Shivam_TXT   BATT_POWER_CHARGING_TXT = Shivam_TXT(SX+85,  SY+130, FreeMonoBold10pt7b, 1, ORANGE, BG_COLOR);
Shivam_TXT   BATT_POWER_DRAINING_TXT = Shivam_TXT(SX+360, SY-20,  FreeMonoBold10pt7b, 1, ORANGE, BG_COLOR);
Shivam_TXT       BATT_POWER_VOLT_TXT = Shivam_TXT(10,     SY-10,  FreeMonoBold12pt7b, 1, ORANGE, BG_COLOR);

Shivam_TXT       STATUS_TXT = Shivam_TXT(10,     90,  FreeMonoBold10pt7b, 1, LIGHT_RED, BG_COLOR);

// ------------------------------------------------------------------------------------------ //
void check_batt_power_ckt_state(uint TimeStamp);
void scr_batt_power_per_second(uint TimeStamp);
void scr_batt_power_per_minute(uint TimeStamp);
void scr_batt_power_per_hour(uint TimeStamp);
void scr_batt_power_on_enter(uint TimeStamp);
void scr_batt_power_initialize(Screen* S);


#define NUM_CURRENT_READINGS 20

// Using array for current_mA makes graphics smoother
uint8_t current_read_index=0;
float current_vals[NUM_CURRENT_READINGS];
float total_current=0;
float avg_current=0;
// ------------------------------------------------------------------------------------------ //
void read_current(float current_mA)
/* Read analog voltage. Add to array. Compute average. */
{
	// subtract the last reading:
	total_current = total_current - current_vals[current_read_index];

	// read from the sensor:
	current_vals[current_read_index] = current_mA;

	// add the reading to the total:
	total_current = total_current + current_vals[current_read_index];

	// advance to the next position in the array:
	current_read_index = current_read_index + 1;

	// if we're at the end of the array...
	if (current_read_index >= NUM_CURRENT_READINGS)
		current_read_index = 0; // ...wrap around to the beginning:

	// calculate the average:
	avg_current = total_current / NUM_CURRENT_READINGS;
}

// ------------------------------------------------------------------------------------------ //
void show_status(){
	if (curr_state==DISCHARGING){
			_DRAW_INA219_CHARGING_(BG_COLOR);
			_DRAW_CHARGING_(BG_COLOR);
			STATUS_TXT.change_color(PINK);
			STATUS_TXT.print_tft_middle("DISCHARGING");
		}

		if (curr_state==CHARGING || curr_state==CHARGED){
			_DRAW_INA219_DRAINING_(BG_COLOR);
			_DRAW_DRAINING_(BG_COLOR);
			STATUS_TXT.change_color(curr_state==CHARGING ? YELLOW : GREEN);
			myTFT.tft.fillRect(175, 75, 140, 20, BG_COLOR);  // draw rect other "discharging" overhangs
			STATUS_TXT.print_tft_middle( curr_state==CHARGING ? "CHARGING" : "CHARGED");
		}
}

void check_batt_power_ckt_state(uint TimeStamp){

	float loadvoltage=0;
	float current_mA=0;
	float power_mW=0;
	float shuntvoltage=0;
	float busvoltage=0;
	get_vals_current_sensor(&ina219,&loadvoltage, &current_mA, &power_mW, &shuntvoltage, &busvoltage);

	read_current(current_mA);	// Add value to array

	// Determine circuit state
	if (ON_BATTERY_POWER){
		prev_state=curr_state;
		curr_state=DISCHARGING;
	}
	else if (PLUGGED_IN_AND_CHARGED){
		prev_state=curr_state;
		curr_state=CHARGED;
	}
	else if (PLUGGED_IN_AND_CHARGING){
		prev_state=curr_state;
		curr_state=CHARGING;
	}

	// Clear previous text
	if (curr_state!=prev_state){
		LOG_DEBUG("curr_state!=prev_state");
		myTFT.tft.fillRect(SX+85,  SY+70, 150, 65, BG_COLOR);
		myTFT.tft.fillRect(SX+335, SY-37, 145, 21, BG_COLOR);
		myTFT.tft.fillRect(SX+162, SY-10, 130, 21, BG_COLOR);

		show_status();

		scr_batt_power_per_second(TimeStamp);
	}
}
// ------------------------------------------------------------------------------------------ //
void scr_batt_power_per_second(uint TimeStamp){

	float loadvoltage=0;
	float current_mA=0;
	float power_mW=0;
	float shuntvoltage=0;
	float busvoltage=0;
	get_vals_current_sensor(&ina219,&loadvoltage, &current_mA, &power_mW, &shuntvoltage, &busvoltage);

	// Show current values
	if (ON_BATTERY_POWER){
		BATT_CURRENT_DRAINING_TXT.print_tft(String(current_mA)+"mA"); // / "+String(avg_current)+"mA");
		BATT_POWER_DRAINING_TXT.print_tft_ralign(String(power_mW)+"mW");
	}
	else if (PLUGGED_IN_AND_CHARGING || PLUGGED_IN_AND_CHARGED){
		BATT_CURRENT_CHARGING_TXT.print_tft(String(current_mA)+"mA");//  "+String(avg_current)+"mA");
		// if (ON_BATTERY_POWER)
		// 	BATT_POWER_CHARGING_TXT.print_tft_ralign(String(power_mW)+"mW");
		// else
			BATT_POWER_CHARGING_TXT.print_tft(String(power_mW)+"mW");
	}

	// Always show battery voltage
	BATT_POWER_VOLT_TXT.print_tft(String(loadvoltage)+"V");

	// Plugged in - charging
	if (PLUGGED_IN_AND_CHARGING){
		_DRAW_CKT_(YELLOW,GREEN,GREEN,GREEN,INACTIVE_COLOR);
		_DRAW_INA219_CHARGING_(GREEN);
	}
	// Plugged in - charged
	if (PLUGGED_IN_AND_CHARGED){
		_DRAW_CKT_(GREEN,GREEN,GREEN,OLIVE,INACTIVE_COLOR);
		_DRAW_INA219_CHARGING_(OLIVE);
	}
	// Not plugged in - on battery power
	else if (ON_BATTERY_POWER) {
		_DRAW_CKT_(WHITE,INACTIVE_COLOR,INACTIVE_COLOR,INACTIVE_COLOR,RED);
		_DRAW_INA219_DRAINING_(RED);
	}
}

void scr_batt_power_on_enter(uint TimeStamp){
	// Shivam_TXT title = Shivam_TXT(5, 35, FreeMonoBold12pt7b, 1, TERTIARY_TXT_COLOR, BG_COLOR);
	// title.begin(myTFT.tft);
	// title.print_tft_middle("BATT / POWER");
	myTFT.clear_screen(BG_COLOR);
	
	_PRINT_TITLE_SMALL_("POWER CKT");

	myTFT.tft.drawBitmap(MCU_X_POS,      MCU_Y_POS,      MCU_BMP,      MCU_W,      MCU_H,      DARKGREY);
	myTFT.tft.drawBitmap(BATT_X_POS,     BATT_Y_POS,     BATT_BMP,     BATT_W,     BATT_H,     WHITE);
	myTFT.tft.drawBitmap(VSYS_X_POS,     VSYS_Y_POS,     VSYS_BMP,     VSYS_W,     VSYS_H,     GREEN);

	show_status();
}

void scr_batt_power_on_touch(uint TimeStamp){
	check_batt_power_ckt_state(TimeStamp);
}

// ------------------------------------------------------------------------------------------ //
void scr_batt_power_initialize(Screen* S){

	// Register functions
	S->set_func_per_second(scr_batt_power_per_second);
	S->set_func_per_minute(do_nothing);
	S->set_func_per_hour(do_nothing);
	S->set_func_on_enter(scr_batt_power_on_enter);
	S->set_func_on_exit(do_nothing);
	S->set_func_on_touch(scr_batt_power_on_touch);
	S->show_power_info=false;

	// Init TXTs
	BATT_CURRENT_CHARGING_TXT.begin(myTFT.tft);
	BATT_CURRENT_DRAINING_TXT.begin(myTFT.tft);
	BATT_POWER_CHARGING_TXT.begin(myTFT.tft);
	BATT_POWER_DRAINING_TXT.begin(myTFT.tft);
	BATT_POWER_VOLT_TXT.begin(myTFT.tft);
	STATUS_TXT.begin(myTFT.tft);

	// Init current_mA array
	for (uint8_t i=0;i<NUM_CURRENT_READINGS;i++)
		current_vals[i]=0.0;
}