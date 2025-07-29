#ifndef Shivam_PicoW_TFT_H
	#include <Shivam_PicoW_TFT.h>
#endif

#ifndef COLORS_H
	#include "../colors.h"
#endif

#ifndef SCREEN_CLASS_H
	#include "ScreenClass.h"
#endif

void scr_green_on_enter(uint TimeStamp){
	myTFT.clear_screen(YELLOW);
}

void scr_green_initialize(Screen* S){
	S->set_func_per_second(do_nothing);
	S->set_func_per_minute(do_nothing);
	S->set_func_per_hour(do_nothing);
	S->set_func_on_enter(scr_green_on_enter);
	S->set_func_on_exit(do_nothing);
	S->set_func_on_touch(do_nothing);
	S->show_power_info=false;
	S->show_backlight_info=false;
	S->show_scr_num=false;
	S->show_mw_icon=false;
	S->show_icons=false;

}