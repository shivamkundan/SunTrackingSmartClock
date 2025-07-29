/*
*	Functions for drawing grid overlay
*/

#ifndef GRID_FUNCS_H
	#define GRID_FUNCS_H
#endif

#ifndef Shivam_PicoW_TFT_H
	#include <Shivam_PicoW_TFT.h>
#endif

#ifndef HARDWARE_H
	#include "../Hardware/hardware.h"
#endif

#define DIVIDER_ROW 70  // this is the vertical distance to where top display / time area ends

void draw_seconds_grid(){
	for (int row=BG_GRID_SIZE;row<DIVIDER_ROW;row+=BG_GRID_SIZE)
		myTFT.tft.drawLine(180, row,410, row, LIGHT_RED);

	for (int col=180;col<410;col+=BG_GRID_SIZE)
		myTFT.tft.drawLine(col, 0,col, DIVIDER_ROW, LIGHT_RED);
}

void draw_quadrants()
/* Divide screen into four parts */
{
	// Width = 3 
	myTFT.tft.drawLine(SCREEN_W/2 +1, 0, SCREEN_W/2 +1, DIVIDER_ROW, GREEN);
	myTFT.tft.drawLine(SCREEN_W/2,    0, SCREEN_W/2,    DIVIDER_ROW, GREEN);
	myTFT.tft.drawLine(SCREEN_W/2 -1, 0, SCREEN_W/2 -1, DIVIDER_ROW, GREEN);
}

void draw_time_area_grid()
/* Draws grid over large time display */
{

	// Draw vertical lines
	for (int xpos=410; xpos<SCREEN_W; xpos+=10)
		myTFT.tft.drawLine(xpos, 0,xpos, 50, DARKCYAN);

	// Draw horizontal lines
	for (int ypos=10; ypos<50; ypos+=10)
		myTFT.tft.drawLine(410, ypos,SCREEN_W, ypos, DARKCYAN);
}

void draw_divider_row()
/* Shows the dividing line between bottom bar and the rest */
{
	myTFT.tft.drawLine(1, DIVIDER_ROW,SCREEN_W, DIVIDER_ROW, BLUE);
	myTFT.tft.drawLine(1, SCREEN_H-20,SCREEN_W, SCREEN_H-20, BLUE);
}

void draw_touch_area_lines(){
	myTFT.tft.drawLine(0,TOUCH_LIM_Y1,SCREEN_W,TOUCH_LIM_Y1,WHITE);
}

void draw_grid(uint grid_size)
/* Overlays grid with x,y spacing = grid_size */
{
	// Draw horizontal lines
	for (int ypos=grid_size; ypos<SCREEN_W; ypos+=grid_size)
		myTFT.tft.drawLine(1, ypos,SCREEN_W, ypos, LIGHTBLACK);

	// Vertical lines
	for (int col=grid_size;col<SCREEN_W+1;col+=grid_size)
		if (col==240)
			myTFT.tft.drawLine(col, 1, col, SCREEN_H, GREEN);
		else
			myTFT.tft.drawLine(col, 1, col, SCREEN_H, LIGHTBLACK);

	draw_divider_row();
	draw_touch_area_lines();
}