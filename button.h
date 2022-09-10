/*
 * button.h
 *
 *  Created on: Sep 9, 2022
 *      Author: Tecra
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

/******************************************************************************
* Typedefs
*******************************************************************************/
/**
 * Button_State_t defines the possible states that a button may be in.
 * Additional button states can be added to this enumeration.  Button_State_t
 * also defines a maximum value that can be used for boundary checking.
 */
typedef enum
{
	BUTTON_STATE_NOT_PRESSED,		/**< The pressed electrical state */
   BUTTON_STATE_PRESSED,	/**< The not pressed electrical state */
   BUTTON_STATE_MAX				/**< Maximum number of button states */
}Button_State_t;

/**
 * Button_t defines the buttons that exist within the embedded system.
 * Additional buttons can be added by adding to this enumeration.
 * It also defines a maximum value that can be used for boundary checking.
 */
typedef enum
{
   BUTTON_RESET,			/**< The reset button */
   BUTTON_DAY_14,				/**< The day 14 button */
   BUTTON_DAY_21,			/**< The day 21 button */
   BUTTON_DAY_30,			/**< The day 30 button */
   BUTTON_MAX_NUMBER			/**< Number of buttons in the system */
}Button_t;

void Button_Init(void);
void Button_Debounce(void);
Button_State_t Button_StateGet(Button_t Button);

#endif /* INC_BUTTON_H_ */
