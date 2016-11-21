/*
 * uart.h
 *
 *  Created on: Oct 30, 2016
 *      Author: VIJOY-PC
 */

#ifndef INCLUDES_FW_LAYER_UART_H_
#define INCLUDES_FW_LAYER_UART_H_

#include <stdint.h>

void uart_init(uint32_t baud);
void UART0_IRQHandler (void);

#define BAUD_RATE       38400

#endif /* INCLUDES_FW_LAYER_UART_H_ */
