/*
 * main.c
 *
 *  Created on: Nov 21, 2016
 *      Author: rakes
 */
#include "main.h"

static int i = 0;

int main(void)
{
	float temp;

	I2C_Init();
	uart_init(BAUD_RATE);

	/*start the temperature conversion*/
	start_Temperature_Conversion();

	LOG_0("\n\rReading temperature ");
	temp = read_Temperature();
	//Log temp on UART
	LOG_2("\n\rTemperature = ",temp);
	LOG_0(" degree Celsius");

	return 0;
}

