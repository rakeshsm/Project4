/*
 * rtc.c
 *
 *  Created on: Nov 24, 2016
 *      Author: rakes
 */

#include "main.h"
int totalAlarmSeconds;
void rtc_Clock_Configuration (void)
{
	MCG_C1 |= MCG_C1_IRCLKEN_MASK; //Enable internal reference clock
	MCG_C2 &= ~(MCG_C2_IRCS_MASK);  //Internal Reference Clock -->Slow

	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	//**RTC_CLKIN**//
	PORTC_PCR1 |= (PORT_PCR_MUX(1));       //PTC1 as RTC_CLKIN
	SIM_SOPT1 |= SIM_SOPT1_OSC32KSEL(0b10);  //32 Khz clock source for RTC

	//**32KHz Frequency**//
	SIM_SOPT2 |= SIM_SOPT2_CLKOUTSEL(0b100); //Clockout pin --> 32 KHz

	PORTC_PCR3 |= PORT_PCR_MUX(5); //PTC3 as CLKOUT
}

void rtc_init(void)
{
    /*enable the clock to SRTC module register space*/
	SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;

	/*Clear Registers, reset All RTC registers*/
    RTC_CR  = RTC_CR_SWR_MASK;
    RTC_CR  &= ~RTC_CR_SWR_MASK;

    if (RTC_SR & RTC_SR_TIF_MASK){
        RTC_TSR = 0x00000000;   //  this action clears the TIF
    }

    /*Set time compensation parameters*/
    RTC_TCR = RTC_TCR_CIR(1) | RTC_TCR_TCR(0xFF);

    NVIC_EnableIRQ(RTC_IRQn);
    NVIC_EnableIRQ(RTC_Seconds_IRQn);
    /*Enable Seconds Interrupt*/
    RTC_IER |= RTC_IER_TSIE_MASK; //Seconds interrupt enable

    /*Timer enable*/
    RTC_SR |= RTC_SR_TCE_MASK;

    RTC_TSR = 0xFF;

    /*Enable Alarm Interrupt*/
   	RTC_IER |= RTC_IER_TAIE_MASK; //Alarm interrupt enable
}

void setAlarm(alarmMinutes,alarmSeconds){

	totalAlarmSeconds = alarmMinutes*60 + alarmSeconds;
    RTC_TAR = totalAlarmSeconds;
}

