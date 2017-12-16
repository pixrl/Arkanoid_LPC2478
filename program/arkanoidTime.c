#include "arkanoidTime.h"

void timeWrapping(unsigned long *value, unsigned long wrapValue){
	(*value) = ((*value) % wrapValue);
}
void setHour(volatile unsigned long *rtcValue, tU16 ifIncrease){
	unsigned long clockHour = (*rtcValue);
	if(ifIncrease)
		clockHour += 1;
	else
		clockHour -= 1;
	timeWrapping(&clockHour, 24);
	(*rtcValue) = clockHour;
}
void setMinuteOrSecond(volatile unsigned long *rtcValue, tU16 ifIncrease){
	unsigned long clockMinuteOrSecond = (*rtcValue);
	if(ifIncrease)
		clockMinuteOrSecond += 1;
	else
		clockMinuteOrSecond -= 1;
	timeWrapping(&clockMinuteOrSecond, 60);
	(*rtcValue) = clockMinuteOrSecond;
}
/*void setRtcHour(tU16 addValue){
	if(addValue){
		setRTC(&RTC_HOUR, INCREMENT);
	}
	else{
		setRTC(&RTC_HOUR, DECREMENT);
	}
}
void setRtcMin(tU16 addValue){
	if(addValue){
		if(RTC_MIN == 59){
			setRtcHour(INCREMENT);
			setRTC(&RTC_MIN, INCREMENT);
		}
		else
			setRTC(&RTC_MIN, INCREMENT);
	}
	else{
		if(RTC_MIN == 0){
			setRtcHour(DECREMENT);
			setRTC(&RTC_MIN, DECREMENT);
		}
		else
			setRTC(&RTC_MIN, DECREMENT);
	}
}
void setRtcSec(tU16 addValue){
	if(addValue){
		if(RTC_SEC == 59){
			setRtcMin(INCREMENT);
			setRTC(&RTC_SEC, INCREMENT);
		}
		else
			setRTC(&RTC_SEC, INCREMENT);
	}
	else{
		if(RTC_SEC == 0){
			setRtcMin(DECREMENT);
			setRTC(&RTC_SEC, DECREMENT);
		}
		else
			setRTC(&RTC_SEC, DECREMENT);
	}
}*/
