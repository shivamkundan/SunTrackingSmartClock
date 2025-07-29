#ifndef SCREENS_H
	#define SCREENS_H
#endif

#ifndef COMMON_H
	#include "common.h"
#endif

// Import all screens
#include "screen_green.h"
#include "screen_summary.h"
#include "screen_detailed.h"
#include "screen_twilight.h"
#include "screen_earth_orbit.h"
#include "screen_daylight_diff.h"
#include "screen_azm.h"
#include "screen_altitude.h"
#include "screen_alt_azm.h"

#include "screen_world_clock.h"
#include "screen_analog_clk.h"
#include "screen_daylen.h"
#include "screen_EoT.h"
#include "screen_next_event.h"
#include "screen_next_5.h"
#include "screen_temp_humid.h"

#include "screen_batt_power.h"
#include "screen_error.h"

#include "info_screens/screen_rtc_info.h"
#include "info_screens/screen_prog_info.h"
#include "info_screens/screen_tz_info.h"
#include "info_screens/screen_mem_info.h"

#include "menu_screens/screen_menu.h"
#include "menu_screens/screen_menu_screens.h"
#include "menu_screens/screen_menu_settings.h"
#include "menu_screens/screen_backlight.h"
#include "menu_screens/screen_menu_info.h"

struct ScreenContainer{
	Screen S;
	std::function<void(Screen*)> init_func;
};

// Declare all screens
ScreenContainer SC[] = {
	{Screen("GREEN",      NONE),   	scr_green_initialize },
	{Screen("SUMMARY",    MEDIUM), 	scr_summary_initialize },
	{Screen("DETAILED",   MEDIUM),	scr_detailed_initialize },
	{Screen("TWILIGHT",   SMALL),	scr_twilight_initialize },
	{Screen("ALTITUDE",   SMALL),	scr_altitude_initialize },
	{Screen("AZIMUTH",    SMALL),	scr_azm_initialize },
	{Screen("ALT/AZM",    SMALL),	scr_alt_azm_initialize },
	{Screen("WORLD",      MEDIUM),	scr_wclk_initialize },

	{Screen("EARTH ORBIT",LARGE),	scr_earth_orbit_initialize },
	{Screen("DAY DIFF",   LARGE),	scr_daylight_diff_initialize },
	{Screen("DAY LEN",    LARGE),	scr_daylen_initialize },
	{Screen("EoT",        LARGE),	scr_EoT_initialize },
	{Screen("NEXT 5",     LARGE),	scr_next_five_initialize },
	{Screen("NEXT",       SMALL),	scr_next_initialize },
	{Screen("ANALOG_CLK", MEDIUM),	scr_analog_clk_initialize },

	{Screen("TEMP/HUMID", SMALL),	scr_temp_humid_initialize },
	{Screen("RTC_INFO",   LARGE),	scr_rtc_info_initialize },
	{Screen("TZ_INFO",    LARGE),	scr_tz_info_initialize },
	{Screen("PROG_INFO",  LARGE),	scr_prog_info_initialize },
	{Screen("MEM_INFO",   LARGE),	scr_mem_info_initialize },
	{Screen("BATTERY",    SMALL),	scr_batt_power_initialize },
	{Screen("ERROR",     NONE) ,scr_error_initialize},

	{Screen("MENU",       SMALL) ,	scr_menu_initialize},
	{Screen("MENU_SCREENS",SMALL) ,scr_menu_screens_initialize},
	{Screen("MENU_SETTINGS",SMALL),scr_menu_settings_initialize},
	{Screen("BACKLIGHT", SMALL),    scr_backlight_initialize},
	{Screen("MENU_INFO_SCREENS", SMALL) ,scr_menu_info_initialize},
};

void init_screens(){
	LOG_TRACE("");

	NUM_SCREENS=sizeof(SC)/sizeof(SC[0]);
	LOG_DEBUG("NUM_SCREENS: "+String(NUM_SCREENS));

	// Initialize all screens
	for (int i=0;i<NUM_SCREENS;i++){
		SC[i].init_func(&(SC[i].S));
		scr_list[i]=&(SC[i].S);
		LOG_DEBUG(String(i)+": "+scr_list[i]->name);
	}

	// Used for displaying screen names in menus
	make_name_list(scr_list);
	make_name_list_info_screens(scr_list, NUM_SCREENS);

}
