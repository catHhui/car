/*
*Change Logs:
*Data           Author         Notes
*2019-1-15    xiaochunming       the first version
*/

#ifndef __CAR_PWM_H
#define __CAR_PWM_H

#include <rtthread.h>
#include <rtdevice.h>

#define  CAR_PWM_DEVICE "pwm1"
#define  CAR_PWM_CH_A     1		//PE9
#define  CAR_PWM_CH_B     2		//PE11

int car_pwm_init(void);			//С��pwm�豸��ʼ��
int car_pwm_on(void);			//С��pwm�豸��
int car_pwm_off(void);			//С��pwm�豸��
int car_pwm_set(uint32_t period, uint32_t pulse);
				//���� ns         ռ�ձ� ns

#endif

