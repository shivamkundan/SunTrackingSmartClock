#ifndef RTC_H
	#define RTC_H
#endif

#ifndef DS3232RTC_H_INCLUDED
	#include <DS3232RTC.h>      // https://github.com/JChristensen/DS3232RTC
#endif

void init_rtc(DS3232RTC* myRTC)
/* Initialize rtc, sync internal clk to rtc */
{
	time_t t;
	tmElements_t tm;
	tm.Year = 2024-1970;
	tm.Month = 7;
	tm.Day = 31;
	tm.Hour = 7+6;
	tm.Minute = 45;
	tm.Second = 10;
	t = makeTime(tm);
	delay(200);
	// myRTC->set(t);   // use the time_t value to ensure correct weekday is set
	setTime(t);
	delay(200);

	myRTC->begin();

	// setSyncProvider(myRTC->get); 	// sync internal clock to rtc every 5 mins
}