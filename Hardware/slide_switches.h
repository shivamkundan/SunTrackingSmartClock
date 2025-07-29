#ifndef SLIDE_SWITCHES_H
	#define SLIDE_SWITCHES_H
#endif


// ------------ Switches ------------ //
#define TOUCH_EN_PIN 3
#define SLIDE_SWITCH_PIN 6

void init_slide_switches(){
	// Touch EN
	pinMode(TOUCH_EN_PIN, INPUT_PULLUP);
	pinMode(SLIDE_SWITCH_PIN, INPUT_PULLUP);
}
