/*
 * main.c
 *
 *  Created on: Nov 21, 2016
 *      Author: rakes
 */
#include "main.h"

static int i = 0;
int seconds , minutes, onesecond, hours;
int main(void)
{
	float temp;

	//I2C_Init();
	uart_init(BAUD_RATE);

	/*start the temperature conversion*/
	start_Temperature_Conversion();

	LOG_0("\n\rReading temperature ");
	temp = read_Temperature();
	//Log temp on UART
	LOG_2("\n\rTemperature = ",temp);
	LOG_0(" degree Celsius");

	rtc_Clock_Configuration();
	rtc_init();

	int alarmSeconds = 13; // take this as input
	int alarmMinutes = 0; // take this as input
	setAlarm(alarmMinutes, alarmSeconds);
	LOG_0("\n\r Alarm is set");
	LOG_0("\n\rHH : MM : SS Format \n");

	while(1){
		if(onesecond ==1){
			LOG_2("\r",hours);
			LOG_2(" : ",minutes);
			LOG_2(" : ",seconds);
			onesecond = 0;
		}
	}
	return 0;
}

