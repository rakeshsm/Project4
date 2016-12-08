/*
 * main.c
 *
 *  Created on: Nov 21, 2016
 *      Author: rakes
 */
#include "main.h"

static int i = 0;
int seconds , minutes, onesecond, hours;
int touchValue[2];
int inputAlarmseconds =0, inputAlarmMinutes =0;
int count =0;
int alarmSet = 1;


void displayTouchBasedAlarmTime(){

	touchValue[1] = touch_data(10);
	if((touchValue[1] > touchValue[0] + 2) && count >0){
		inputAlarmseconds++;
	}
	if((touchValue[1] < (touchValue[0] -2)) && count >0){
		inputAlarmseconds--;
	}
	count =1;

	touchValue[0] = touchValue[1];

	if(inputAlarmseconds > 59){
		inputAlarmMinutes++;
		inputAlarmseconds =0;
	}

	if(inputAlarmseconds < 0){
		inputAlarmseconds = 59;
		if(inputAlarmMinutes > 0){
			inputAlarmMinutes--;
		} else{
			inputAlarmseconds =0;
		}
	}

	LOG_2("\rAlarm Minutes: Seconds = ", inputAlarmMinutes);
	LOG_2(" : ", inputAlarmseconds);
}


int main(void)
{
	void (*funcPoint)() ;
	funcPoint= &displayTouchBasedAlarmTime;
	float temp;
	led_init();
	I2C_Init();
	uart_init(BAUD_RATE);


	//Initialize TSI Sensor With channel 10
	touch_init(1 << 10);

	/*start the temperature conversion*/
	start_Temperature_Conversion();

	LOG_0("\n\rReading temperature ");
	temp = read_Temperature();
//	Log temp on UART
	LOG_2("\n\rTemperature = ",temp);
	LOG_0(" degree Celsius");

	LOG_0("\n\n\n\rUse Touch Slide to Set Alarm time, Press Enter After Setting\n");
	touchValue[0]=1;
	while(alarmSet){
		funcPoint();
	}

	rtc_Clock_Configuration();
	rtc_init();
	setAlarm(inputAlarmMinutes, inputAlarmseconds);
	LOG_0("\n\rAlarm is set\n");
	alarmSet =2;
	LOG_0("\n\rStarting RTC\n");
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

