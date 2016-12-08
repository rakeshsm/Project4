/*
 * tsi.h
 *
 *  Created on: Nov 29, 2016
 *      Author: rakes
 */

#ifndef INCLUDES_FIRMWARE_I_TSI_H_
#define INCLUDES_FIRMWARE_I_TSI_H_

void touch_init(uint32_t channel_mask);
int touch_data(int channel);
void scan_start(int channel);
uint16_t scan_data(void);




#endif /* INCLUDES_FIRMWARE_I_TSI_H_ */
