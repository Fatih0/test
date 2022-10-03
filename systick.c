tick_start(){
	start = HAL_GetTick();
}

time_elapsed(TICK_t tick_t){
	if (tick.tick_start[tick_t] > HAL_GetTick){
		tick.tick_start[tick_t] = MAXTICK_ms - tick.tick_start[tick_t];
	}
	if (HAL_GetTick() - tick.tick_start > tick.tick_period[tick_t]){
		return true;
		//tick.tick_start[tick_t] = HAL_GetTick();
	}
	else return false;
}
void motor(){
  
if (Get_MotorState()){
    motor_on;
    if (time_elapsed(MOTOR){
	     motor_state = motorstate_stop;
     }
  }motor_off;      
}
