/*'''
	Blank template for making a new screen.
'''*/

/**
 * A brief description. A more elaborate class description
 * @param bool somebool a boolean argument.
 * @see Test()
 * @return The test results
 */
#ifndef COMMON_H
	#include "common.h"
#endif

void scr_template_per_minute(uint TimeStamp){
		return;
}
void scr_template_per_second(uint TimeStamp){
	return;
}

void scr_template_per_hour(uint TimeStamp){
	return;
}
void scr_template_on_enter(uint TimeStamp){
	return;
}
void scr_template_on_touch(uint TimeStamp){
	return;
}
void scr_template_on_exit(uint TimeStamp){
	return;
}

void scr_template_initialize(Screen* S){
	S->set_func_per_second(scr_template_per_second);
	S->set_func_per_minute(scr_template_per_minute);
	S->set_func_per_hour(scr_template_per_hour);
	S->set_func_on_enter(scr_template_on_enter);
	S->set_func_on_exit(scr_template_on_exit);
	S->set_func_on_touch(scr_template_on_touch);
	S->show_power_info=false;
	S->show_backlight_info=false;
	S->show_mw_icon=false;
	S->show_icons=false;
}

