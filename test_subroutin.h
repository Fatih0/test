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
	motor_day14_releasetime_sec = 10,// orijinalde 196
	motor_day21_releasetime_sec = 20,//orijinalde 318
	motor_day30_releasetime_sec = 30,//orijinalde 420
	motor_workingtime_ms = 500,
	motorstate_stop = 0,
	motorstate_working = 1,
	motor_working_30times_sec = 5,
	motor_testtime_sec = 5

}Motor_t;

typedef enum{
	fan_releasetime_sec = 20,// orijinalde 900
	fan_workingtime_sec = 4, // orijinalde 20
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

typedef enum{
	devicestate_reset,
	devicestate_normal,
	devicestate_test,
	devicestate_start
}Device_t;
typedef struct{
	uint16_t motorreleasecounter;//0
	uint16_t fanreleasecounter;//0
	uint16_t workingledreleasecounter;//0
	uint32_t counter_motor_startsec; //counterGetsec();
	uint32_t counter_workingled_startsec;//counterGetsec();
	uint32_t counter_fan_startsec;//counterGetsec();
	uint8_t counter_motor_workingtime_ms; //HAL_GetTick();
	uint8_t counter_fan_workingtime_sec;//counterGetsec();
	uint8_t counter_workingled_workingtime_ms;//HAL_GetTick();
	uint32_t counter_motor_workingstart_ms;//HAL_GetTick();
	uint32_t counter_fan_workingstart_sec;//counterGetsec();
	uint32_t counter_workingled_workingstart_ms;//HAL_GetTick();
	uint8_t counter_motor_30times;//0, eğer resete basıldığında motor 30 defa çalışacak ise 30 ve device_state ona göre ayarlanır
	uint32_t counter_motor_30times_startsec;//counterGetsec();
	uint32_t counter_motor_testtime_startsec;//counterGetsec();
//counters_struct = (counters_s){0,0,0,counterGetsec(),counterGetsec(),counterGetsec(),HAL_GetTick(),counterGetsec(),HAL_GetTick(),HAL_GetTick(),};
}counters_s;



void buttonstates_update();
void IncSeconds();
uint32_t counterGetsec();
void workingstate_updt();
void control();
void states_init();
void devicereset_func();
void devicetest_func();
void normal_func();
void reset_func();
void test_func();
void start_func();

void __test_init();
void __reset_init();
void __start_func();
void __test_func();
void __normal_func();
void __reset_func();

#endif /* INC_SUBROUTINS_H_ */
