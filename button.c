/*
 * button.c
 *
 *  Created on: Sep 9, 2022
 *      Author: Tecra
 */


#include <stdint.h>				/* For portable types */
#include "button.h"				/* For button definitions */
#include "stm32f4xx_hal.h"
//#include "gpio_config.h"		/* For gpio bits and definitions */
//#include "gpio.h"				/* For Gpio_ChannelRead */

/**
 * Defines a list of masks that identify the gpio channel that the buttons
 * are attached to.  These are used by Gpio_ChannelRead to get the pin state.
 */
const uint8_t ButtonList[] =
{
	GPIO_PIN_0,
	GPIO_PIN_4,
	GPIO_PIN_5,
	GPIO_PIN_6
};

/**
 * ButtonCurrentState holds the current state of the physical pin
 * They are initialized to NOT_PRESSED which is an electrical state
 * of 1.
 */
Button_State_t ButtonCurrentState[BUTTON_MAX_NUMBER] =
{
    BUTTON_STATE_NOT_PRESSED,
    BUTTON_STATE_NOT_PRESSED,
	BUTTON_STATE_NOT_PRESSED,
	BUTTON_STATE_NOT_PRESSED
};

/**
 * Defines a list that contains the number of debounce counts necessary
 * to successfully debounce the button(s).  An array was chosen so that
 * different buttons with different debounce parameters could be used
 * in the same application.  It is assumed that each count represents
 * 10 milliseconds.  In this case each switch has a 30 millisecond
 * debounce time.  Different switches can be attached and debounced at
 * different rates.
 */
const uint8_t ButtonDebounceCountList[BUTTON_MAX_NUMBER] =
{
   4,
   4,
   4,
   4
};

/**
 * Stores the current debounce count of the buttons.  This variable is
 * initialized in Button_Init.
 */
uint8_t ButtonDebounceCount[BUTTON_MAX_NUMBER];

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
/******************************************************************************
* Function : Button_Init()
*//**
* \b Description:
*
*  This function is used to initialize the button variables.  It assumes that
*  the gpio pins have already been configured as inputs with the appropriate
*  settings.
*
* @param  		void
*
* @return 		void
*
* @see Button_Init
* @see Button_Debounce
* @see Button_StateGet
*
* \b Example Example:
* @code
*    Gpio_Init();
*    Button_Init();
* @endcode
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Version   Author         Description
*  04/01/15   1.0.0   Jacob Beningo   Initial Release.
*
*******************************************************************************/
void Button_Init(void)
{
	uint8_t i = 0;

	/* Initialize ButtonDebounceCount to an initial value of zero for all
	 * buttons that are attached to the system.
	 */
	for(i = 0; i < BUTTON_MAX_NUMBER; i++)
	{
		ButtonDebounceCount[i] = 0;
	}
}

/******************************************************************************
* Function : Button_Debounce()
*//**
* \b Description:
*
* This function is used to debonce buttons that are attached to the system.
* It loops through ButtonList which contains all available buttons.  Each
* button pin state is then read.  If a change has occurred, it is noted by an
* increment to ButtonDebounceCount.  When ButtonDebounceCount has reached the
* ButtonDebounceCountList value for that button, the button will have been
* debounced and the button state will be updated in ButtonCurrentState.
*
* @param  		void
*
* @return 		void
*
* @see Button_Init
* @see Button_Debounce
* @see Button_StateGet
*
* \b Example Example:
* @code
*    // In System_Init
*    Gpio_Init();
*    Button_Init();
*
*	 // In Task_10ms
*    Button_Debounce();
* @endcode
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Version   Author         Description
*  04/01/15   1.0.0   Jacob Beningo   Initial Release.
*
*******************************************************************************/
void Button_Debounce(void)
{
	uint8_t Index = 0;

	/* Loop through all of the buttons, read their state and determine if
	 * any of their states have changed.
	 */
	for(Index = 0; Index < BUTTON_MAX_NUMBER; Index++)
	{
		/* Check to see if the pin reading is different than the current
		 * debounced button state.  If it is different then the debounce
		 * counter for this pin will be incremented.  If it is the same
		 * the counter will be cleared.
		 */
		if(HAL_GPIO_ReadPin(GPIOA,(ButtonList[Index])) != ButtonCurrentState[Index])
		{
			ButtonDebounceCount[Index]++;

			/* Check to see if the debounce count has met or exceeded the
			 * required count.  If it has, then the state of the button is
			 * updated.  Otherwise it is left as is.
			 */
			if(ButtonDebounceCount[Index] >= ButtonDebounceCountList[Index])
			{
				if(ButtonCurrentState[Index] == BUTTON_STATE_NOT_PRESSED)
				{
					ButtonCurrentState[Index] = BUTTON_STATE_PRESSED;
				}
				else
				{
					ButtonCurrentState[Index] = BUTTON_STATE_NOT_PRESSED;
				}
			}
		}
		else
		{
			ButtonDebounceCount[Index] = 0;
		}
	} // End for loop
}

/******************************************************************************
* Function : Button_StateGet()
*//**
* \b Description:
*
* This function is used to return the current state of a button to the application.
* The application can then use this information to run a state machine or
* perform other related tasks.
*
* @param  		Button Button_t, a system button defined in the Button_t enum
*
* @return 		Button_State_t the debounced state of the button
*
* @see Button_Init
* @see Button_Debounce
* @see Button_StateGet
*
* \b Example Example:
* @code
*    // In System_Init
*    Gpio_Init();
*    Button_Init();
*
*	 // In Task_10ms
*    Button_Debounce();
*
*    Button_MenuState = Button_StateGet(BUTTON_MENU);
*
*    if(Button_MenuState == BUTTON_PRESSED)
*    {
*	    Led_Toggle(LED_RED);
*	 }
* @endcode
*
*  ----------------------
*  - HISTORY OF CHANGES -
*  ----------------------
*    Date    Version   Author         Description
*  04/01/15   1.0.0   Jacob Beningo   Initial Release.
*
*******************************************************************************/
Button_State_t Button_StateGet(Button_t Button)
{
	Button_State_t State;

	/* Verify that the requested button exists and
	 * return its state.  If it doesn't exist, then
	 * return the MAX as an error code.
	 */
	if(Button < BUTTON_MAX_NUMBER)
	{
		State = ButtonCurrentState[Button];
	}
	else
	{
		State = BUTTON_STATE_MAX;
	}

	return State;
}
