/*
 * Timer.c
 *
 * Created: 9/4/2023 8:29:36 PM
 *  Author: Ammar Yasser
 */ 

#include "Timer.h"


Uint_8 Init_Value=0;
Uint_32 Namber_OVRflows=0;



void Timer0_Init(void)
{
	TCCR0 |= 0x00;
	TIMSK |= 0x01;
	SREG  |= 0x80;
}
void Timer0_Start(void)
{
	TCCR0 |=0x05;
}
void Timer0_Stop(void)
{
	CLR_BIT(TCCR0, 0);
	CLR_BIT(TCCR0, 1);
	CLR_BIT(TCCR0, 2);
}
void Timer0_SetDelay(Uint_32 Delay_Ms)
{
	Uint_8 Tick_Time =(1024 /8);
	Uint_32 Total_Ticks =(Delay_Ms * 1000) / Tick_Time ;
	Namber_OVRflows =Total_Ticks /256;
	Init_Value =256 - (Total_Ticks % 256);
	TCNT0 =Init_Value;
	Namber_OVRflows++;
}

/*******************	Timer 1 *************************/
void Timer1_Init(void)
{
	TCCR1B |= 0x08;
	TIMSK  |=0x10;
	SREG  |=0x80;
	
}
//clock

void Timer1_Start(void)
{
	 TCCR1B |= 0x05;
}


// zero  -->stop timer
void Timer1_Stop(void)
{
	CLR_BIT(TCCR1B, 0);
	CLR_BIT(TCCR1B, 1);
	CLR_BIT(TCCR1B, 2);
}


void Timer1_SetDelay(Uint_32 Delay_Ms )
{
	if (Delay_Ms <= 4000) 
	{
		Uint_32 Tick_Time = (1024 / 8);
		Uint_8 Num_Tick = (Delay_Ms * 1000) / Tick_Time;
		OCR1A = (Num_Tick - 1);
	}
}

void Timer1_INT_disable(void)
{
	
	// Disable Interrupts when Comparing with values A and B
	CLR_BIT(TIMSK,OCIE1A_BIT);
	
}


void Timer1_INT_enable(void)
{
	
	// Enable Interrupts when Comparing with values A and B
	SET_BIT(TIMSK,OCIE1A_BIT);
}