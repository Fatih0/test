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
