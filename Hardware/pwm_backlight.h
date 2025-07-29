#ifndef PWM_BACKLIGHT_H
	#define PWM_BACKLIGHT_H
#endif

// #ifndef EEPROM_STUFF_H
// 	#include "eeprom_stuff.h"
// #endif

// Backlight related

#define DELAY_TIME 60 //in seconds?
#define PWM_L1 1400
#define PWM_L2 8192
#define PWM_L3 16384
#define PWM_L4 32768
#define PWM_LIMIT 65535
#define MIN_PWM 1400
#define MAX_PWM 16384
#define PWM_DEFAULT 16000


uint16_t PWM_LVL;// = MIN_PWM;
uint16_t PREV_PWM_LVL = PWM_LVL;


void set_pwm_val(uint16_t new_pwm)
/* Set new PWM level */
{
	gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);
	uint slice_num = pwm_gpio_to_slice_num(PWM_PIN);
	pwm_set_wrap(slice_num, PWM_LIMIT);
	pwm_set_chan_level(slice_num, PWM_CHAN_A, new_pwm);
	pwm_set_enabled(slice_num, true);
	PWM_LVL=new_pwm;
}

// ------------------------
// Brightness levels, experimentally obtained
#define b1 19+1
#define b2 28+1
#define b3 66+1
#define b4 250+1


void set_auto_light_lvl()
/* Sets global var PWM_LVL to scaled value */
{

	// PWM_LVL=4000;
	// uint32_t B=1023-avg_brightness;

	// if (B<b1){
	// 	PREV_PWM_LVL=PWM_LVL;
	// 	PWM_LVL=PWM_L1;
	// }

	// else if (B<b2) {
	// 	PREV_PWM_LVL=PWM_LVL;
	// 	PWM_LVL=PWM_L2;
	// }

	// else if (B<b3) {
	// 	PREV_PWM_LVL=PWM_LVL;
	// 	PWM_LVL=PWM_L3;
	// }
	// else{
	// 	PREV_PWM_LVL=PWM_LVL;
	// 	PWM_LVL=PWM_L4;
	// }
}