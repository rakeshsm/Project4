/*
 * led.h
 *
 *  Created on: Oct 10, 2016
 *      Author: VIJOY-PC
 */

#ifndef INCLUDES_LED_H_
#define INCLUDES_LED_H_


void led_init(void);

#define R(b_color) TPM2_C0V=TPM2_MOD *(b_color)		// Red with brightness b_color
#define G(b_color) TPM2_C1V=TPM2_MOD *(b_color)		// Green with brightness b_color
#define B(b_color) TPM0_C1V=TPM0_MOD *(b_color)		// Blue with brightness b_color

#endif /* INCLUDES_LED_H_ */
