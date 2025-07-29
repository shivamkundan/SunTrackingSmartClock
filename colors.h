#ifndef COLORS_H
	#define COLORS_H
#endif

// --------------------------------------------------------------------------------
// Color format: RGB565  (see https://barth-dev.de/online/rgb565-color-picker/)
// --------------------------------------------------------------------------------

// Color definitions
#define BLUE 0x001F ///<   0,   0, 255
#define PINK 0xFC18 ///< 255, 130, 198
#define LIGHT_RED 0xAAAA
// ----


#define RED       0xF800 ///< 255,   0,   0
#define MAROON    0x7800 ///< 123,   0,   0
#define BROWN     0x9240 ///< 150,  75,   0
#define ORANGE 	  0xFD20 ///< 255, 165,   0
#define DARK_ORANGE 0xE480 ///< 224, 146, 0
#define YELLOW    0xFFE0 ///< 255, 255,   0

#define OLIVE       0x7BE0 ///< 123, 125,   0
#define GREENYELLOW 0xAFE5 ///< 173, 255,  41
#define GREEN       0x07E0 ///<   0, 255,   0
#define DARKGREEN   0x03E0 ///<   0, 125,   0
#define LIGHTGREEN  0x8705 ///< 133, 224,  41
#define DARKCYAN    0x03EF ///<   0, 125, 123
#define SUPER_DARK_GREEN 0x1100

#define PURPLE    0x780F ///< 123,   0, 123
#define MAGENTA   0xF81F ///< 255,   0, 255
#define CYAN      0x07FF ///<   0, 255, 255
#define NAVY      0x000F ///<   0,   0, 123

#define BLACK     0x0000 ///<   0,   0,   0
#define DARKGREY  0x7BEF ///< 123, 125, 123
#define LIGHTGREY 0xC618 ///< 198, 195, 198
#define GREY      0x0821
#define WHITE     0xFFFF ///< 255, 255, 255

#define LIGHTBLACK 0x3186  // from https://barth-dev.de/online/rgb565-color-picker/


// =================== COLORS =================== //
// theme 0
#define BG_COLOR 			BLACK
#define TXT_COLOR 			YELLOW
#define SECONDARY_TXT_COLOR CYAN
#define TERTIARY_TXT_COLOR  RED
#define MINI_TXT_COLOR 		WHITE
#define BOTTOM_BAR_COLOR 	RED
#define HORIZON_COLOR 		WHITE


// #define BIG_SUN_COLOR HX8357_YELLOW

// #define NOON_DIAGRAM_ARC_COLOR WHITE


// // // theme 1
// // #define BG_COLOR HX8357_WHITE
// // #define TXT_COLOR HX8357_BLACK
// // #define SECONDARY_TXT_COLOR HX8357_RED
// // #define TERTIARY_TXT_COLOR ILI9341_OLIVE
// // #define MINI_TXT_COLOR HX8357_BLACK
// // #define BOTTOM_BAR_COLOR ILI9341_MAROON

// // #define HORIZON_COLOR MINI_TXT_COLOR
// // #define SUN_PATH_COLOR ILI9341_MAROON

// // #define NOON_DIAGRAM_ARC_COLOR BLACK
// // #define MW_ICON_COLOR ILI9341_MAGENTA

// // #define BIG_SUN_COLOR ILI9341_ORANGE
// // #define SUN_MARKER_COLOR ILI9341_ORANGE

// =============================================

// Icons and buttons
#define MW_ICON_COLOR 	  MAGENTA
#define STATUS_ICON_COLOR ORANGE
#define ICON_STRIP_COLOR  BG_COLOR
#define BL_SCR_BTN_COLOR  ORANGE

// Plot/curve colors
#define DAY_DIFF_CURVE_COLOR RED
#define DAY_LEN_CURVE_COLOR  PURPLE
#define EOT_CURVE_COLOR 	 GREEN



// =============================================
// Gradients

#define RED_L1  0x5800  // 88,  0, 0
#define RED_L2  0x6000  // 99,  0, 0
#define RED_L3  0x6800  // 110, 0, 0
#define RED_L4  0x7800  // 122, 0, 0
#define RED_L5  0x8000  // 132, 0, 0
#define RED_L6  0x9800  // 154, 0, 0
#define RED_L7  0xA000  // 164, 0, 0
#define RED_L8  0xB000  // 176, 0, 0
#define RED_L9  0xC000  // 198, 0, 0
#define RED_L10 0xD800  // 220, 0, 0
#define RED_L11 0xF000  // 242, 0, 0


#define WHITE_L1 0x5ACB  //  88,  88,  88
#define WHITE_L2 0x6B6D  // 110, 110, 110
#define WHITE_L3 0x8430  // 132, 132, 132
#define WHITE_L4 0x9CD3  // 154, 154, 154
#define WHITE_L5 0xB596  // 176, 176, 176
#define WHITE_L6 0xC638  // 198, 198, 198
#define WHITE_L7 0xDEFB  // 220, 220, 220
#define WHITE_L8 0xF79E  // 242, 242, 242

// For time travel
#define FUTURE_FRAME_COLOR GREEN
#define PAST_FRAME_COLOR ORANGE

// // TZ colors utc+10 to utc-11

// // Sun is at utc-11:
// RED, RED_L8, RED_L7,
// RED_L6, RED_L5, RED_L4,
// RED_L3, RED_L2, RED_L1,
// LIGHTBLACK, LIGHTGREY, BLACK

// RED + 11 shades + LIGHTBLACK



// uint8_t red;
// uint8_t green;
// uint8_t blue;

// uint16_t Rgb565 = 0;

// Rgb565 = (((red & 0b11111000)<<8) + ((green & 0b11111100)<<3)+(blue>>3));

// Rgb565 = (((red & 0xf8)<<8) + ((green & 0xfc)<<3)+(blue>>3));


// RGB565 = (((RGB888&0xf80000)>>8) + ((RGB888&0xfc00)>>5) + ((RGB888&0xf8)>>3));


