#ifndef EEPROM_STUFF_H
	#define EEPROM_STUFF_H
#endif

#ifndef PWM_BACKLIGHT_H
	#include "pwm_backlight.h"
#endif

#include <EEPROM.h>

#ifndef ARX_DEBUGLOG_H
    #include <DebugLog.h>
#endif

#define EEPROM_SIZE 512 // in bytes
// ---- EEPROM Addresses ----- //
#define    AUTO_BL_ADDR 20
#define PIEZO_MUTE_ADDR 25
#define DEBUG_INFO_ADDR 30
#define SCREEN_NUM_ADDR 35
#define PWM_LVL_ADDR 40
#define BL_ADDR 500

#ifndef GLOBALS_H
    #include "../globals.h"
#endif

#ifndef PIEZO_STUFF_H
		#include "piezo_stuff.h"
#endif


void writeEepromInt(int value, int location){
  EEPROM.write(location, value);
  EEPROM.write(location + 1, value >> 8);
  LOG_INFO("Wrote "+String(value)+" to addr# "+String(location));
}

int readEepromInt(int location){
  int val;
  LOG_INFO("Reading from addr# "+String(location));
  val = (EEPROM.read(location + 1) << 8);
  val |= EEPROM.read(location);

  return val;
}

void init_eeprom(){
	EEPROM.begin(EEPROM_SIZE);

	auto_backlight=EEPROM.read(AUTO_BL_ADDR);
	PIEZO_MUTE=EEPROM.read(PIEZO_MUTE_ADDR);

	PWM_LVL=readEepromInt(PWM_LVL_ADDR);
	if (!(PWM_LVL>=1400 && PWM_LVL<=PWM_LIMIT))
		PWM_LVL=PWM_DEFAULT;


	// LOG_DEBUG("\n------------ EEPROM stored stettings ------------");
	// LOG_DEBUG("auto_backlight: "+String(auto_backlight));
	// LOG_DEBUG("PIEZO_MUTE: "+String(PIEZO_MUTE));
	// LOG_DEBUG("screen_num: "+String(EEPROM.read(SCREEN_NUM_ADDR)));
}
