/*
 * System.c
 *
 * Created: 9/6/2023 2:42:01 AM
 *  Author: abdel
 */ 


/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  FileName.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "System.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)        
* \Description     : Describe this service                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/
void SYS_init(void){
	// Modules initialization
	ADC_init();
	Buttons_init();
	PORT_Init();
	Timer0_Init();
	Timer1_Init();
	Timer1_INT_enable();
	
	// ON_OFF_flag is in OFF mode initially
	MODE = OFF;
	
	// setting initial temp. and fill array
	if(EEPROM_read(0x0000) != 0xFF)
	{
		desired_temp = EEPROM_read(0x0000);
	}
	else
	{
		desired_temp = INIT_DESIRED_TEMP;
	}
	
	temp_arr_init();
	
	// Save desired temp in EEPROM
	// which is the INIT_DESIRED_TEMP.
	EEPROM_write(0x0000,(Uint_8) desired_temp);
	
}



/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/

void MODE_OFF(void)
{
	SSD_turn_off();
	LED0_OFF();
	STOP_COOL();
	STOP_HEAT();
	go_to_sleep();
}



/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/


 void MODE_ON(void){
	
	// if 100ms elapsed and flag is triggered
	// measure temperature from the sensor
	// add it to array and get the average
	
	if (temp_measure_flag == 1)
	{
		actual_temp = (ADC_read()*0.5);
		add_new_temp(temp_arr , actual_temp);
		avg_temp = calc_avg_temp(temp_arr);
		temp_measure_flag = 0;
	}
	
	SSD_write(actual_temp);
	
	// turn cooler or heater ON and OFF depending on
	// the average temperature measured from the array.
	
	change_temp();
	
	// Check if UP or DOWN buttons are pressed to
	// switch to the SETTING_MODE
	
	if(UP_pressed()==PRESSED || DOWN_pressed()==PRESSED){

		SSD_disable();
		setting_counter = 0;
		MODE = SETTING;
		
	}
}


/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/

void MODE_Set(void){
	
	
	LED0_OFF();
	STOP_COOL();
	STOP_HEAT();
	
	// to toggle the seven segment
	// while writing the desired temperature
	
	if(toggle_flag == 1){
		SSD_write(desired_temp);
	}
	else{
		SSD_turn_off();
	}
	
	// if UP or DOWN pressed, change the desired temp
	// as long as it's still in range
	
	if((UP_pressed() == PRESSED) && (desired_temp < MAX_TEMP))
	{
		desired_temp = desired_temp + 5;
		setting_counter = 0;
		SSD_write(desired_temp);
	}
	else if ((DOWN_pressed() == PRESSED) && (desired_temp > MIN_TEMP))
	{
		desired_temp = desired_temp - 5;
		setting_counter = 0;
		SSD_write(desired_temp);
	}
	
	EEPROM_write(0x0000,desired_temp);
	
}


/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/

void change_temp(void)
{
	if( (desired_temp < avg_temp + MARGIN_TEMP) && (desired_temp > avg_temp - MARGIN_TEMP) )
	{
		// Actual Temperature equals Desired Temperature
		// No need for Heating or Cooling
		LED0_OFF();
		STOP_COOL();
		STOP_HEAT();
	}
	else if(desired_temp < avg_temp + MARGIN_TEMP)
	{
		// Actual Temperature is Larger
		// we need the Cooling element
		
		LED0_OFF();
		START_COOL();
		STOP_HEAT();;
	}
	else if (desired_temp > avg_temp - MARGIN_TEMP)
	{
		// Actual Temperature is Smaller
		// we need the Heating element
		

		STOP_COOL();
		START_HEAT();
		if (toggle_flag == 1)
		{
			LED0_ON();
		}
		else 
		{
			LED0_OFF();
		}
	}
}


/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void temp_arr_init(void){
	Uint_16 first_temp = ADC_read()*0.5;
	
	for (Uint_8 i = 0; i<NUM_OF_TEMP_MEASURES; i++)
	{
		temp_arr[i]= first_temp;
	}
	
	avg_temp = calc_avg_temp(temp_arr);
	arr_counter = 0;
}


/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/



/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void add_new_temp(Uint_16 * arr , Uint_16 new_val)
{
	arr[arr_counter] = new_val;
	arr_counter ++;
	
	if (arr_counter == 10)
	{
		arr_counter = 0;
	}
}


/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
Uint_16 calc_avg_temp(Uint_16 * arr){
	Uint_16 sum = 0;
	Uint_16 avg;
	
	for(Uint_8 i=0; i<NUM_OF_TEMP_MEASURES; i++)
	{
		sum = sum + arr[i];
	}
	avg = (Uint_16) sum / NUM_OF_TEMP_MEASURES;
	return avg;
}

/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void go_to_sleep(void)
{
	
	MCUCR&=~(1<<SM0);
	MCUCR&=~(1<<SM1);
	MCUCR&=~(1<<SM2);
	
	MCUCR|=(1<<SE);

}
/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
