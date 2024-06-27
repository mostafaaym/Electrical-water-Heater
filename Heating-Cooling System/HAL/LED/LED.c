/*
 * LED.c
 *
 * Created: 9/5/2023 2:30:56 PM
 *  Author: Ammar Yasser
 */ 
#include "LED.h"


void LED0_ON(void)
{
	DIO_WriteChannel(LED_PIN,PIN_HIGH);
}

void LED0_OFF(void)
{
	DIO_WriteChannel(LED_PIN,PIN_LOW);
}

void LED0_Toggle(void) 
{
	DIO_FlipChannel(LED_PIN);
}