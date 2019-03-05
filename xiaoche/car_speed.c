/*
*Change Logs:
*Data           Author         Notes
*2019-1-19    xiaochunming       the first version
*/

#include <rtdevice.h>
#include "car_speed.h"

void car_speed_init(void)
{
	/*小车速度初始化*/
	car_pwm_init();
	//car_speed_on();
	
}

void car_speed_high(void)
{
	/*小车全速行驶*/
	car_pwm_set(PERIOD,PULSE);
	car_pwm_on();
	
}

void car_speed_medium(void)
{
	/*小车中速行驶*/
	car_pwm_set(PERIOD,PULSE-20000);
	car_pwm_on();
	
}

void car_speed_low(void)
{
	/*小车低速行驶*/
	car_pwm_set(PERIOD,PULSE-30000);
	car_pwm_on();
	
}

void car_speed_stop(void)
{
	/*小车停止行驶*/
	car_pwm_off();
}

void car_speed_on(void)
{
	/*小车允许行驶*/
	car_pwm_set(PERIOD,PULSE-30000);	//低速
	car_pwm_on();
	
}

