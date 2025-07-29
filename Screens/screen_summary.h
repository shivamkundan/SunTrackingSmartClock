#ifndef COMMON_H
	#include "common.h"
#endif

#define S_TXT_COLOR SECONDARY_TXT_COLOR
// ------------------------------------------------ Declare string objects ------------------------------------------------ //
Shivam_TXT             IN_label = Shivam_TXT( 15, 210, FreeMonoBold16pt7b, 1, S_TXT_COLOR, BG_COLOR);
Shivam_TXT    next_event_t_str  = Shivam_TXT(100, 295, FreeMonoBold18pt7b, 1, S_TXT_COLOR, BG_COLOR);
Shivam_TXT            AT_label  = Shivam_TXT(125, 290, FreeMonoBold12pt7b, 1, S_TXT_COLOR, BG_COLOR);
#define START_ROW_ELEV 250
#define START_COL_elev 190
Shivam_TXT hours_remaining_elev = Shivam_TXT(START_COL_elev-100, START_ROW_ELEV,    FreeMonoBold36pt7b, 1,   TXT_COLOR, BG_COLOR);
Shivam_TXT 			 hours_elev = Shivam_TXT(START_COL_elev,     START_ROW_ELEV-30, FreeMonoBold14pt7b, 1,   TXT_COLOR, BG_COLOR);
Shivam_TXT 	mins_remaining_elev = Shivam_TXT(START_COL_elev,     START_ROW_ELEV,    FreeMonoBold36pt7b, 1,   TXT_COLOR, BG_COLOR);
Shivam_TXT 		   minutes_elev = Shivam_TXT(START_COL_elev+100, START_ROW_ELEV+30, FreeMonoBold14pt7b, 1,   TXT_COLOR, BG_COLOR);
Shivam_TXT       event_name_str = Shivam_TXT(                 5,               198, FreeMonoBold20pt7b, 1, S_TXT_COLOR, BG_COLOR);

// ----------------------- Pre-computed vals for drawing ------------------------ //
#define AZM_RAD 18
#define ORIG_X 440
#define ORIG_Y 265

// ----------------------------------- Diagrams ----------------------------------- //
void draw_azm_marker(int in_angle, uint radius, uint color, uint color2)
/* Draws circular marker at given in_angle */
{
	float x=ORIG_X+AZM_RAD*cos(in_angle*RADIAN_MULT+ANGLE_OFFSET);
	float y=ORIG_Y+AZM_RAD*sin(in_angle*RADIAN_MULT+ANGLE_OFFSET);
	myTFT.tft.drawLine(ORIG_X, ORIG_Y, x, y, color2);
	myTFT.tft.fillCircle( ORIG_X, ORIG_Y, 1 ,color2);
	myTFT.tft.fillCircle( x, y, radius ,color);
}

void draw_azm_diagram(int day_num, int mm, int yy, int today_minute, time_t localTime)
/* For drawing current azimuth */
{
		// ----------------- Draw azm circle ----------------- //
		myTFT.tft.drawCircle(ORIG_X, ORIG_Y, AZM_RAD, RED);

		// ----------------- Draw current azm marker ----------------- //
		uint32_t curr_azm=AZM_ARR[mm-1][day_num-1][(int)today_minute/AZM_MULT];
		draw_azm_marker(curr_azm, 3, YELLOW, LIGHTGREY);

		// ----------------- Retrieve sunrise/sunset angles ----------------- //
		uint32_t sunrise_angle = SUNRISE_ANGLE_ARR[mm-1][get_day_of_month(localTime)-1];
		uint32_t sunset_angle  = SUNSET_ANGLE_ARR [mm-1][get_day_of_month(localTime)-1];

		// ----------------- Draw sunrise/sunset markers ----------------- //
		draw_azm_marker(sunrise_angle, 1, LIGHTGREY, BG_COLOR);
		draw_azm_marker(sunset_angle, 1, LIGHTGREY, BG_COLOR);

		// ----------------- Show current azm value ----------------- //
		Shivam_TXT azm_str = Shivam_TXT(ORIG_X, ORIG_Y-AZM_RAD-10, Font4x5Fixed,      2, DARKGREY, BG_COLOR);
		azm_str.begin(myTFT.tft);
		azm_str.print_tft_ralign(String(curr_azm));
}

void draw_diagrams(time_t TimeStamp)
/* Draw both elevation and azimuth diagrams */
{
	time_t localTime = convert_to_local_time(TimeStamp);
	// Retrieve current date/time
	int day_num=get_day_of_month(localTime);
	int mm=convert_to_tmelements(localTime).Month;
	int yy=convert_to_tmelements(localTime).Year+UNIX_START_YEAR;
	uint16_t today_minute=get_minute_of_day(localTime);

	int day_of_year = get_day_of_year(localTime);

	int yT=_yTop;
	int yB=_yBottom;

	/*Mar 3 to Nov 1*/
	if (day_of_year<=MAR_3 || day_of_year>=NOV_1){
		yT=35; yB=yT+ELEV_DIAG_HEIGHT;
	}
	int zero_line_y_pos = draw_elevation_diagram (day_num,mm,yy,today_minute,yT,yB);

	draw_x_labels(zero_line_y_pos);
	draw_azm_diagram (day_num,mm,yy,today_minute,localTime);
}

