#include "subroutins.h"
#include "button.h"

Motor_t motorreleasetime;
Motor_t motor_state;
Fan_t fan_state;
Leds_t workingled_state;
Device_t device_state;
counters_s counters_struct;
volatile uint32_t counter1sec = 0;

uint32_t resetled_workingtime_ms = 0;
uint8_t flag = 0;

void __start func(){
	// başlangıçta cihaz açıldığında 30 kez motoru 5 saniye aralıklarla çalıştırır	
	// 4sn de bir çalışma ledi yanar
	
	//30 defa çalışması bittikten sonra
	//counters_struct.counter_motor_startsec = counterGetsec();
	
	// motor_cal();//motorstate_updt();
	// workingled_cal();//workingledstate_updt();
	// motor_work_or_dontwork();//motor_updt();
	// workingled_work_or_dontwork();//workingled_updt();
	
	//counters_struct.counter_motor_30times_startsec = counterGetsec();  init kısmında başlatılır
	if((counterGetsec() - counters_struct.counter_motor_30times_startsec > 5)){
		if (counters_struct.counter_motor_30times != 0){
			motor_state = motorstate_working;
			--counters_struct.counter_motor_30times;
			counters_struct.counter_motor_30times_startsec = counterGetsec();
			counters_struct.counter_motor_workingstart_ms = HAL_GetTick();// bu burda mı yoksa else tarafında mı olmalı
		}else{
			counters_struct.counter_motor_30times_startsec = counterGetsec();
			counters_struct.counter_motor_startsec = counterGetsec();// normal mode için ama init kısmında mı yapılcak kontrol et
			//device_state = devicestate_normal;
		}	
	}
	if (counterGetsec() - counters_struct.counter_workingled_startsec >= workingled_releasetime_sec){
		workingled_state = workingledstate_working;
		counters_struct.counter_workingled_workingstart_ms = HAL_GetTick();
		counters_struct.counter_workingled_startsec = counterGetsec();
	}
	if (motorGetState()){
		motor_on;
		if (HAL_GetTick() - counters_struct.counter_motor_workingstart_ms  == motor_workingtime_ms){
			motor_state = motorstate_stop;
		}
	}
	else motor_off;
	
	if (workingledGetState()){
		greenled_on;
		if (HAL_GetTick() - counters_struct.counter_workingled_workingstart_ms == greenled_workingtime_ms){
			workingled_state = workingledstate_stop;
		}
	}
	else greenled_off;
	
	if (counters_struct.counter_motor_30times == 0) device_state = devicestate_normal;
	
}
void __normal_func(){
	// çalışma ledi 4sn de bir yanar
	// motor basma aralığı sürelerine göre çalışır
	// fan 15dk bir 20sn boyunc çalışır
	// basım aralıkları eeproma kaydedilir
	
	// motor_cal();//motorstate_updt();
	// workingled_cal();//workingledstate_updt();
	// motor_work_or_dontwork();//motor_updt();
	// workingled_work_or_dontwork();//workingled_updt();	
	// fan_cal(); // fanstate_updt();
	// fan_work_or_dontwork();//fan_updt();
	//
	if (counterGetsec() - counters_struct.counter_motor_startsec == motorreleasetime){
		motor_state = motorstate_working;
		counters_struct.counter_motor_workingstart_ms = HAL_GetTick();
		counters_struct.counter_motor_startsec = counterGetsec();
	}
	if (motorGetState()){
		motor_on;
		if (HAL_GetTick() - counters_struct.counter_motor_workingstart_ms  == motor_workingtime_ms){
			motor_state = motorstate_stop;
			//counters_struct.counter_motor_workingstart_ms = HAL_GetTick();
		}
	}
	else motor_off;	
	//counters_struct.counter_fan_startsec = counterGetsec(); // init kısmında
	if (counterGetsec() - counters_struct.counter_fan_startsec == fan_releasetime_sec){
		fan_state = fanstate_working;
		counters_struct.counter_fan_workingstart_sec = counterGetsec();
		counters_struct.counter_fan_startsec = counterGetsec();		
	}
	if (fanGetState()){
		fan_on;
		if (counterGetsec() - counters_struct.counter_fan_workingstart_sec == fan_workingtime_sec){
			fan_state = fanstate_stop;
			//counters_struct.counter_fan_workingstart_sec = counterGetsec();
		}
	}
	else fan_off;
	//counters_struct.counter_workingled_startsec = counterGetsec();//start fonksiyonundan kaldığı yerde devam etmesi gerekir
	if (counterGetsec() - counters_struct.counter_workingled_startsec >= workingled_releasetime_sec){
		workingled_state = workingledstate_working;
		counters_struct.counter_workingled_workingstart_ms = HAL_GetTick();
		counters_struct.counter_workingled_startsec = counterGetsec();
	}	
	if (workingledGetState()){
		greenled_on;
		if (HAL_GetTick() - counters_struct.counter_workingled_workingstart_ms == greenled_workingtime_ms){
			workingled_state = workingledstate_stop;
		}
	}
	else greenled_off;
	
}
void _test_init(){
	device_state = devicestate_test;
	counters_struct.counter_motor_testtime_startsec = counterGetsec();
}
void __test_func(){
	// test butonuna basıldıktan 5sn sonra motor bir kez çalışır
	if ((counterGetsec() - counters_struct.counter_motor_testtime_startsec > motor_testtime_sec)){
		motor_state = motorstate_working;
		counters_struct.counter_motor_testtime_startsec = counterGetsec();
		counters_struct.counter_motor_workingstart_ms = HAL_GetTick();
	}	
	if (motorGetState()){
		motor_on;
		if (HAL_GetTick() - counters_struct.counter_motor_workingstart_ms  == motor_workingtime_ms){
			motor_state = motorstate_stop;
			//counters_struct.counter_motor_workingstart_ms = HAL_GetTick();
		}
	}else {
		motor_off;
		device_state = devicestate_normal;
	}
}
void __reset_init(){
	// devicereset_func();
	motor_state = motorstate_stop;//motor_off;
	fan_state = fanstate_stop;//fan_off;
	workingled_state = workingledstate_stop;
	//workingled_off;
	//yellowled_off;
	counter1sec = 0;//ms içinde yapılır
	counters_struct = (counters_s){0,0,0,counterGetsec(),counterGetsec(),counterGetsec(),HAL_GetTick(),
	counterGetsec(),HAL_GetTick(),HAL_GetTick(),counterGetsec(),HAL_GetTick(),0,counterGetsec(),counterGetsec()};
	//ysysy 500ms aralıklarla yapalım
	flag=1;
	device_state = devicestate_reset;
	//motor fan led state leri ayarla
	//counter ları ayarları sec ms vscanf
	//counters_struct = (counters_s){000000....counterGetsec(), HAL_GetTick()};
	resetled_workingtime_ms = HAL_GetTick();
}
void __reset_func(){
	// counterlar init
	// değerler init
	// ysysy 500ms olarak yanar
	
	switch(flag){
		case 1: greenled_on;
			if ((HAL_GetTick() - resetled_workingtime_ms > 500) && flag==1){
				greenled_off;
				yellowled_on;
				resetled_workingtime_ms = HAL_GetTick();
				flag = 2;
			}break;
		case 2:
			if ((HAL_GetTick() - resetled_workingtime_ms > 500)&& flag==2){
				yellowled_off;
				greenled_on;
				resetled_workingtime_ms = HAL_GetTick();
				flag = 3;
			}break;
		case 3:
			if (HAL_GetTick() - resetled_workingtime_ms > 500){
				greenled_off;
				yellowled_on;
				resetled_workingtime_ms = HAL_GetTick();
				flag = 4;
			}break;
		case 4:
			if (HAL_GetTick() - resetled_workingtime_ms > 500){
				yellowled_off;
				greenled_on;
				resetled_workingtime_ms = HAL_GetTick();
				flag=5;
		}break;
		case 5:
			if (HAL_GetTick() - resetled_workingtime_ms > 500){
				greenled_off;
				resetled_workingtime_ms = HAL_GetTick();
				flag=0;
			}break;
		default : device_state = devicestate_normal;
			break;
	}	
}
void buttonstates_update()
{
//	  Button_State_t button_resetState;
//	  Button_State_t button_swday14State;
//	  Button_State_t button_swday21resetState;
//	  Button_State_t button_swday30resetState;

	  if (Button_StateGet(BUTTON_RESET) == BUTTON_STATE_PRESSED){
		 //device_state = devicestate_reset;// devicereset_func();
		 __reset_init();
	  }
	  if (Button_StateGet(BUTTON_TEST) == BUTTON_STATE_PRESSED){
		  //device_state = devicestate_test;//devicetest_func();
		  __test_init();
	  }
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
void control(){
	buttonstates_update();
	switch(device_state)
	{
		case devicestate_normal:
			__normal_func();
			break;
		case devicestate_reset:
			__reset_func();
			break;
		case devicestate_test:
			__test_func();
			break;
		case devicestate_start:
			__start_func();
			break;
		//case devicestate_lowvoltage:
		//	__lowvoltage_func();
		//	break;
	}
}
