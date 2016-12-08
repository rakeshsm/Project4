/*
 * ds1631.c
 *
 *  Created on: Nov 21, 2016
 *      Author: rakes
 */

#include "main.h"
uint16_t MASK = 0x8000;
float MUL =64;
#define ResetMultiplciationfactor  MUL = 64.00;

void start_Temperature_Conversion(void)
{
	I2C_WriteCommand(DS1631_SLAVE_ADDRESS, CMD_START_CONVERSION);
}

float convert_temperature(uint16_t val){
	uint8_t i = 0, right_shift =14;
	float tempval, result = 0.00;
	float temp;

	for(i = 1 ; i < 15 ; i++){;
     temp = (val & (MASK >> i))>>right_shift;
     right_shift--;
     tempval = temp*MUL;
     MUL = MUL/2;
     result = result + tempval;
	}
	ResetMultiplciationfactor;
	return result;
}

float read_Temperature (void)
{
	uint8_t read_temp[3];
	uint16_t readvalue;
	float temp;
	I2C_ReadRegisters(DS1631_SLAVE_ADDRESS,CMD_READ_TEMP,2,read_temp);
	readvalue = ((read_temp[1] << 8) | read_temp[2]);
	temp = convert_temperature(readvalue);
	return temp;
}