// ------------------------------------------------------------------------------ //
void display_remaining_time(int diff)
/* Displays the actual hours & minutes till event. */
{
	String HH_=secondsToHH(abs(diff));
	String MM_=secondsToMM(abs(diff));
	if (HH_=="00"){

		mins_remaining_elev.set_pos(60,225);
		if (MM_=="00"){
			mins_remaining_elev.print_tft_middle("NOW");
		}
		else{
			String mins;
			if (MM_[0]=='0')
				mins=String(MM_[1])+ (MM_[1]=='1'? " minute":" minutes");
			else
				mins=String(MM_)+" minutes";

			mins_remaining_elev.print_tft_middle(mins);

			IN_label.set_x_pos(0);
		}
	}
	else{
		mins_remaining_elev.set_pos(START_COL_elev, mins_remaining_yPos);
		minutes_elev.set_y_pos(mins_remaining_yPos-30);

		hours_elev.set_y_pos(hrs_remain_yPos-30);
		hours_remaining_elev.set_y_pos(hrs_remain_yPos);

		hours_elev.print_tft_no_prev_bg  (HH_=="01" ? "hour" : "hours");
		minutes_elev.print_tft_no_prev_bg(MM_=="01" ? "minute" : "minutes");

		hours_remaining_elev.print_tft_no_prev_bg(HH_);
		mins_remaining_elev.print_tft_no_prev_bg(MM_);
		IN_label.set_pos(15,8+((hrs_remain_yPos-30)+(mins_remaining_yPos-30))/2);
	}
}

void scr_summary_main(time_t TimeStamp, int index_offset)
/* Shows countdown to next(+offset) event */
{
	// Clear the background area
	// myTFT.tft.fillRect(0,  base_y_pos, SCREEN_W, SCREEN_H-base_y_pos-20, LIGHTGREY);
	// myTFT.tft.fillRect(100,  0, SCREEN_W-220, base_y_pos, LIGHTBLACK);
	myTFT.clear_screen(BG_COLOR);

	// -------------------- Draw diagrram -------------------- //
	// Draws both alt &  (tiny) azm diagrams
	draw_diagrams(TimeStamp);

	// ----------------- Find index of next event ----------------- //
	uint16_t index=calc_event_index(TimeStamp);
	index+=index_offset;

	// ----------------- Calc time diff from event ----------------- //
	String event_name = get_event_type(index%NUM_ITEMS_PER_DAY);
	time_t localTime = convert_to_local_time(TimeStamp);
	int next=retrieve_time_from_index(TimeStamp,index);
	int diff = next - (int)localTime;

	// ----------------- Print remaining time ----------------- //
	display_remaining_time(diff);

	// ----------------- Print next event name ----------------- //
	event_name_str.set_y_pos(L1_pos);
	event_name_str.print_tft_middle_no_bg(event_name);

	// ----------------- Print time of event ----------------- //
	next_event_t_str.print_tft_middle(get_readable_time(convert_to_local_time(next)));

	// ----------------- Print symbols ----------------- //
	IN_label.print_tft_no_prev_bg("in");
	AT_label.print_tft_no_prev_bg("@");
}

// ----------------------------------------------------
void scr_summary_per_second(uint TimeStamp){

	// LOG_INFO("");

	// ----------------- Find index of next event ----------------- //
	uint16_t index=calc_event_index(TimeStamp);
	// index+=index_offset;

	time_t localTime = convert_to_local_time(TimeStamp);
	int next = convert_to_local_time(retrieve_time_from_index(TimeStamp,index));
	int diff = next - (int)localTime;
	// LOG_INFO("diff: "+String(diff));

	if (diff<60 && diff>0){
		// Erase previous text
		myTFT.tft.fillRect(50, SCREEN_H-140, SCREEN_W-100, 50, BG_COLOR);
		String s=String(diff)+" s";
		mins_remaining_elev.set_pos(60,225);
		mins_remaining_elev.print_tft_middle(s);
	}
}

void scr_summary_per_minute(uint TimeStamp){
    scr_summary_main(TimeStamp,0);
}

void scr_summary_on_enter(uint TimeStamp){
	scr_summary_main(TimeStamp,0);
}

// ----------------------------------------------------
void scr_summary_initialize(Screen* S){
	S->set_func_per_second(scr_summary_per_second);
	S->set_func_per_minute(scr_summary_per_minute);
	S->set_func_per_hour(do_nothing);
	S->set_func_on_enter(scr_summary_on_enter);
	S->set_func_on_exit(do_nothing);
	S->set_func_on_touch(do_nothing);

	IN_label.begin(myTFT.tft);
	next_event_t_str.begin(myTFT.tft);
	AT_label.begin(myTFT.tft);
	hours_remaining_elev.begin(myTFT.tft);
	hours_elev.begin(myTFT.tft);
	mins_remaining_elev.begin(myTFT.tft);
	minutes_elev.begin(myTFT.tft);
	event_name_str.begin(myTFT.tft);
}