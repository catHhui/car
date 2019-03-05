/*
*Change Logs:
*Data           Author         Notes
*2019-1-16      Huanghui       the first version
*/
/*
********说明：
********IN1、IN2控制左边电机转动；IN3、IN4控制右边电机转动
********IN1=1、IN2=0时，左轮向前；IN3=1、IN4=0时，右轮向前
********IN1=0、IN2=1时，左轮向后；IN3=0、IN4=1时，右轮向后
*/

#ifndef __CAR_RUN_CONTROL_H
#define __CAR_RUN_CONTROL_H

#include <rtthread.h>

#define   IN1		50		//PF12
#define   IN2 		53		//PF13
#define   IN3		54		//PF14
#define   IN4		55		//PF15

void car_run_control_init(void);		//小车行走初始化
void car_run_control_forward(void);		//小车前进
void car_run_control_back(void);		//小车后退
void car_run_control_stop(void);		//小车停止
void car_run_control_left(void);		//小车左转
void car_run_control_right(void);		//小车右转

#endif

