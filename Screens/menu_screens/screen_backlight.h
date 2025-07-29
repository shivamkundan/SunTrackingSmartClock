
#ifndef SCREEN_CLASS_H
	#include "ScreenClass.h"
#endif

#ifndef Shivam_PicoW_TFT_H
	#include <Shivam_PicoW_TFT.h>
#endif

#ifndef COLORS_H
	#include "../../colors.h"
#endif

#ifndef HARDWARE_H
	#include "../../Hardware/hardware.h"
#endif


#define SLIDER_BTN_W 30


uint16_t slider_ypos=80;
uint16_t slider_height=40;
uint16_t slider_start_x=50;
uint16_t slider_width=SCREEN_W-2*slider_start_x;


// x-range actual = 20 to 297

uint16_t slider_btn_xpos=80;
uint16_t slider_btn_width=SLIDER_BTN_W;

int prev_touch_x=slider_btn_xpos;

Shivam_TXT pwm_val_txt = Shivam_TXT(slider_ypos+slider_height+20, 200, FreeMonoBold11pt7b, 1, YELLOW, BG_COLOR);

#define PAD ((int) SLIDER_BTN_W*1.5)
#define CHECK_Y ay>slider_ypos && ay<slider_ypos+slider_height
#define CHECK_X ax>slider_btn_xpos-PAD && ax<slider_btn_xpos+slider_btn_width+PAD
#define SLIDER_TOUCH (CHECK_Y) && (CHECK_X)

#define MIN_LIMIT slider_start_x+25
#define MAX_LIMIT slider_start_x+slider_width-SLIDER_BTN_W-25


//   outline: Color of the outline (16-bit 5-6-5 standard)
//      fill: Color of the button fill (16-bit 5-6-5 standard)
// textcolor: Color of the button label (16-bit 5-6-5 standard)
#define __H 60
#define _BTN_AUTO_ btn_auto.initButtonUL(&myTFT.tft, NAV_PREV_X, 240, BUTTON_W,	__H, BG_COLOR,	LIGHTBLACK, WHITE, (char *) "Auto",	BUTTON_TEXTSIZE, BUTTON_TEXTSIZE);
#define _BTN_SAVE_ btn_save.initButtonUL(&myTFT.tft,        320, 240, BUTTON_W,	__H, BG_COLOR,	LIGHTBLACK, WHITE, (char *) "Save",	BUTTON_TEXTSIZE, BUTTON_TEXTSIZE);

#define _SHOW_VALS_(PW) (pwm_val_txt.print_tft_middle(String(slider_btn_xpos-slider_start_x)+" / "+String(PW)+" / "+String(log(PW)*100)+" / "+String(100*log(PW)/log(10))))

#define _DRAW_LINES_ {\
	myTFT.tft.drawLine(MIN_LIMIT, 70, MIN_LIMIT, 130, WHITE);\
	myTFT.tft.drawLine(MAX_LIMIT, 70, MAX_LIMIT, 130, WHITE);\
}

Adafruit_GFX_Button btn_auto, btn_save;

uint PW; //PWM val

void btn(Adafruit_GFX_Button* BTN, uint8_t btn_num){
	if (BTN->contains(ax, ay))
		BTN->press(true);
	else
		BTN->press(false);

	if (BTN->justReleased()){
		BTN->drawButton();  // draw normal

		if (btn_num==0)
			LOG_DEBUG("btn_auto");
		if (btn_num==1)
			LOG_DEBUG("btn_save");
	}
	if (BTN->justPressed())
		BTN->drawButton(true);  // draw invert!
}

