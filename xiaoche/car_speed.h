/*
*Change Logs:
*Data           Author         Notes
*2019-1-19    xiaochunming       the first version
*/

#ifndef __CAR_SPEED_H
#define __CAR_SPEED_H

#include "car_pwm.h"

#define PERIOD	100000			//PWM����
#define PULSE	100000			//PWMռ�ձ�

void car_speed_init(void);		//С���ٶȳ�ʼ��
void car_speed_high(void);		//С��������ʻ
void car_speed_medium(void);	//С��������ʻ
void car_speed_low(void);		//С��������ʻ
void car_speed_stop(void);		//С��ֹͣ��ʻ
void car_speed_on(void);		//С��������ʻ

#endif

