/*
 * i2c.c
 *
 *  Created on: Nov 21, 2016
 *      Author: rakes
 */
#include "main.h"
void I2C_Init()
{
	/* enable clock of I2C1 */
	SIM->SCGC4 |= (1 << SIM_SCGC4_I2C1_SHIFT) & SIM_SCGC4_I2C1_MASK;
	SIM->SCGC5 |= (1 << SIM_SCGC5_PORTE_SHIFT) & SIM_SCGC5_PORTE_MASK;

	/* configure port E pins to I2C operation */
	PORTE->PCR[1] = PORT_PCR_MUX(6); /* SCL */
	PORTE->PCR[0] = PORT_PCR_MUX(6); /* SDA */

	/* Baud rate = busspeed / (mult * SCL divider), ICR = 0x12 -> SCL divider = 64, MUL=0x00 -> mul =1*/
	I2C1->F = I2C_F_MULT(0x00) | I2C_F_ICR(0x12); /* divide by 64 instead, so 375 kHz */


	/* enable the I2C1 module */
	I2C1->C1 = (1 << I2C_C1_IICEN_SHIFT) & I2C_C1_IICEN_MASK;
}


/**
 * Reads register byte from an I2C slave
 */
uint8_t I2C_ReadRegister(register uint8_t slaveId, register uint8_t registerAddress)
{
	/* loop while the bus is still busy */
	I2C_WaitWhileBusy();

	/* send I2C start signal and set write direction, also enables ACK */
	I2C_SendStart();

	/* send the slave address and wait for the I2C bus operation to complete */
	I2C_SendBlocking(I2C_WRITE_ADDRESS(slaveId));

	/* send the register address */
	I2C_SendBlocking(registerAddress);

	/* signal a repeated start condition */
	I2C_SendRepeatedStart();

	/* send the read address */
	I2C_SendBlocking(I2C_READ_ADDRESS(slaveId));

	/* switch to receive mode but disable ACK because only one data byte will be read */
	I2C_EnterReceiveModeWithoutAck();

	/* read a dummy byte to drive the clock */
	I2C_ReceiverModeDriveClock();

	/* stop signal */
	I2C_SendStop();

	/* fetch the last received byte */
	register uint8_t result = I2C1->D;
	return result;
}

/**
 * Reads an 8-bit register from an I2C slave
 */
void I2C_WriteCommand(register uint8_t slaveId, register uint8_t value)
{
	/* loop while the bus is still busy */
	I2C_WaitWhileBusy();

	/* send I2C start signal and set write direction*/
	I2C_SendStart();

	/* send the slave address and wait for the I2C bus operation to complete */
	I2C_SendBlocking(I2C_WRITE_ADDRESS(slaveId));

	/* send the command value */
	I2C_SendBlocking(value);

	/* issue stop signal by clearing master mode. */
	I2C_SendStop();
}



void I2C_ReadRegisters(register uint8_t slaveId, register uint8_t command, register uint8_t registerCount, register uint8_t *buffer)
{
	if (registerCount > 1)
	{
		I2C_ReadMultipleRegisters(slaveId, command, registerCount, buffer);
	}
	else
	{
		register uint8_t result = I2C_ReadRegister(slaveId, command);
		buffer[0] = result;
	}
}


static void I2C_ReadMultipleRegisters(register uint8_t slaveId, register uint8_t startRegisterAddress, register uint8_t registerCount, uint8_t *const buffer)
{

	uint8_t TEM;

	/* loop while the bus is still busy */
	I2C_WaitWhileBusy();

	/* send I2C start signal and set write direction, also enables ACK */
	I2C_SendStart();

	/* send the slave address and wait for the I2C bus operation to complete */
	I2C_SendBlocking(I2C_WRITE_ADDRESS(slaveId));

	/* send the register address */
	I2C_SendBlocking(startRegisterAddress);

	/* signal a repeated start condition */
	I2C_SendRepeatedStart();

	/* send the read address */
	I2C_SendBlocking(I2C_READ_ADDRESS(slaveId));

	/* switch to receive mode and assume more than one register */
	I2C_EnterReceiveModeWithAck();

	/* for all remaining bytes, read */
	uint8_t index = 0;
	while (registerCount-- > 0)
	{
		/* fetch and store value */
		register uint8_t value = I2C1->D;
		buffer[index++] = value;

		/* wait for completion */
		I2C_Wait();
	}

	/* disable ACK and read second-to-last byte */
	I2C_DisableAck();

	/* fetch and store value */
	buffer[index++] = I2C1->D;

	/* wait for completion */
	I2C_Wait();

	/* stop signal */
	I2C_SendStop();

	/* fetch the last received byte */
	buffer[index++] = I2C1->D;
}
