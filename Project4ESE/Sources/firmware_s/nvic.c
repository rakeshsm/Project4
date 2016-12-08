/*
 * nvic.c
 *
 *  Created on: Oct 30, 2016
 *      Author: VIJOY-PC
 */

#include "main.h"

uint8_t packet_byte,rx_byte=0,dma_complete=0;
uint32_t overflow_count;
int totalAlarmSeconds;
volatile uint16_t raw_counts[NCHANNELS];
volatile uint16_t base_counts[NCHANNELS];
uint32_t enable_mask;

void UART0_IRQHandler (void)
{
/* When rx_byte =1:
 * Incoming packet is stored into the circular buffer
 * length from the second byte is checked to ensure packet completion
 * Packet complete flag is checked to enable processing of packet
 */

  if (UART0_S1&UART_S1_RDRF_MASK)
  	{
	  	alarmSet=0;
	  	packet_byte = UART0_D;
	  	UART0_D = packet_byte;
		UART0_C2 &= ~UART0_C2_RIE_MASK; 		//Peripheral interrupt disable (RX)
		rx_byte = 1;
  	}

  if ((UART0_S1&UART_S1_TDRE_MASK)||(UART0_S1&UART_S1_TC_MASK))
    {

    }
}

void DMA0_IRQHandler(void)
{
	LOG_0("\r\nDMA complete !!!\r\n");
	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;
	//end_time();
	dma_complete = 1;
}


void TSI0_IRQHandler(void)
{
    // Save data for channel
    uint32_t channel = (TSI0_DATA & TSI_DATA_TSICH_MASK) >> TSI_DATA_TSICH_SHIFT;
    raw_counts[channel] = scan_data();

    // Start a new scan on next enabled channel
    for(;;) {
        channel = (channel + 1) % NCHANNELS;
        if ((1 << channel) & enable_mask) {
            scan_start(channel);
            return;
        }
    }
}

void RTC_Seconds_IRQHandler(void){

	onesecond = 1;
	seconds = RTC_TSR;
	if (seconds >59){
		minutes++;
		RTC_SR &= ~RTC_SR_TCE_MASK;
		RTC_TSR = 0x00; //Reset counter
		seconds = RTC_TSR;
		RTC_SR |= RTC_SR_TCE_MASK;
		int alarmTime = RTC_TAR;
		RTC_TAR = alarmTime - 60;
	}
	if(minutes > 59){
		hours++;
		minutes =0;
	}
}


void RTC_IRQHandler(void){
	if(alarmSet ==2){
		LOG_0("   Alarm time!!!!");
		R(1);
		G(0);
		B(0);
	}
	RTC_TAR = totalAlarmSeconds;
}


