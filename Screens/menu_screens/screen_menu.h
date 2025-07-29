#ifndef COMMON_H
	#include "../common.h"
#endif

// Declare buttons
Adafruit_GFX_Button BTN1,BTN2,BTN3,BTN4;
Adafruit_GFX_Button* btn_list[]={&BTN1,&BTN2,&BTN3,&BTN4};

#define _COLLIDE_ btn_list[i]->contains(ax, ay) // for checking button press

#define NUM_MAIN_MENU_BTNS 4
#define MAIN_MENU_FONT FreeSansBold10pt7b
#define MAIN_MENU_FONT_COLOR WHITE
#define MAIN_MENU_BTN_COLOR DARK_ORANGE

#define _DRAW_BTNS_(A,B,C,D) { A.drawButton(); B.drawButton(); C.drawButton(); D.drawButton(); }

// Button positions
// (10,  60), (250,  60)
// (10, 150), (250, 150)
const int bx=10, by=60, bw=220, bh=80;
const int xvals[] = {bx, bx+bw+20, bx,       bx+bw+20};
const int yvals[] = {by, by,       by+bh+10, by+bh+10};

String NM[]={"SCREENS","SETTINGS","BACKLIGHT","INFO"};

// bool timer_fired=false;
int64_t alarm_callback(alarm_id_t id, void *user_data) {
   printf("Timer %d fired!\n", (int) id);
   // timer_fired = true;
   // Can return a value here in us to fire in the future
   if (curr_screen==SCREEN_MENU){
   	curr_screen=return_screen;
   	SWITCH_SCR=true;
   }
  return 0;
}


void show_names()
/* Overlays names on top of buttons since default lib is finicky */
{
	LOG_TRACE("");
	for (int i=0;i<NUM_MAIN_MENU_BTNS;i++){
		Shivam_TXT label = Shivam_TXT( xvals[i], yvals[i]+bh/2 +5, MAIN_MENU_FONT, 1, MAIN_MENU_FONT_COLOR, MAIN_MENU_BTN_COLOR);
		label.begin(myTFT.tft);
		label.print_tft_centered(NM[i],xvals[i],xvals[i]+bw);
	}
}

void scr_menu_main()
/* Controls button press and navigation. */
{
	for (uint8_t i=0;i<NUM_MAIN_MENU_BTNS;i++){

		btn_list[i]->press(_COLLIDE_);  // check for button press

		if (btn_list[i]->justReleased()){
			btn_list[i]->drawButton();  // draw normal
			prev_screen=SCREEN_MENU;
			SWITCH_SCR=true;

			switch (i) {
				case (0): { curr_screen=SCREEN_MENU_SCREENS;  SWITCH_SCR=true; return;}
				case (1): { curr_screen=SCREEN_MENU_SETTINGS; SWITCH_SCR=true; return;}
				case (2): { curr_screen=SCREEN_BACKLIGHT;     SWITCH_SCR=true; return;}
				case (3): { curr_screen=SCREEN_MENU_INFO;     SWITCH_SCR=true; return;}
			}
		}
		if (btn_list[i]->justPressed()){
			btn_list[i]->drawButton(true);  // draw invert!
		}
	}
}

void scr_menu_on_enter(uint TimeStamp){
	LOG_TRACE("");
	myTFT.clear_screen(BG_COLOR);

	_DRAW_BTNS_(BTN1,BTN2,BTN3,BTN4)
	_DRAW_X_

	show_names(); // Display button names

	return;
}

void scr_menu_on_touch(uint TimeStamp)
/* Fires alarm at each touch. Previous screen is restored after timeout. */
{
	scr_menu_main();

	// time-out alarm resets with each press
	add_alarm_in_ms(MENU_TIMEOUT_S*1000, alarm_callback, NULL, false);
}

void scr_menu_initialize(Screen* S){
	S->set_func_per_second(do_nothing);
	S->set_func_per_minute(do_nothing);
	S->set_func_per_hour(do_nothing);
	S->set_func_on_enter(scr_menu_on_enter);
	S->set_func_on_exit(do_nothing);
	S->set_func_on_touch(scr_menu_on_touch);
	S->show_power_info=false;
	S->show_mw_icon=false;

	// Give the buttons blank names otherwise lib causes errors
	String name="";
	char* c = const_cast<char*> (name.c_str());

	// int bx=10, by=60, bw=220, bh=80;
	BTN1.initButtonUL(&myTFT.tft,bx,       by,      bw,bh,BG_COLOR,MAIN_MENU_BTN_COLOR,WHITE,c, 2,2);
	BTN2.initButtonUL(&myTFT.tft,bx+bw+20, by,      bw,bh,BG_COLOR,MAIN_MENU_BTN_COLOR,WHITE,c, 2,2);
	BTN3.initButtonUL(&myTFT.tft,bx,       by+bh+10,bw,bh,BG_COLOR,MAIN_MENU_BTN_COLOR,WHITE,c, 2,2);
	BTN4.initButtonUL(&myTFT.tft,bx+bw+20, by+bh+10,bw,bh,BG_COLOR,MAIN_MENU_BTN_COLOR,WHITE,c, 2,2);
}