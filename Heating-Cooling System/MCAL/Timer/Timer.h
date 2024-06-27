/*
 * Timer.h
 *
 * Created: 9/4/2023 8:29:17 PM
 *  Author: Ammar Yasser
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "MCU.h"
#include "BIT_MATH.h"


#define	OCIE1A_BIT					4
#define	GLOBAL_INT_PIN				7	

/*******************	Timer 0 *************************/
void Timer0_Init(void);
void Timer0_Start(void);
void Timer0_Stop(void);
void Timer0_SetDelay(Uint_32 Delay_Ms);

/*******************	Timer 1 *************************/
void Timer1_Init(void);
void Timer1_Start(void);
void Timer1_Stop(void);
void Timer1_SetDelay(Uint_32 Delay_Ms);
void Timer1_INT_disable(void);
void Timer1_INT_enable(void);



#endif /* TIMER_H_ */