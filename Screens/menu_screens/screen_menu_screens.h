#ifndef COMMON_H
	#include "../common.h"
#endif

#ifndef _MENU_BUTTONS_H_
 	#include "menu_buttons.H"
#endif

// ------------------------------------------------------------- //
void disp_scr_names()
/* Overlays screen names on top of buttons */
{
	uint8_t start_i= NUM_BTNS_PER_PAGE*menu_pg_num;

	for (int i=0;i<NUM_BTNS_PER_PAGE;i++){
		Shivam_TXT label = Shivam_TXT( xp[i], yp[i], FreeMonoBold10pt7b, 1, WHITE, buttoncolors[menu_pg_num]);
		label.begin(myTFT.tft);
		label.print_tft_centered(scr_list_names[i+start_i],xp[i],xp[i]+BUTTON_W);
	}
}

void nav_btn_actions(uint8_t bnum)
/* Control nav buttons */
{
	if (bnum==BNUM_NAV_PREV){
		decrement_menu_pg();
		disp_scr_names();
	}
	else if (bnum==BNUM_NAV_NEXT){
		increment_menu_pg();
		disp_scr_names();
	}
}

void scr_btn_actions(uint8_t bnum)
/* Control screen selection buttons. */
{
	if (bnum!=BNUM_NAV_PREV && bnum!=BNUM_NAV_NEXT){
		uint16_t s=bnum+(NUM_BTNS_PER_PAGE)*menu_pg_num;
		if (s<NUM_REG_SCREENS){
			curr_screen=s;
			SWITCH_SCR=true;
		}
	}
}

void button_controller(Adafruit_GFX_Button* BTN, uint8_t bnum)
/* Decides button appearance, performs mapped action */
{
	if (BTN->contains(ax, ay))
		BTN->press(true);
	else
		BTN->press(false);

	if (BTN->justReleased()){

		BTN->drawButton();  // draw normal

		// Control nav buttons
		nav_btn_actions(bnum);

		// Control screen selection buttons
		scr_btn_actions(bnum);
	}
	if (BTN->justPressed())
		BTN->drawButton(true);  // draw invert!
}

// ------------------------------------------------------------- //
void scr_menu_screens_on_enter(uint TimeStamp){
	myTFT.clear_screen(BG_COLOR);
	LOG_TRACE("scr_menu_screens_on_enter");
	menu_pg_num=0;
	draw_all_buttons();
	NAV_PREV.drawButton();
	NAV_NEXT.drawButton();
	disp_scr_names();

	_DRAW_X_
}

void scr_menu_screens_on_touch(uint TimeStamp){
	// Check for normal button press
	for (uint8_t i=0;i<NUM_BTNS_PER_PAGE;i++)
		button_controller(&all_buttons[menu_pg_num][i],i);

	// Check for nav button press
	button_controller(&NAV_PREV,BNUM_NAV_PREV);
	button_controller(&NAV_NEXT,BNUM_NAV_NEXT);
}

void scr_menu_screens_initialize(Screen* S){
	S->set_func_per_second(do_nothing);
	S->set_func_per_minute(do_nothing);
	S->set_func_per_hour(do_nothing);
	S->set_func_on_enter(scr_menu_screens_on_enter);
	S->set_func_on_exit(do_nothing);
	S->set_func_on_touch(scr_menu_screens_on_touch);

	// Init buttons
	init_buttons_no_labels();

	// Init nav buttons
	init_nav_buttons();

	S->show_power_info=false;
	S->show_backlight_info=false;
}