void move_slider(uint16_t new_x){

	if (auto_backlight){
		auto_backlight=false;
		LOG_DEBUG("auto_backlight: "+String(auto_backlight));
		EEPROM.write(AUTO_BL_ADDR,auto_backlight);
		delay(50);
		_EEPROM_COMMIT_
	}
	slider_btn_xpos=new_x;
	prev_touch_x=slider_btn_xpos;


	if (new_x<MIN_LIMIT)
		PW=MIN_PWM;
	else if (new_x>MAX_LIMIT)
		PW=MAX_PWM;
	else
		PW=custom_map(new_x,slider_start_x,slider_start_x+slider_width-slider_btn_width,MIN_PWM, MAX_PWM);

	_SHOW_VALS_(PW);
	set_pwm_val(PW);
	_DRAW_LINES_

	LOG_DEBUG("new_x: "+String(new_x)+" / "+String(MIN_LIMIT)+" / "+String(MAX_LIMIT));
}

void slider(){
	if (SLIDER_TOUCH){
		LOG_DEBUG("touch: " +String(ax)+","+String(ay));
		// myTFT.tft.fillRect(slider_btn_xpos,slider_ypos,slider_btn_width,slider_height,RED);

		if (ax!=prev_touch_x){

			int diff=ax-prev_touch_x;
			LOG_DEBUG("ax-prev_touch_x: "+String(diff)+"\n");
			// incrementing value
			if (diff>0){
				myTFT.tft.fillRect(slider_btn_xpos,slider_ypos,slider_btn_width,slider_height,LIGHTBLACK);
				uint16_t new_x=slider_btn_xpos+(ax-prev_touch_x);
				if (new_x<=slider_start_x+slider_width-slider_btn_width)
					move_slider(new_x);
			}
			// decrementing value
			else if (diff<0){
				myTFT.tft.fillRect(slider_btn_xpos,slider_ypos,slider_btn_width,slider_height,LIGHTBLACK);
				uint16_t new_x=slider_btn_xpos-(prev_touch_x-ax);
				if (new_x>slider_start_x && new_x<slider_start_x+slider_width)
					move_slider(new_x);
			}
		}
	}
	else{
		myTFT.tft.fillRect(slider_btn_xpos,slider_ypos,slider_btn_width,slider_height,YELLOW);
	}
}

void scr_backlight_on_enter(uint TimeStamp){
	myTFT.clear_screen(BG_COLOR);
	PW=PWM_LVL;
	_SHOW_VALS_(PW);
	myTFT.tft.fillRect(slider_start_x,slider_ypos,slider_width,slider_height,LIGHTBLACK);
	myTFT.tft.fillRect(slider_btn_xpos,slider_ypos,slider_btn_width,slider_height,YELLOW);

	_DRAW_LINES_;

	btn_auto.drawButton();

	Shivam_TXT       clb = Shivam_TXT(225,     300,  FreeSansBold15pt7b, 1, LIGHTGREY, BG_COLOR);
	clb.begin(myTFT.tft);
	clb.print_tft(" X ");
}

void scr_backlight_on_exit(uint TimeStamp){
	LOG_DEBUG("leaving BL screen");
	writeEepromInt(PW, PWM_LVL_ADDR);
	_EEPROM_COMMIT_
}

void scr_backlight_on_touch(uint TimeStamp){
	if (touch_countdown!=0 && SLIDER_TOUCH)
			myTFT.tft.fillRect(slider_btn_xpos,slider_ypos,slider_btn_width,slider_height,RED);
		else
			myTFT.tft.fillRect(slider_btn_xpos,slider_ypos,slider_btn_width,slider_height,YELLOW);

		btn(&btn_auto,0);
		btn(&btn_save,1);
}

void scr_backlight_initialize(Screen* S){
	S->set_func_per_second(do_nothing);
	S->set_func_per_minute(do_nothing);
	S->set_func_per_hour(do_nothing);
	S->set_func_on_enter(scr_backlight_on_enter);
	S->set_func_on_exit(scr_backlight_on_exit);
	S->set_func_on_touch(scr_backlight_on_touch);

	pwm_val_txt.begin(myTFT.tft);

	_BTN_AUTO_;
	_BTN_SAVE_;
	S->show_power_info=false;
	S->show_backlight_info=false;
}