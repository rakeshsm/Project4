/*
 * logger.h
 *
 *  Created on: Oct 30, 2016
 *      Author: VIJOY-PC
 */

#ifndef INCLUDES_SYSTEM_LOGGER_H_
#define INCLUDES_SYSTEM_LOGGER_H_

void LOG_0(uint8_t * data);
void LOG_1(uint8_t * data, uint32_t  param);
void LOG_2(uint8_t * data, float param);

int8_t itoa(int8_t *str, int32_t data, int32_t base);
uint8_t myAtoi(uint8_t *str);
char *ftoa(float f);

#endif /* INCLUDES_SYSTEM_LOGGER_H_ */
