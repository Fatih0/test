/*
 * subroutins.h
 *
 *  Created on: Sep 10, 2022
 *      Author: Tecra
 */

#ifndef INC_SUBROUTINS_H_
#define INC_SUBROUTINS_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"

#define motor_on 		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
#define motor_off 		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
#define fan_on			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
#define fan_off			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
#define greenled_on		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
#define greenled_off	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
#define yellowled_on	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
#define yellowled_off	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
typedef enum{
	motor_day14_releasetime_sec = 196,
	motor_day21_releasetime_sec = 318,
	motor_day30_releasetime_sec = 420,
	motor_workingtime_ms = 500,
	motorstate_stop = 0,
	motorstate_working = 1

}Motor_t;

typedef enum{
	fan_releasetime_sec = 900,
	fan_workingtime_sec = 20,
	fanstate_stop = 0,
	fanstate_working = 1
}Fan_t;

typedef enum{
	workingled_releasetime_sec = 4,
	greenled_workingtime_ms = 100,
	yellowled_workingtime_ms = 100,
	workingledstate_stop = 0,
	workingledstate_working = 1
}Leds_t;

typedef struct{
	uint16_t motorreleasecounter;
	uint16_t fanreleasecounter;
	uint16_t workingledreleasecounter;
	uint32_t counter_motor_startsec;
	uint32_t counter_workingled_startsec;
	uint32_t counter_fan_startsec;
	uint8_t counter_motor_workingtime_ms;
	uint8_t counter_fan_workingtime_sec;
	uint8_t counter_workingled_workingtime_ms;
	uint32_t counter_motor_workingstart_ms;
	uint32_t counter_fan_workingstart_sec;
	uint32_t counter_workingled_workingstart_ms;

}counters_s;



void states_update();
void IncSeconds();
uint32_t counterGetsec();
void workingstate_updt();
void control();
void states_init();
#endif /* INC_SUBROUTINS_H_ */
