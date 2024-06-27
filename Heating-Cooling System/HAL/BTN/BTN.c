/*
 * BTN.c
 *
 * Created: 9/6/2023 3:05:37 PM
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
#include "BTN.h"

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


void Buttons_init(void){
	
	// Enable internal Pull-Up Resistor
	DIO_WriteChannel(UP_PIN,PIN_HIGH); 
	DIO_WriteChannel(ON_OFF_PIN,PIN_HIGH);
	DIO_WriteChannel(DOWN_PIN,PIN_HIGH);
	
	// This Following Section is for the external interrupt
	// assigned to the ON/OFF Button.
	
	// Enable Global Interrupt bit
	SET_BIT(SREG,GLOBAL_INT_PIN);
	
	// Trigger with Rising Edge
	SET_BIT(MCUCSR,ISC2);
	
	// Enable INT2 (External Interrupt)
	SET_BIT(GICR,INT2);
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


Uint_8 UP_pressed(void)
{
	Uint_8 button =1,temp=0;
	
	DIO_ReadChannel(UP_PIN,&button);
	
	//Loop to stop bouncing
	while(temp==0)
	{
		DIO_ReadChannel(UP_PIN,&temp);
	}
	
	_delay_ms(10);
	
	if (button == 0)
	{
		return PRESSED;
	}
	else
	{
		return NOT_PRESSED;
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


unsigned char DOWN_pressed(void){
	
	Uint_8 button =1,temp=0;
	
	DIO_ReadChannel(DOWN_PIN,&button);
	
	//Loop to stop bouncing
	
	while(temp==0)
	{
		DIO_ReadChannel(DOWN_PIN,&temp);
	}
	
	_delay_ms(10);
	
	if (button == 0)
	{
		return PRESSED;
	}
	else
	{
		return NOT_PRESSED;
	}
}

/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
