#ifndef TS_PARAMS_H
	#define TS_PARAMS_H
#endif

#ifndef TouchScreen_H
	#include "TouchScreen.h"
#endif

#ifndef UTILS_H
  #include "../utils.h"
#endif

#ifndef Shivam_PicoW_TFT_H
	#include <Shivam_PicoW_TFT.h>
#endif

#ifndef SCR_ROT
	#define SCR_ROT 3
#endif

// Touch pins
#define YP A0  // must be an analog pin, use "An" notation!
#define XM A1  // must be an analog pin, use "An" notation!
#define YM 12   // can be a digital pin
#define XP 13   // can be a digital pin

#define TOUCH_SQUARE_SIDE 50 // for drawing touch points

#define TOUCH_PRESSURE_THRESHOLD 100
#define MAX_PRESSURE 2800

#define TS_RESISTANCE 290  // Measured by shivam

// ---------- Touch screen limits ---------- //
#define TOUCH_LIM_X1 160
#define TOUCH_LIM_X2 480-160
#define TOUCH_LIM_Y1 320-80
#define TOUCH_LIM_Y_MENU_SCR 240

// // For better pressure precision, we need to know the resistance
// // between X+ and X- Use any multimeter to read it    <<<<<< TO DO
// // For the one we're using, its 300 ohms across the X plate
// TouchScreen ts = TouchScreen(XP, YP, XM, YM, TS_RESISTANCE);
// // ts.pressureThreshhold=300;

// Stores the adjusted x and y coords
int ax=-1;
int ay=-1;

int touch_countdown=0;
bool touch_en=true;

void translate_coords(uint16_t curr_x, uint16_t curr_y )
/* Translate co-ordinates from TS panel to LCD */
{
	switch (SCR_ROT){
		case 0:
			// for orientation no. 0 / portrait
			ax=custom_map(curr_x, 151, 861, 0, 319);
			ay=custom_map(curr_y, 99, 922, 0, 479);
			break;

		case 1:
			// for orientation no. 1 / landscape
			ay=custom_map(curr_x, 230-10, 835-10, 319, 0);
			ax=custom_map(curr_y, 120-10, 889-10, 0, 479);
			break;

		case 3:
			// for orientation no. 3 / landscape
			ay=custom_map(curr_x, 230-10, 835-10, 0, 319);
			ax=custom_map(curr_y, 120-10, 889-10, 479, 0);
			break;
	}
}

// // ============================ HELPERS ============================ //

// void show_touch_point(int curr_x, int curr_y, int curr_z, Adafruit_HX8357 tft)
// /* Draw a square around the touch point */
// {
// 	// For finding max/min x and y
// 	// update_touch_limits((int) curr_x,(int) curr_y);
// 	// print_touch_limits((int) curr_x, (int) curr_y,tft);

// 	// Translate TS co-ords to current LCD orientation
// 	translate_coords((int) curr_x,(int) curr_y);

// 	// // Blit to screen
// 	// tft.println("(X,Y) = ("+String(ax)+","+String(ay)+")");
// 	// tft.println(" ");
// 	// tft.println("p.z: "+String(curr_z));
// 	// tft.println(" ");

// 	// Draw square around touch point
// 	tft.drawRect(ax-TOUCH_SQUARE_SIDE/2, ay-TOUCH_SQUARE_SIDE/2, TOUCH_SQUARE_SIDE, TOUCH_SQUARE_SIDE, HX8357_WHITE);
// }