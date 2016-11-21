/*
 * uart.c
 *
 *  Created on: Oct 30, 2016
 *      Author: VIJOY-PC
 */

#include "main.h"

/*--------------------------------------------------------------------
 * void uart_init(uint32_t baud)
 * This function initialises the port,clock,baud rate and interrupts
 * for UART0
---------------------------------------------------------------------*/
void uart_init(uint32_t baud)
{
	//STEP1: Clock Config
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;		//Clock gate enable for PORTA
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;		//Clock gate enable for UART0
    SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);  	//MCGFLLCLK as UART0

	//STEP2: Pin Config
	PORTA_PCR1 |= PORT_PCR_MUX(2); 			//ALT2 mode for UART0_Rx
	PORTA_PCR2 |= PORT_PCR_MUX(2);			//ALT2 mode for UART0_Tx

	//STEP3: Disable TX and RX before making changes to UART0 registers
	UART0_C2&= ~(UART0_C2_TE_MASK|UART0_C2_RE_MASK);

	//STEP4: UART frame config
	UART0_BDH |= UART_BDH_SBNS(0);			// 1 STOP bit
	UART0_C1  |= UART_C1_M(0);				// 8 BIT mode
	UART0_C1  |= UART_C1_PE(0);				// NO PARITY

	//STEP5: Baud rate setup
	uint32_t divisor;
	divisor = (SystemCoreClock/16)/baud ;
	UART0_BDH = ((divisor >> 8) & UART_BDH_SBR_MASK);
	UART0_BDL = (divisor & UART_BDL_SBR_MASK);

	 //STEP6: Interrupt enable
	 NVIC_EnableIRQ(UART0_IRQn); 			//Enable at NVIC
//	 UART0_C2 |= UART0_C2_TIE_MASK; 		//Peripheral interrupt enable (TX)
	 UART0_C2 |= UART0_C2_RIE_MASK;			//Peripheral interrupt enable (RX)

	 // Re-enable TX and RX bits
	 UART0_C2 |= UART0_C2_TE_MASK ;
	 UART0_C2 |= UART0_C2_RE_MASK ;

}

