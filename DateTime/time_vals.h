#ifndef TIME_VALS_H
	#define TIME_VALS_H
#endif

#ifndef OUTPUT_ALL_MONTHS
	#include "_output_all_months.h"
#endif

#ifndef _TIMESTAMPS_2024_H_
	#include "timestamps_2024.h"
#endif

#include "sun_dist_all.h"
#include "day_len_all.h"

// #ifndef GLOBALS_H
//     #include "../globals.h"
// #endif

long  OFFSET_T_SECS=0;

#include "azm_data/azimuths.h"
#include "elevation_data/elevations.h"
const int** AZM_ARR[]={AZM_JAN,AZM_FEB,AZM_MAR,AZM_APR,AZM_MAY,AZM_JUN,AZM_JUL,AZM_AUG,AZM_SEP,AZM_OCT,AZM_NOV,AZM_DEC};
const float** ELEV_ARR[]={elev_jan_2024,elev_feb_2024,elev_mar_2024,elev_apr_2024,elev_may_2024,elev_jun_2024,elev_jul_2024,elev_aug_2024,elev_sep_2024,elev_oct_2024,elev_nov_2024,elev_dec_2024};
// const int** AZM_ARR[]={AZM_M,AZM_M,AZM_MAR,AZM_APR,AZM_MAY,AZM_M,AZM_M,AZM_M,AZM_M,AZM_M,AZM_M,AZM_M};
// const float** ELEV_ARR[]={ELV_M,ELV_M,elev_mar_2024,elev_apr_2024,elev_may_2024,ELV_M,ELV_M,ELV_M,ELV_M,ELV_M,ELV_M,ELV_M};

const int* MIN_ELEV_ARRAY [] = {elev_mins_jan_2024, elev_mins_feb_2024, elev_mins_mar_2024, elev_mins_apr_2024, elev_mins_may_2024, elev_mins_jun_2024, elev_mins_jul_2024, elev_mins_aug_2024, elev_mins_sep_2024, elev_mins_oct_2024, elev_mins_nov_2024, elev_mins_dec_2024};
const int* MAX_ELEV_ARRAY [] = {elev_maxs_jan_2024, elev_maxs_feb_2024, elev_maxs_mar_2024, elev_maxs_apr_2024, elev_maxs_may_2024, elev_maxs_jun_2024, elev_maxs_jul_2024, elev_maxs_aug_2024, elev_maxs_sep_2024, elev_maxs_oct_2024, elev_maxs_nov_2024, elev_maxs_dec_2024};

// ------------------------------------------------------------------------------------ //
int32_t* SUNRISE_ANGLE_ARR [] = {JAN_SUNRISE_ANGLE, FEB_SUNRISE_ANGLE, MAR_SUNRISE_ANGLE, APR_SUNRISE_ANGLE, MAY_SUNRISE_ANGLE, JUN_SUNRISE_ANGLE, JUL_SUNRISE_ANGLE, AUG_SUNRISE_ANGLE, SEP_SUNRISE_ANGLE, OCT_SUNRISE_ANGLE, NOV_SUNRISE_ANGLE, DEC_SUNRISE_ANGLE};
float*      NOON_ANGLE_ARR [] = {JAN_NOON_ANGLE,    FEB_NOON_ANGLE,    MAR_NOON_ANGLE,    APR_NOON_ANGLE,    MAY_NOON_ANGLE,    JUN_NOON_ANGLE,    JUL_NOON_ANGLE,    AUG_NOON_ANGLE,    SEP_NOON_ANGLE,    OCT_NOON_ANGLE,    NOV_NOON_ANGLE,    DEC_NOON_ANGLE};
int32_t*  SUNSET_ANGLE_ARR [] = {JAN_SUNSET_ANGLE,  FEB_SUNSET_ANGLE,  MAR_SUNSET_ANGLE,  APR_SUNSET_ANGLE,  MAY_SUNSET_ANGLE,  JUN_SUNSET_ANGLE,  JUL_SUNSET_ANGLE,  AUG_SUNSET_ANGLE,  SEP_SUNSET_ANGLE,  OCT_SUNSET_ANGLE,  NOV_SUNSET_ANGLE,  DEC_SUNSET_ANGLE};

