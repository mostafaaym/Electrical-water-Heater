/*
 * Cooling.c
 *
 *  Created on: Sep 5, 2023
 *      Author: lenovo
 */

#include "Cooling.h"


void START_COOL (void){

	DIO_WriteChannel(COOL_PIN  ,PIN_HIGH);
}


void STOP_COOL (void)
{
	DIO_WriteChannel(COOL_PIN  ,PIN_LOW);
}


void START_HEAT (void)
{
	DIO_WriteChannel(HEAT_PIN  ,PIN_HIGH);

}


void STOP_HEAT (void)
{
	DIO_WriteChannel(HEAT_PIN  ,PIN_LOW);
	
}