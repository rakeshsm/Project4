/*
 * main.h
 *
 *  Created on: Nov 21, 2016
 *      Author: rakes
 */

#ifndef INCLUDES_MAIN_H_
#define INCLUDES_MAIN_H_

#include "stdint.h"
#include "MKL25Z4.h"
#include "firmware_i\i2c.h"
#include "middle_i\ds1631.h"
#include "firmware_i\logger.h"
#include "firmware_i\nvic.h"
#include "firmware_i\uart.h"
#include "firmware_i\rtc.h"
#include "firmware_i\tsi.h"
#include "firmware_i\led.h"
#define LOG
#define NCHANNELS 16
extern int seconds;
extern int minutes;
extern int onesecond;
extern int hours;
extern int totalAlarmSeconds;
extern int alarmSet;
extern volatile uint16_t raw_counts[NCHANNELS];
extern volatile uint16_t base_counts[NCHANNELS];
extern uint32_t enable_mask;

#endif /* INCLUDES_MAIN_H_ */
