# test
test libraries
https://www.youtube.com/watch?v=PB8Htul_bYI
this link is necessary for timers


https://www.beningo.com/a-reusable-button-debounce-module/
this link is for buttons and structure of the code

void control_p(){
	//buttonstates_update();
	 void (*ptrcontrol[4])() = {__reset_func, __normal_func, __test_func, __start_func};
	 ptrcontrol[device_state]();
}


void CalculateIntervalTime(uint32_t time,uint32_t start_time){
	if (HAL_GetTick() - start_time == time) interval_state = success;
	else interval_state = failed
}
uint32_t IntervalTimeGet(){
	return interval_state;
}
CalculateIntervalTime(100,HAL_GetTick());//100ms hesapla geçince success döndür
// şu anki tick değerini gönder ki hesaplayabilsin
// yukarıdaki olmazsa fonksiyondan önce start_time = HAL_GetTick();
CalculateIntervalTime(100,start_time);
