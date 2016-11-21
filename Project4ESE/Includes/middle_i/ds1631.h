/*
 * ds1631.h
 *
 *  Created on: Nov 21, 2016
 *      Author: rakes
 */
#ifndef DS1631_H_
#define DS1631_H_


#define DS1631_SLAVE_ADDRESS 0x48
#define CMD_START_CONVERSION 0x51
#define CMD_READ_TEMP 0xAA

void start_Temperature_Conversion (void);
float read_Temperature (void);

#endif
