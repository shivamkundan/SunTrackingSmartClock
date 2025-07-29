#ifndef PIEZO_STUFF_H
	#define PIEZO_STUFF_H
#endif

#define PIEZO_PIN 2

bool PIEZO_MUTE; // load from eeprom
bool MANUAL_T = false;
bool MANUAL_T_DECR = false;

void single_beep();
void double_beep();
void triple_beep();

void flip_piezo(uint T){
	digitalWrite(PIEZO_PIN,HIGH);
	delay(T);
	digitalWrite(PIEZO_PIN,LOW);
}

void init_piezo(){
	pinMode(PIEZO_PIN,OUTPUT);
	pinMode(PIEZO_PIN,INPUT_PULLDOWN);
	if (PIEZO_MUTE)
		return;
	double_beep();
}

void single_beep(){
	if (PIEZO_MUTE || MANUAL_T || MANUAL_T_DECR)
		return;
	flip_piezo(200);

}

void double_beep(){
	if (PIEZO_MUTE || MANUAL_T || MANUAL_T_DECR)
		return;
	flip_piezo(50);

	delay(40);

	flip_piezo(50);
}

void triple_beep(){
	if (PIEZO_MUTE || MANUAL_T || MANUAL_T_DECR)
		return;

	flip_piezo(40);

	delay(30);
	flip_piezo(40);

	delay(30);
	flip_piezo(40);

}