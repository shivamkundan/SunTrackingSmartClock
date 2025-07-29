// ================================================================= //
// ================================================================= //
// These strings HAVE to be global so the program can know previous positions
// and then selectively update the pixels for next frame.
// ================================================================= //
// ================================================================= //
#ifndef STRING_DEFS_H
	#define STRING_DEFS_H
#endif

#ifndef Shivam_TXT_H
	#include <Shivam_TXT.h>
#endif

#ifndef HARDWARE_H
    #include "Hardware/hardware.h"
#endif

#ifndef MY_FONTS_H
	#include "MyFonts/my_fonts.h"
#endif

#ifndef COLORS_H
	#include "colors.h"
#endif

// ---------------------------------------------------------------------------------------
// Main (large) time display
Shivam_TXT   timestr = Shivam_TXT(190, 62, FreeSansBold44pt7b, 1, TXT_COLOR, BG_COLOR);
Shivam_TXT   sec_str = Shivam_TXT(390, 40, FreeSansBold25pt7b, 1, TXT_COLOR, BG_COLOR);
Shivam_TXT am_pm_str = Shivam_TXT(400, 64, FreeSansBold10pt7b, 1, SECONDARY_TXT_COLOR,      BG_COLOR);

// Main (small) time display
Shivam_TXT timestr_small = Shivam_TXT(368, 21, FreeMonoBold14pt7b, 1, SECONDARY_TXT_COLOR, BG_COLOR);
Shivam_TXT sec_str_small = Shivam_TXT(  0, 20, FreeMonoBold9pt7b,  1, SECONDARY_TXT_COLOR, BG_COLOR);

// ---------------------------------------------------------------------------------------
// Show day+date on top left of screen
Shivam_TXT         day_str = Shivam_TXT( 0, 20, FreeMonoBold14pt7b, 1, SECONDARY_TXT_COLOR, BG_COLOR);
Shivam_TXT        date_str = Shivam_TXT( 0, 52, FreeMonoBold14pt7b, 1, SECONDARY_TXT_COLOR, BG_COLOR);

Shivam_TXT daydate_small = Shivam_TXT(0, 20, FreeMonoBold11pt7b, 1, SECONDARY_TXT_COLOR, BG_COLOR);
// ---------------------------------------------------------------------------------------
// Utils
Shivam_TXT current_str = Shivam_TXT(30, 		 SCREEN_H-1,  FreeMonoBold9pt7b, 1, BOTTOM_BAR_COLOR, BG_COLOR);
Shivam_TXT     pwm_str = Shivam_TXT(SCREEN_W-40, SCREEN_H-1,  FreeMonoBold9pt7b, 1, BOTTOM_BAR_COLOR, BG_COLOR);
Shivam_TXT scr_num_str = Shivam_TXT(0,  		 SCREEN_H-1,  Font4x5Fixed,      2, DARKGREY,         BG_COLOR);


#define NUM_STRINGS 11
Shivam_TXT* LL[NUM_STRINGS]={
	&timestr, &sec_str, &am_pm_str,
	&timestr_small, &sec_str_small,
	&day_str, &date_str, &daydate_small,
	&current_str,&pwm_str,&scr_num_str
};

void init_TXTs(Adafruit_HX8357 tft)
/* Initializes all TXT objects */ {
	for (uint8_t i=0;i<NUM_STRINGS;i++)
		LL[i]->begin(tft);
}