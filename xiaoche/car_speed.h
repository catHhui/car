/*
*Change Logs:
*Data           Author         Notes
*2019-1-19    xiaochunming       the first version
*/

#ifndef __CAR_SPEED_H
#define __CAR_SPEED_H

#include "car_pwm.h"

#define PERIOD	100000			//PWM周期
#define PULSE	100000			//PWM占空比

void car_speed_init(void);		//小车速度初始化
void car_speed_high(void);		//小车高速行驶
void car_speed_medium(void);	//小车中速行驶
void car_speed_low(void);		//小车低速行驶
void car_speed_stop(void);		//小车停止行驶
void car_speed_on(void);		//小车允许行驶

#endif

