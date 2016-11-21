/*
 * logger.c
 *
 *  Created on: Oct 30, 2016
 *      Author: VIJOY-PC
 */

#include "main.h"

void LOG_0(uint8_t * data)
{
#ifdef LOG
	for (int i=0;*data!='\0';i++)
	{
		//Wait until TX buffer is emplty or transmission complete flag is set
		while(!((UART0_S1&UART_S1_TDRE_MASK)|(UART0_S1&UART_S1_TC_MASK)));
	    UART0_D = *data;	// Send the character
	    data++;				//point to next character
	}
#endif
}

void LOG_1(uint8_t * data, uint32_t  param)
{
#ifdef LOG
	LOG_0(data);
	uint8_t dest[20];
	itoa(dest,param,16);
	LOG_0(dest);
#endif
}

void LOG_2(uint8_t * data, float param)
{
#ifdef LOG
	LOG_0(data);
	char *dest;
	char temp[20];
	dest = temp;
	dest = ftoa(param);
	LOG_0(dest);
#endif
}

int8_t itoa(int8_t *str, int32_t data, int32_t base)
{
	int8_t* str1 = str;
	int isNeg = 0;
	if (data < 0)
	{
		isNeg = 1;
		data = -data;
	}

	if (data == 0)
	{
		*str++ = '0';
		*str++ = '\0';
		return 1;
	}

	int length = 0;
	while (data != 0)
	{
		int8_t reminder = data% base;
		data = data / base;
		if (reminder > 9)
		{
			*str++ = (reminder - 10) + 'a';
		}
		else
		{
			*str++ = reminder + '0';
		}
		length++;
	}
	if (isNeg)
	{
		*str++ = '-';
		length++;
	}
	*str++ = '\0'; //End of character

	int8_t* src = str1;

	int index = 0;
	uint8_t temp;
	while (index<length / 2)
	{
		temp = *(src + index);
		*(src + index) = *(src + length - index - 1);
		*(src + length - index - 1) = temp;
		index++;
	}
	if (index == (length/2))
		return 1;
	else
		return 0;
}

uint8_t myAtoi(uint8_t *str)
{
    uint8_t res,res1,res2; // Initialize result

    // Iterate through all characters of input string and
    // update result

    	if(str[0] >= 'A' && str[0] <= 'F')
    	{
    		res1 = str[0] - 0x37;
    		res1 = res1 * 16;
    	}
    	else
    	{
    		res1 = str[0] - 0x30;
    		res1 = res1 * 16;
    	}

    	if(str[1] >= 'A' && str[1] <= 'F')
    	{
    		res2 = str[1] - 0x37;
    	}
    	else
    		res2 = str[1] - 0x30;

    	res = res1 + res2;
    // return result.
    return res;
}

typedef union {
long	L;
float	F;
}	LF_t;

/*
 * This function is taken from www.geeksforgeeks.org
 */
char *ftoa(float f)
{
	long mantissa, int_part, frac_part;
	short exp2;
	LF_t x;
	char *p;
	static char outbuf[15];

	if (f == 0.0)
	{
		outbuf[0] = '0';
		outbuf[1] = '.';
		outbuf[2] = '0';
		outbuf[3] = 0;
		return outbuf;
	}
	x.F = f;

	exp2 = (unsigned char)(x.L >> 23) - 127;
	mantissa = (x.L & 0xFFFFFF) | 0x800000;
	frac_part = 0;
	int_part = 0;

	if (exp2 >= 23)
		int_part = mantissa << (exp2 - 23);
	else if (exp2 >= 0)
	{
		int_part = mantissa >> (23 - exp2);
		frac_part = (mantissa << (exp2 + 1)) & 0xFFFFFF;
	}
	else /* if (exp2 < 0) */
		frac_part = (mantissa & 0xFFFFFF) >> -(exp2 + 1);

	p = outbuf;

	if (x.L < 0)
		*p++ = '-';

	if (int_part == 0)
		*p++ = '0';
	else
	{
		itoa(p, int_part, 10);
		while (*p)
			p++;
	}
	*p++ = '.';

	if (frac_part == 0)
		*p++ = '0';
	else
	{
		char m, max;
		max = sizeof (outbuf) - (p - outbuf) - 1;
		if (max > 7)
			max = 7;
		/* print BCD */
		for (m = 0; m < max; m++)
		{
			/* frac_part *= 10;	*/
			frac_part = (frac_part << 3) + (frac_part << 1);

			*p++ = (frac_part >> 24) + '0';
			frac_part &= 0xFFFFFF;
		}
		/* delete ending zeroes */
		for (--p; p[0] == '0' && p[-1] != '.'; --p)
			;
		++p;
	}
	*p = 0;

	return outbuf;
}
