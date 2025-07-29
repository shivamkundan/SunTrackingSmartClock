// Buttons used for multiple screens

#ifndef _MENU_BUTTONS_H_
 	#define _MENU_BUTTONS_H_
#endif

#ifndef Shivam_PicoW_TFT_H
	#include <Shivam_PicoW_TFT.h>
#endif

#ifndef COLORS_H
	#include "../../colors.h"
#endif

#ifndef MY_FONTS_H
	#include "../../MyFonts/my_fonts.h"
#endif

#define BUTTON_W 150
#define BUTTON_H 100
#define BUTTON_X 2
#define BUTTON_Y 25
#define BUTTON_SPACING_X 10
#define BUTTON_SPACING_Y 10
#define BUTTON_TEXTSIZE 2
#define NROWS 2
#define NCOLS 3

#define NUM_MENU_PAGES 2
#define NUM_BTNS_PER_PAGE 6

#define NAV_BUTTON_H BUTTON_H+25
#define NAV_PREV_X BUTTON_X+0*(BUTTON_W+BUTTON_SPACING_X)
#define NAV_PREV_Y BUTTON_Y+2*(BUTTON_H+BUTTON_SPACING_Y)
#define NAV_NEXT_X BUTTON_X+2*(BUTTON_W+BUTTON_SPACING_X)
#define NAV_NEXT_Y NAV_PREV_Y

#define BNUM_NAV_PREV 100
#define BNUM_NAV_NEXT 101
// ---------------------------------------------------------------- //
// For displaying labels

// ----- button positions ----- //
// (0,  0), (160,  0), (320,  0)
// (0,110), (160,110), (320,110)
// (0,210), (160,210), (320,210)
#define X_INCR 160
#define Y_INCR 110

// x-axis positions
#define X1 0*X_INCR+BUTTON_X
#define X2 1*X_INCR+BUTTON_X
#define X3 2*X_INCR+BUTTON_X
#define X4 3*X_INCR+BUTTON_X //dummy

// y-axis positions
#define YB BUTTON_Y+(BUTTON_H/2)+(BUTTON_SPACING_Y/2)
#define Y1 0*Y_INCR+YB
#define Y2 1*Y_INCR+YB
#define Y3 2*Y_INCR+YB
#define Y4 3*Y_INCR+YB //dummy

uint16_t xp[]={X1,X2,X3,X1,X2,X3,X4};
uint16_t yp[]={Y1,Y1,Y1,Y2,Y2,Y2,Y4};

// ---------------------------------------------------------------- //

Adafruit_GFX_Button pg1_btns[NUM_BTNS_PER_PAGE];
Adafruit_GFX_Button pg2_btns[NUM_BTNS_PER_PAGE];
Adafruit_GFX_Button* all_buttons [NUM_MENU_PAGES]= {pg1_btns,pg2_btns};

// next/prev buttons
Adafruit_GFX_Button NAV_PREV, NAV_NEXT;
Adafruit_GFX_Button* nav_btns[]={&NAV_PREV, &NAV_NEXT};

uint16_t buttoncolors[4] = {MAROON, DARKGREEN, ORANGE, NAVY};
uint menu_pg_num=0;

// ------------------------------------------------------------- //
// Shivam_TXT       close_label = Shivam_TXT(225,     300,  FreeSansBold15pt7b, 1, LIGHTGREY, BG_COLOR);
// ------------------------------------------------------------- //

void draw_all_buttons(){
	for (uint8_t i=0;i<NUM_BTNS_PER_PAGE;i++)
		all_buttons[menu_pg_num][i].drawButton();
}

void increment_menu_pg(){
	if (menu_pg_num<(NUM_MENU_PAGES-1))
		menu_pg_num+=1;
	draw_all_buttons();
}

void decrement_menu_pg(){
	if (menu_pg_num!=0)
		menu_pg_num-=1;
	draw_all_buttons();
}

void init_nav_buttons(){
	// Draw nav buttons
	NAV_PREV.initButtonUL(&myTFT.tft, NAV_PREV_X, NAV_PREV_Y,	BUTTON_W,	NAV_BUTTON_H,	BG_COLOR,	BG_COLOR, WHITE,	(char *) "<<    ",	BUTTON_TEXTSIZE,	BUTTON_TEXTSIZE);
	NAV_NEXT.initButtonUL(&myTFT.tft, NAV_NEXT_X, NAV_NEXT_Y,	BUTTON_W,	NAV_BUTTON_H,	BG_COLOR,	BG_COLOR, WHITE,	(char *) "    >>",	BUTTON_TEXTSIZE,	BUTTON_TEXTSIZE);
}

void init_buttons_no_labels()
{
	for (uint8_t PG=0; PG<NUM_MENU_PAGES; PG+=1){
		for (uint8_t row=0; row<NROWS; row+=1) {
			for (uint8_t col=0; col<NCOLS; col+=1) {

				String name;
				uint index=(PG*(NUM_BTNS_PER_PAGE))+col + row*NCOLS;
				// LOG_DEBUG("index: "+String(index));

				name="";

				char* c = const_cast<char*> (name.c_str());

				// "UL" = upper left
				all_buttons[PG][col + row*NCOLS].initButtonUL(
						&myTFT.tft,									//       gfx: Pointer to our display so we can draw to it!
						BUTTON_X+col*(BUTTON_W+BUTTON_SPACING_X),	//         x: The X coordinate of the center of the button
						BUTTON_Y+row*(BUTTON_H+BUTTON_SPACING_Y),   // 		   y: The Y coordinate of the center of the button
						BUTTON_W,									//         w: Width of the buttton
						BUTTON_H,									//         h: Height of the buttton
						BG_COLOR,								//   outline: Color of the outline (16-bit 5-6-5 standard)
						buttoncolors[PG],					//      fill: Color of the button fill (16-bit 5-6-5 standard)
						WHITE,								// textcolor: Color of the button label (16-bit 5-6-5 standard)
						// buttonlabels[PG][col + row*NCOLS],					//     label: Ascii string of the text inside the button
						c,					//     label: Ascii string of the text inside the button

						BUTTON_TEXTSIZE,							//  textsize X: The font magnification of the label tex
						BUTTON_TEXTSIZE								//  textsize Y: The font magnification of the label tex
					);
			}
		}
	}
}