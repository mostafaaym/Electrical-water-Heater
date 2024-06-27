/*
 * Heating-Cooling System.c
 *
 * Created: 9/4/2023 7:23:39 PM
 * Author : abdel
 */ 


#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "System.h"



int main(void)
{
    SYS_init();
    
    while(1)
	{
	    switch (MODE)
		{
		    case ON:
			{
			    MODE_ON();
			    break;
		    }
		    case OFF:
			{
			    MODE_OFF();
			    break;
		    }
		    case SETTING:
			{
			    MODE_Set();
			    break;
		    }
			
			default:
			break;
	    }
    }
}

/*
ON/OFF_Button_Interrupt : To switch between ON and OFF States.
*/

ISR(INT2_vect)
{
	if(MODE==OFF)
	{
		MODE = ON;
		desired_temp = EEPROM_read(0x0000);
	}
	else if (MODE==ON || MODE==SETTING)
	{
		MODE = OFF;
	}
}

/*
TIMER1_Interrupt (A) : It triggers the ISR every 100ms. So, it makes the temperature
measure flag equals one to enable the ADC to do the work.
*/

ISR(TIMER1_COMPA_vect)
{
	temp_measure_flag = 1;
}

/*
TIMER1_Interrupt (B) : It triggers the ISR every 1 second. So, it toggles the
toggle flag for the LED and the Seven Segment. and counts to keep it in
ON_STATE if nothing is pressed during in ON or SETTING modes for 5 secs.
*/

ISR(TIMER0_COMP_vect)
{
	if ((MODE==SETTING) || (MODE==ON)){
		setting_counter++;
		if(setting_counter % 4 == 0)
		{
			toggle_flag ^= 1;
		}
		if (setting_counter > 20)
		{
			
			// Write the new desired temperature in EEPROM
			MODE = ON;
		}
	}
}