/*
*Change Logs:
*Data           Author         Notes
*2019-1-19    xiaochunming       the first version
*/

#include <rtdevice.h>
#include "car_speed.h"

void car_speed_init(void)
{
	/*С���ٶȳ�ʼ��*/
	car_pwm_init();
	//car_speed_on();
	
}

void car_speed_high(void)
{
	/*С��ȫ����ʻ*/
	car_pwm_set(PERIOD,PULSE);
	car_pwm_on();
	
}

void car_speed_medium(void)
{
	/*С��������ʻ*/
	car_pwm_set(PERIOD,PULSE-20000);
	car_pwm_on();
	
}

void car_speed_low(void)
{
	/*С��������ʻ*/
	car_pwm_set(PERIOD,PULSE-30000);
	car_pwm_on();
	
}

void car_speed_stop(void)
{
	/*С��ֹͣ��ʻ*/
	car_pwm_off();
}

void car_speed_on(void)
{
	/*С��������ʻ*/
	car_pwm_set(PERIOD,PULSE-30000);	//����
	car_pwm_on();
	
}

