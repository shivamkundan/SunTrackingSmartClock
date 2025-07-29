#ifndef PUSH_BUTTONS_H
	#define PUSH_BUTTONS_H
#endif

// ------------ Push buttons ------------ //
#define BTN1_PIN 20
#define BTN2_PIN 21
#define BTN3_PIN 22

#define PUSH_BTN_DEBOUNCE_T 20

#define _PRESSED_(PIN) {digitalRead(PIN)==LOW}

int push_btn_countdown=0;

void init_push_buttons(){
/* Set push button pins to input_pullup. */
	pinMode(BTN1_PIN, INPUT_PULLUP);
	pinMode(BTN2_PIN, INPUT_PULLUP);
	pinMode(BTN3_PIN, INPUT_PULLUP);
}
