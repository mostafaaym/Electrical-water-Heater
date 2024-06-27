/*
 * Seven_Seg.c
 *
 * Created: 8/18/2023 4:11:17 PM
 *  Author: Abdelrahman
 */ 
/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Seven_Seg.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Seven_Seg.h"
#define F_CPU 16000000U

#include <util/delay.h>
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
Uint_8 seven_seg[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
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
******************************************************************************/
void SSD_send(Uint_16 Num)
{
	DIO_WritePort(A,seven_seg[Num]) ;
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
******************************************************************************/
void SSD_enable(Uint_8 disp)
{	
	if (disp == COMMON1)
	{
		DIO_WriteChannel(COMMON1,seven_high);
		DIO_WriteChannel(COMMON2,seven_low );
	}
	else if (disp == COMMON2)
	{
		DIO_WriteChannel(COMMON1,seven_low );
		DIO_WriteChannel(COMMON2,seven_high );
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
******************************************************************************/
void SSD_disable(void)
{	
	DIO_WriteChannel(COMMON1,seven_low );
	DIO_WriteChannel(COMMON2,seven_low );
	
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
******************************************************************************/
void SSD_turn_off(void)
{
	DIO_WritePort(A,0X00);
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
******************************************************************************/
void SSD_write(Uint_16 N)
{	
	Uint_8 units;
	Uint_8 tens;
	
	units = N % 10;
	tens = (Sint_32) N / 10;
	
	SSD_enable(COMMON1);
	SSD_send(units);
	_delay_ms(2);
	
	SSD_enable(COMMON2);
	SSD_send(tens);
	_delay_ms(2);
	
}

/**********************************************************************************************************************
 *  END OF FILE: Seven_Seg.c
 *********************************************************************************************************************/
