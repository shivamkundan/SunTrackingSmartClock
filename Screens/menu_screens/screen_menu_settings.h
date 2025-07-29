#ifndef COMMON_H
	#include "../common.h"
#endif

#define      MUTE_BTN 0
#define   AUTO_BL_BTN 1
#define CYCLE_SCR_BTN 2
#define      GRID_BTN 3
#define TOGGLE_DEBUG_BTN 4
// ------------------------------------------------------------- //
String Settings[]={"Mute","Auto BL","Cycle Scr","Grid","Presence","","","",""};

void disp_settings()
{
	for (int i=0;i<NUM_BTNS_PER_PAGE;i++){
		Shivam_TXT label = Shivam_TXT( xp[i], yp[i], FreeMonoBold10pt7b, 1, WHITE, buttoncolors[menu_pg_num]);
		label.begin(myTFT.tft);
		label.print_tft_centered(Settings[i],xp[i],xp[i]+BUTTON_W);
	}
}


void btn_ctrl(Adafruit_GFX_Button* BTN, uint8_t bnum)
/* Map buttons to actions */
{
	if (BTN->contains(ax, ay)){
		LOG_DEBUG("Pressed button: "+String(bnum));
		BTN->press(true);
		disp_settings();
	}
	else
		BTN->press(false);

	if (BTN->justReleased()){

		BTN->drawButton();  // draw normal

		// if (bnum==BNUM_NAV_PREV){
		// 	decrement_menu_pg(); disp_settings();
		// }
		// else if (bnum==BNUM_NAV_NEXT){
		// 	increment_menu_pg(); disp_settings();
		// }
		switch (bnum){
			case    (MUTE_BTN):  {_TOGGLE_PIEZO_; break;}
			case  (AUTO_BL_BTN): { _TOGGLE_AUTO_BL_; break;}
			case(CYCLE_SCR_BTN): {  cycle_screens=!cycle_screens; break;}
			case     (GRID_BTN): { SHOW_GRID=!SHOW_GRID; break;}
		}
		disp_settings();
	}
	if (BTN->justPressed())
		BTN->drawButton(true);  // draw invert!
}


// ------------------------------------------------------------- //
void scr_menu_settings_on_enter(uint TimeStamp){
	myTFT.clear_screen(BG_COLOR);
	menu_pg_num=0;
	draw_all_buttons();
	disp_settings();
	_DRAW_X_
}

void scr_menu_settings_on_touch(uint TimeStamp){
	for (uint8_t i=0;i<NUM_BTNS_PER_PAGE;i++)
			btn_ctrl(&all_buttons[menu_pg_num][i],i);

		// btn_ctrl(&NAV_PREV,BNUM_NAV_PREV);
		// btn_ctrl(&NAV_NEXT,BNUM_NAV_NEXT);
}

// ------------------------------------------------------------- //
void scr_menu_settings_initialize(Screen* S){
	S->set_func_per_second(do_nothing);
	S->set_func_per_minute(do_nothing);
	S->set_func_per_hour(do_nothing);
	S->set_func_on_enter(scr_menu_settings_on_enter);
	S->set_func_on_exit(do_nothing);
	S->set_func_on_touch(scr_menu_settings_on_touch);
}