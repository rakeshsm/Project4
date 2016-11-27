/*
 * rtc.h
 *
 *  Created on: Nov 24, 2016
 *      Author: rakes
 */

#ifndef INCLUDES_FIRMWARE_I_RTC_H_
#define INCLUDES_FIRMWARE_I_RTC_H_
#include "main.h"

void rtc_Clock_Configuration (void);
void rtc_init(void);
void RTC_Seconds_IRQHandler(void);
void RTC_IRQHandler(void);
void setAlarm(int alarmMinutes, int alarmSeconds);

#endif /* INCLUDES_FIRMWARE_I_RTC_H_ */
