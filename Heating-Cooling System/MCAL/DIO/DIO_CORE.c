/*
 * DIO_CORE.c
 *
 * Created: 8/19/2023 5:44:21 PM
 *  Author: Mina
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
#include "DIO_CORE.h"

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
void DIO_WriteChannel(Uint_8 Pin_Num , PIN_VALUE_t Pin_Value)
{
	Uint_8 Port = 0 ,Pin = 0;
	Port = Pin_Num / NUMBER_OF_EACH_PORT_PINS;
	Pin = Pin_Num % NUMBER_OF_EACH_PORT_PINS;
	switch(Pin_Value)
	{
		case PIN_HIGH:
		switch (Port)
		{
			case 0:
			SET_BIT(PHYSICAL_GPIO_ACCESS(GPIOA_BASE_ADDRESS+GPIO_OUTPUT_REGISTER_PORT),Pin);
			break;
			
			case 1:
			SET_BIT(PHYSICAL_GPIO_ACCESS(GPIOB_BASE_ADDRESS+GPIO_OUTPUT_REGISTER_PORT),Pin);
			break;
			
			case 2:
			SET_BIT(PHYSICAL_GPIO_ACCESS(GPIOC_BASE_ADDRESS+GPIO_OUTPUT_REGISTER_PORT),Pin);
			break;
			
			case 3:
			SET_BIT(PHYSICAL_GPIO_ACCESS(GPIOD_BASE_ADDRESS+GPIO_OUTPUT_REGISTER_PORT),Pin);
			break;
			
			default:
			
			break;
		}
		break;
		case PIN_LOW: 
		switch (Port)
		{
			case 0:
			CLR_BIT(PHYSICAL_GPIO_ACCESS(GPIOA_BASE_ADDRESS+GPIO_OUTPUT_REGISTER_PORT),Pin);
			break;
			
			case 1:
			CLR_BIT(PHYSICAL_GPIO_ACCESS(GPIOB_BASE_ADDRESS+GPIO_OUTPUT_REGISTER_PORT),Pin);
			break;
			
			case 2:
			CLR_BIT(PHYSICAL_GPIO_ACCESS(GPIOC_BASE_ADDRESS+GPIO_OUTPUT_REGISTER_PORT),Pin);
			break;
			
			case 3:
			CLR_BIT(PHYSICAL_GPIO_ACCESS(GPIOD_BASE_ADDRESS+GPIO_OUTPUT_REGISTER_PORT),Pin);
			break;
			
			default:
			
			break;
		}
		break;
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
void DIO_ReadChannel(Uint_8 Pin_Num , PIN_VALUE_t *Pin_Value)
{
	Uint_8 Port = 0 ,Pin = 0;
	Port = Pin_Num / NUMBER_OF_EACH_PORT_PINS;
	Pin = Pin_Num % NUMBER_OF_EACH_PORT_PINS;
	switch (Port)
	{
		case 0:
		*Pin_Value= GET_BIT(PHYSICAL_GPIO_ACCESS(GPIOA_BASE_ADDRESS+GPIO_INPUT_REGISTER_PIN),Pin);
		break;
		
		case 1:
		*Pin_Value=GET_BIT(PHYSICAL_GPIO_ACCESS(GPIOB_BASE_ADDRESS+GPIO_INPUT_REGISTER_PIN),Pin);
		break;
		
		case 2:
		*Pin_Value=GET_BIT(PHYSICAL_GPIO_ACCESS(GPIOC_BASE_ADDRESS+GPIO_INPUT_REGISTER_PIN),Pin);
		break;
		
		case 3:
		*Pin_Value=GET_BIT(PHYSICAL_GPIO_ACCESS(GPIOD_BASE_ADDRESS+GPIO_INPUT_REGISTER_PIN),Pin);
		break;
		
		default:
		
		break;
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
void DIO_FlipChannel(Uint_8 Pin_Num)
{
	Uint_8 Port = 0 ,Pin = 0;
	Port = Pin_Num / NUMBER_OF_EACH_PORT_PINS;
	Pin = Pin_Num % NUMBER_OF_EACH_PORT_PINS;
	switch (Port)
	{
		case 0:
		Toggle_BIT(PHYSICAL_GPIO_ACCESS(GPIOA_BASE_ADDRESS+GPIO_OUTPUT_REGISTER_PORT),Pin);
		break;
		
		case 1:
		Toggle_BIT(PHYSICAL_GPIO_ACCESS(GPIOB_BASE_ADDRESS+GPIO_OUTPUT_REGISTER_PORT),Pin);
		break;
		
		case 2:
		Toggle_BIT(PHYSICAL_GPIO_ACCESS(GPIOC_BASE_ADDRESS+GPIO_OUTPUT_REGISTER_PORT),Pin);
		break;
		
		case 3:
		Toggle_BIT(PHYSICAL_GPIO_ACCESS(GPIOD_BASE_ADDRESS+GPIO_OUTPUT_REGISTER_PORT),Pin);
		break;
		
		default:
		
		break;
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
void DIO_WritePort(Uint_8 Pin_Num , Uint_8 PORT_Value)
{
	Uint_8 Port = 0 ;
	Port = Pin_Num / NUMBER_OF_EACH_PORT_PINS;
	
	
	switch (Port)
	{
		case 0:
		PHYSICAL_GPIO_ACCESS(GPIOA_BASE_ADDRESS+GPIO_OUTPUT_REGISTER_PORT)= PORT_Value;
		break;
		
		case 1:
		PHYSICAL_GPIO_ACCESS(GPIOB_BASE_ADDRESS+GPIO_OUTPUT_REGISTER_PORT)= PORT_Value;
		break;
		
		case 2:
		PHYSICAL_GPIO_ACCESS(GPIOC_BASE_ADDRESS+GPIO_OUTPUT_REGISTER_PORT)= PORT_Value;
		break;
		
		case 3:
		PHYSICAL_GPIO_ACCESS(GPIOD_BASE_ADDRESS+GPIO_OUTPUT_REGISTER_PORT)= PORT_Value;
		break;
		
		default:
		
		break;
	}
}

void DIO_WriteDDR(Uint_8 Pin_Num , Uint_8 PORT_Value)
{
	Uint_8 Port = 0 ;
	Port = Pin_Num / NUMBER_OF_EACH_PORT_PINS;
	
	
	switch (Port)
	{
		case 0:
		PHYSICAL_GPIO_ACCESS(GPIOA_BASE_ADDRESS+GPIO_DIRECTION_REGISTER_DDR)= PORT_Value;
		break;
		
		case 1:
		PHYSICAL_GPIO_ACCESS(GPIOB_BASE_ADDRESS+GPIO_DIRECTION_REGISTER_DDR)= PORT_Value;
		break;
		
		case 2:
		PHYSICAL_GPIO_ACCESS(GPIOC_BASE_ADDRESS+GPIO_DIRECTION_REGISTER_DDR)= PORT_Value;
		break;
		
		case 3:
		PHYSICAL_GPIO_ACCESS(GPIOD_BASE_ADDRESS+GPIO_DIRECTION_REGISTER_DDR)= PORT_Value;
		break;
		
		default:
		
		break;
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
void DIO_ReadPort(Uint_8 Pin_Num , Uint_8 *PORT_Value)
{
	Uint_8 Port = 0 ;
	Port = Pin_Num / NUMBER_OF_EACH_PORT_PINS;
	
	
	switch (Port)
	{
		case 0:
		*PORT_Value= PHYSICAL_GPIO_ACCESS(GPIOA_BASE_ADDRESS+GPIO_INPUT_REGISTER_PIN);
		break;
		
		case 1:
		*PORT_Value= PHYSICAL_GPIO_ACCESS(GPIOB_BASE_ADDRESS+GPIO_INPUT_REGISTER_PIN);
		break;
		
		case 2:
		*PORT_Value= PHYSICAL_GPIO_ACCESS(GPIOC_BASE_ADDRESS+GPIO_INPUT_REGISTER_PIN);
		break;
		
		case 3:
		*PORT_Value= PHYSICAL_GPIO_ACCESS(GPIOD_BASE_ADDRESS+GPIO_INPUT_REGISTER_PIN);
		break;
		
		default:
		
		break;
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
void DIO_ReadOutputPort(Uint_8 Pin_Num , Uint_8 *PORT_Value)
{
	Uint_8 Port = 0 ;
	Port = Pin_Num / NUMBER_OF_EACH_PORT_PINS;
	
	
	switch (Port)
	{
		case 0:
		*PORT_Value= PHYSICAL_GPIO_ACCESS(GPIOA_BASE_ADDRESS+GPIO_OUTPUT_REGISTER_PORT);
		break;
		
		case 1:
		*PORT_Value= PHYSICAL_GPIO_ACCESS(GPIOB_BASE_ADDRESS+GPIO_OUTPUT_REGISTER_PORT);
		break;
		
		case 2:
		*PORT_Value= PHYSICAL_GPIO_ACCESS(GPIOC_BASE_ADDRESS+GPIO_OUTPUT_REGISTER_PORT);
		break;
		
		case 3:
		*PORT_Value= PHYSICAL_GPIO_ACCESS(GPIOD_BASE_ADDRESS+GPIO_OUTPUT_REGISTER_PORT);
		break;
		
		default:
		
		break;
	}
}

/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
