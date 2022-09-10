/*
 * subroutins.c
 *
 *  Created on: Sep 10, 2022
 *      Author: Tecra
 */

#include "subroutins.h"
#include "button.h"

Motor_t motorreleasetime;
Motor_t motor_state;
Fan_t fan_state;
Leds_t workingled_state;
counters_s counters_struct;
volatile uint32_t counter1sec = 0;
void states_update()
{
//	  Button_State_t button_resetState;
//	  Button_State_t button_swday14State;
//	  Button_State_t button_swday21resetState;
//	  Button_State_t button_swday30resetState;



	  if (Button_StateGet(BUTTON_DAY_14) == BUTTON_STATE_PRESSED){
		motorreleasetime = motor_day14_releasetime_sec;
	  }
	  if (Button_StateGet(BUTTON_DAY_21) == BUTTON_STATE_PRESSED){
		motorreleasetime = motor_day21_releasetime_sec;
	  }
	  if (Button_StateGet(BUTTON_DAY_30) == BUTTON_STATE_PRESSED){
		motorreleasetime = motor_day30_releasetime_sec;
	  }

}
void IncSeconds(){
	++counter1sec;
}
uint32_t counterGetsec(){
	return counter1sec;
}

void workingstate_updt()
{
	if (counterGetsec() - counters_struct.counter_motor_startsec > motorreleasetime){
		motor_state = motorstate_working;
		counters_struct.counter_motor_workingstart_ms = HAL_GetTick();
		counters_struct.counter_motor_startsec = counterGetsec();
	}
	if (counterGetsec() - counters_struct.counter_fan_startsec >= fan_releasetime_sec){
		fan_state = fanstate_working;
		counters_struct.counter_fan_workingstart_sec = counterGetsec();
		counters_struct.counter_fan_startsec = counterGetsec();
	}
	if (counterGetsec() - counters_struct.counter_workingled_startsec >= workingled_releasetime_sec){
		workingled_state = workingledstate_working;
		counters_struct.counter_workingled_workingstart_ms = HAL_GetTick();
		counters_struct.counter_workingled_startsec = counterGetsec();
	}
}
Motor_t motorGetState(){

	return motor_state;
}
Fan_t fanGetState(){

	return fan_state;
}
Leds_t workingledGetState(){

	return workingled_state;
}
void control(){
	if (motorGetState()){
		motor_on;
		if (HAL_GetTick() - counters_struct.counter_motor_workingstart_ms  == motor_workingtime_ms){
			motor_state = motorstate_stop;
		}
	}
	else motor_off;

	if (fanGetState()){
		fan_on;
		if (counterGetsec() - counters_struct.counter_fan_workingstart_sec == fan_workingtime_sec){
			fan_state = fanstate_stop;
		}
	}
	else fan_off;

	if (workingledGetState()){
		greenled_on;
		if (HAL_GetTick() - counters_struct.counter_workingled_workingstart_ms == greenled_workingtime_ms){
			workingled_state = workingledstate_stop;
		}
	}
	else greenled_off;
}
void states_init()
{
	motor_state = motorstate_stop;
	fan_state = fanstate_stop;
	workingled_state = workingledstate_working;
}
