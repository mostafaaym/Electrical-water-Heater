/*
 * PORT_Core.c
 *
 * Created: 9/4/2023 11:43:06 PM
 *  Author: abdel
 */ 


/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  PORT_CORE.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "PORT_CORE.h"


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
* \Syntax          : void PORT_Init(void)        
* \Description     : PORT Initialization                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/
void PORT_Init(void)
{
	Uint_8 port=0,pin=0,dir=0,cnt=0;
	for (cnt=0;cnt< DEFINED_PINS ;cnt++)
	{
		port=PORT_Initialization[cnt].PIN_NUM / NUMBER_OF_EACH_PORT_PINS;
		pin=PORT_Initialization[cnt].PIN_NUM % NUMBER_OF_EACH_PORT_PINS;
		dir = PORT_Initialization[cnt].PIN_DIR;
		
		switch(dir)
		{
			case PIN_OUTPUT :
			switch (port)
			{
				case 0:
				SET_BIT(PHYSICAL_GPIO_ACCESS(GPIOA_BASE_ADDRESS+GPIO_DIRECTION_REGISTER_DDR),pin);
				break;
				
				case 1:
				SET_BIT(PHYSICAL_GPIO_ACCESS(GPIOB_BASE_ADDRESS+GPIO_DIRECTION_REGISTER_DDR),pin);
				break;
				
				case 2:
				SET_BIT(PHYSICAL_GPIO_ACCESS(GPIOC_BASE_ADDRESS+GPIO_DIRECTION_REGISTER_DDR),pin);
				break;
				
				case 3:
				SET_BIT(PHYSICAL_GPIO_ACCESS(GPIOD_BASE_ADDRESS+GPIO_DIRECTION_REGISTER_DDR),pin);
				break;
				
				default:
				
				break;
			}
			break;
			
			case  PIN_INPUT :
			switch (port)
			{
				case 0:
				CLR_BIT(PHYSICAL_GPIO_ACCESS(GPIOA_BASE_ADDRESS+GPIO_DIRECTION_REGISTER_DDR),pin);
				break;
				
				case 1:
				CLR_BIT(PHYSICAL_GPIO_ACCESS(GPIOB_BASE_ADDRESS+GPIO_DIRECTION_REGISTER_DDR),pin);
				break;																	   
																						   
				case 2:																	   
				CLR_BIT(PHYSICAL_GPIO_ACCESS(GPIOC_BASE_ADDRESS+GPIO_DIRECTION_REGISTER_DDR),pin);
				break;																	   
																						   
				case 3:																	   
				CLR_BIT(PHYSICAL_GPIO_ACCESS(GPIOD_BASE_ADDRESS+GPIO_DIRECTION_REGISTER_DDR),pin);
				break;
				
				default:
				
				break;
			}
			break;
			
			default:
			
			break;
		}
	}
	
}

/**********************************************************************************************************************
 *  END OF FILE: PORT_CORE.c
 *********************************************************************************************************************/
