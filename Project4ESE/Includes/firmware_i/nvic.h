/*
 * nvic.h
 *
 *  Created on: Oct 30, 2016
 *      Author: VIJOY-PC
 */

#ifndef INCLUDES_SYSTEM_NVIC_H_
#define INCLUDES_SYSTEM_NVIC_H_

#define ARM_INTERRUPT_LEVEL_BITS          2

#define EnableInterrupts __asm(" CPSIE i");
#define DisableInterrupts __asm(" CPSID i");

void enable_irq (int);
void disable_irq (int);
void set_irq_priority (int, int);

#endif /* INCLUDES_SYSTEM_NVIC_H_ */
