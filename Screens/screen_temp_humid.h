#ifndef Shivam_PicoW_TFT_H
	#include <Shivam_PicoW_TFT.h>
#endif

#ifndef SHIVAM_TXT_H
	#include <Shivam_TXT.h>
#endif

#ifndef TIME_FUNCS_H
	#include "../DateTime/time_funcs.h"
#endif

#ifndef TIME_VALS_H
	#include "../DateTime/time_vals.h"
#endif

#ifndef UTILS_H
  #include "../utils.h"
#endif

#ifndef STRING_DEFS_H
	#include "../string_defs.h"
#endif

#ifndef GLOBALS_H
	#include "../globals.h"
#endif

#ifndef SCREEN_CLASS_H
	#include "ScreenClass.h"
#endif

#ifndef HARDWARE_H
	#include "../Hardware/hardware.h"
#endif
// ---------------------------------------------------------------------------------------------------- //
#define X_AX_START 50
#define X_AX_END 460
#define Y_AX_START 115
#define Y_AX_END 270

#define MINTEMP_C 16
#define MAXTEMP_C 27
#define MINHUMID 20
#define MAXHUMID 80

#define HUMIDITY_PLOT_COLOR  CYAN
#define TEMP_PLOT_COLOR      ORANGE

#define NOW_POS_LINE_COLOR RED

#define MARKER_RADIUS 3  // for plotting

// ---------------------------------------------------------------------------------------------------- //
#define _CLEAR_PLOT_AREA_ myTFT.tft.fillRect(0, 95, 480, 205, BG_COLOR);
#define _DRAW_X_AXIS_ myTFT.tft.drawLine(X_AX_START, Y_AX_END, X_AX_END, Y_AX_END, LIGHTGREY);
#define _DRAW_Y_AXIS_ myTFT.tft.drawLine(X_AX_START, Y_AX_START+10, X_AX_START, Y_AX_END, LIGHTGREY);

#define _RESET_PLOT_ {\
	_CLEAR_PLOT_AREA_\
	_DRAW_X_AXIS_\
	_DRAW_Y_AXIS_\
}

#define _PLOT_(ARR, MIN_VAL, MAX_VAL, COLOR) {\
	for (int now_minute=1;now_minute<NUM_MINS_IN_DAY+1;now_minute++){\
		int now_x_pos=(int) custom_map(now_minute,1,NUM_MINS_IN_DAY,X_AX_START,X_AX_END);\
		int now_y_pos=(int) custom_map(ARR[now_minute-1],MIN_VAL,MAX_VAL,Y_AX_END,Y_AX_START-5);\
		myTFT.tft.fillCircle(now_x_pos, now_y_pos, MARKER_RADIUS, COLOR);\
	}\
}

#define _SHOW_NOW_POS_(NOW_MIN) {\
	int now_x_pos=(int) custom_map(NOW_MIN,1,NUM_MINS_IN_DAY,X_AX_START,X_AX_END);\
	draw_dotted_vline(myTFT.tft,2, 5,Y_AX_START+10, Y_AX_END, now_x_pos, NOW_POS_LINE_COLOR);\
}

// ---------------------------------------------------------------------------------------------------- //
Shivam_TXT temp_val_txt= Shivam_TXT(100, 80, FreeMonoBold18pt7b, 1, TEMP_PLOT_COLOR, BG_COLOR);
Shivam_TXT humid_val_txt= Shivam_TXT(300, 80, FreeMonoBold18pt7b, 1, HUMIDITY_PLOT_COLOR, BG_COLOR);

// ---------------------------------------------------------------------------------------------------- //
void draw_xlabels(){
	// x-axis labels
	Shivam_TXT T_marker_str = Shivam_TXT(X_AX_START,Y_AX_END+20, FreeMonoBold9pt7b, 1, WHITE, BG_COLOR);
	T_marker_str.begin(myTFT.tft);
	T_marker_str.print_tft_no_prev_bg("12AM");
	T_marker_str.set_x_pos(235);
	T_marker_str.print_tft_no_prev_bg("12PM");
	T_marker_str.set_x_pos(430);
	T_marker_str.print_tft_no_prev_bg("12AM");
}

void draw_y_labels(){
	// y-axis labels: humidity
	Shivam_TXT y_str_humid = Shivam_TXT(X_AX_START-23, Y_AX_END, Font4x5Fixed, 2, HUMIDITY_PLOT_COLOR, BG_COLOR);
	y_str_humid.begin(myTFT.tft);
	y_str_humid.print_tft(String(MINHUMID));
	y_str_humid.set_y_pos(125);
	y_str_humid.print_tft(String(MAXHUMID));

	// y-axis labels: temperature
	float maxVal_temp = temperature_array[0];
	for (int i = 0; i < (sizeof(temperature_array) / sizeof(temperature_array[0])); i++) {
	      maxVal_temp = max(temperature_array[i],maxVal_temp);
	    }
	LOG_DEBUG("The maximum value of the array is: ");
	LOG_DEBUG(maxVal_temp);

	Shivam_TXT y_str_temp = Shivam_TXT(5, Y_AX_END, Font4x5Fixed, 2, TEMP_PLOT_COLOR, BG_COLOR);
	y_str_temp.begin(myTFT.tft);
	y_str_temp.print_tft(String(MINTEMP_C));
	y_str_temp.set_y_pos(125);
	y_str_temp.print_tft(String((int)maxVal_temp+1));
}

// ---------------------------------------------------------------------------------------------------- //
void scr_temp_humid_per_minute(uint TimeStamp){

	// Erase plot area
	_RESET_PLOT_ ;

	uint16_t now_min=get_minute_of_day(now()+TIME_ZONE_DIFF_SECS);
	if (now_min>1)
		now_min-=2;

	// Plot all values
	_PLOT_(humidity_array,    MINHUMID,  MAXHUMID,  HUMIDITY_PLOT_COLOR);
	_PLOT_(temperature_array, MINTEMP_C, MAXTEMP_C, TEMP_PLOT_COLOR);

	// Marker for current time
	_SHOW_NOW_POS_(now_min);

	// x-axis labels
	draw_xlabels();

	// y-axis labels: humidity & temperature
	draw_y_labels();

}

void scr_temp_humid_per_second(uint TimeStamp){
	// Update every 3 seconds
	if (TimeStamp%3==0){
		temp_val_txt.print_tft(String(read_temp(&sht31))+" C");
		humid_val_txt.print_tft(String(read_humid(&sht31))+" %");
	}
}



void scr_temp_humid_on_enter(uint TimeStamp){
	myTFT.clear_screen(BG_COLOR);
	scr_temp_humid_per_minute(TimeStamp);
	_PRINT_TITLE_SMALL_("TEMP/HUMID");
	temp_val_txt.print_tft(String(read_temp(&sht31))+" C");
	humid_val_txt.print_tft(String(read_humid(&sht31))+" %");
}

void scr_temp_humid_initialize(Screen* S){
	S->set_func_per_second(scr_temp_humid_per_second);
	S->set_func_per_minute(scr_temp_humid_per_minute);
	S->set_func_per_hour(do_nothing);
	S->set_func_on_enter(scr_temp_humid_on_enter);
	S->set_func_on_exit(do_nothing);
	S->set_func_on_touch(do_nothing);
	temp_val_txt.begin(myTFT.tft);
	humid_val_txt.begin(myTFT.tft);
}