/*
 * Cooling.h
 *
 *  Created on: Sep 5, 2023
 *      Author: lenovo
 */

#ifndef COOLING_H_
#define COOLING_H_
#include <avr/io.h>
#include <avr/delay.h>
#include "MCU.h"
#include "BIT_MATH.h"
#include "DIO_CORE.h"


#define  COOL_PIN				PORTB_PIN5
#define  HEAT_PIN				PORTB_PIN4


void START_COOL (void);
void STOP_COOL (void);

void START_HEAT (void);
void STOP_HEAT (void);
#endif /* COOLING_H_ */
