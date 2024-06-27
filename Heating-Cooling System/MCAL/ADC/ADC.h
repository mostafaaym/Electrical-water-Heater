/*
 * ADC.h
 *
 *  Created on: Aug 17, 2023
 *      Author: HP
 */

#ifndef MCAL_DIO_ADC_H_
#define MCAL_DIO_ADC_H_

#include <avr/delay.h>

#include "MCU.h"
#include "BIT_MATH.h"
#include "DIO_CORE.h"
#include "ADC_CFG.h"

void ADC_init(void);
Uint_16 ADC_read(void);

#endif /* MCAL_DIO_ADC_H_ */
