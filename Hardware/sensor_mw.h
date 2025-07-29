#ifndef SENSOR_MW_H
	#define SENSOR_MW_H
#endif

#ifndef ARX_DEBUGLOG_H
	#include <DebugLog.h>
#endif

// ------------ MW sensor ------------ //
#define MW_DET_PIN 11

bool curr_MW;
bool prev_MW;

void init_mw_sensor(){
/* Set mw sensor pin to input. */
	pinMode(MW_DET_PIN, INPUT);
}

void MW_sensor_manager()
/* Handles presence detection and sleep enable/disable */
{
	curr_MW=digitalRead(MW_DET_PIN);



	// if (SLEEP_MODE==false){
	// 	uint T_now=millis();
	// 	MW_T_DIFF=T_now-MW_DET_T;
	// 	// LOG_DEBUG ("curr_MW: "); LOG_DEBUG(curr_MW);
	// 	// LOG_DEBUG (", prev_MW: "); LOG_DEBUG(prev_MW);
	// 	// LOG_DEBUG ("MW_T_DIFF: "); LOG_DEBUG((int)MW_T_DIFF/1000);
	// 	if (curr_MW!=prev_MW){
	// 		if (screen_num!=SCREEN_GREEN)
	// 			blit_MW_icon(curr_MW);
	// 		if (curr_MW){
	// 			MW_num_detects+=1;
	// 			LOG_DEBUG("MW_num_detects: "+String(MW_num_detects));
	// 		}
	// 	}
	// 	if (MW_T_DIFF>GOTO_SLEEP_MS){
	// 		go_to_sleep();
	// 	}
	// }
	// else{
	// 	if (curr_MW==true)
	// 		wake_from_sleep();
	// 	else
	// 		sleep_refresh();
	// }
	// prev_MW=curr_MW;
	// // LOG_DEBUG ("SLEEP_MODE: "); LOG_DEBUG(SLEEP_MODE);
}