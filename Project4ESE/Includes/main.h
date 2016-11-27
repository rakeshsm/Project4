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
#define LOG
extern int seconds;
extern int minutes;
extern int onesecond;
extern int hours;
extern int totalAlarmSeconds;

#endif /* INCLUDES_MAIN_H_ */