// These vars save previous time vals
uint16_t prev_DD=1;
uint8_t prev_HH=99;
uint8_t prev_MM=99;
uint8_t prev_ss=99;

// #define _MIN_TS_ 1704088800 // Jan 1 2024 midnight
#define _MIN_TS_ 1735711200 // Jan 1 2025 midnight
#define _MAX_TS_ 1767247200 // Jan 1 2026 midnight

// Some basics
#define UNIX_START_YEAR 1970
#define NUM_MINS_IN_DAY 1440
#define NUM_SECS_IN_HOUR 3600
#define NUM_HOURS_IN_DAY 24
#define NUM_MONTHS_IN_YEAR 12

#define NUM_SECS_IN_DAY 24*60*60

#define NUM_DAYS_YEAR 366 // this is for 2024

#define DST_BEGIN_2024 1710057600  //Sun Mar 10 2024 03:00:00 GMT-0500 (CDT)
#define DST_END_2024   1730620800  //Sun Nov 03 2024 02:00:00 GMT-0600 (CST)

#define _DAYS_(D) {D*NUM_SECS_IN_DAY}
#define _MINUTES_(M) {M*60}
#define _HOURS_(H) {H*NUM_SECS_IN_HOUR}

// Special days' #
#define JAN_2 2     // Perihelion (closest point)
#define MAR_19 79   // Vernal equinox
#define JUN_20 172  // Summer solstice
#define JUL_5 187   // Aphelion (furthest point)
#define SEP_22 266  // Autumnal equinox
#define DEC_21 356  // Winter solstice

// This is for 2024 which is a leap year
#define JAN_1 1
#define FEB_1 32
#define MAR_1 61
#define APR_1 92
#define MAY_1 122
#define JUN_1 153
#define JUL_1 183
#define AUG_1 214
#define SEP_1 245
#define OCT_1 275
#define NOV_1 306
#define DEC_1 337

// For elev diagram
#define MAR_3 64


#define JAN_1_24_00_00_TS 1704088800
#define JAN_1_24_07_09_TS 1704114550

// // Special days' timestamps
// #define JAN_2_MIDNIGHT 1704175200
// #define JUL_5_MIDNIGHT 1720155600
// #define MAR_19_MIDNIGHT 1710824400
// #define JUN_20_MIDNIGHT 1718859600
// #define SEP_22_MIDNIGHT 1726981200
// #define DEC_21_MIDNIGHT 1734588000

#define NUM_REF_DAYS 4
uint ref_days[]{MAR_19,JUN_20,SEP_22,DEC_21};

// for screen_day_diff()
#define MIN_DAY_DIFF -145
#define MAX_DAY_DIFF 147

// int TIME_ZONE_DIFF_SECS=-18000;
#define TIME_ZONE_DIFF_HOURS_CST -6 	// CST
#define TIME_ZONE_DIFF_HOURS_CDT -6+1 	// CST
const int TIME_ZONE_DIFF_SECS_CDT = (TIME_ZONE_DIFF_HOURS_CDT)*NUM_SECS_IN_HOUR; // -18,000
const int TIME_ZONE_DIFF_SECS_CST = (TIME_ZONE_DIFF_HOURS_CST)*NUM_SECS_IN_HOUR; // -21,600
int TIME_ZONE_DIFF_SECS =TIME_ZONE_DIFF_SECS_CST;
bool DST=false;

enum event_type{MIDNIGHT_OFFSET, ASTRO_DAWN_OFFSET, NAUTICAL_DAWN_OFFSET, FIRST_LIGHT_OFFSET, SUNRISE_OFFSET, SOLAR_NOON_OFFSET, SUNSET_OFFSET, LAST_LIGHT_OFFSET, NAUTICAL_DUSK_OFFSET, ASTRO_DUSK_OFFSET };
#define NUM_ITEMS_PER_DAY 10 //number of time values stored for each day
const uint16_t START_INDEX=0; // to prevent reading too many old dates

#define BASE_YEAR 2023 // This is the start value for list of  years

int INDEX_OFFSET=0; // for screen_summary


// midnight, astro_dawn ,nautical_dawn, dawn, sunrise, solar_noon, sunset, dusk, nautical_dusk, astro_dusk

// repeat 2024 for 2025
uint32_t** all_years[3]={NULL,year_2024,year_2024};