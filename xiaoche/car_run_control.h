/*
*Change Logs:
*Data           Author         Notes
*2019-1-16      Huanghui       the first version
*/
/*
********˵����
********IN1��IN2������ߵ��ת����IN3��IN4�����ұߵ��ת��
********IN1=1��IN2=0ʱ��������ǰ��IN3=1��IN4=0ʱ��������ǰ
********IN1=0��IN2=1ʱ���������IN3=0��IN4=1ʱ���������
*/

#ifndef __CAR_RUN_CONTROL_H
#define __CAR_RUN_CONTROL_H

#include <rtthread.h>

#define   IN1		50		//PF12
#define   IN2 		53		//PF13
#define   IN3		54		//PF14
#define   IN4		55		//PF15

void car_run_control_init(void);		//С�����߳�ʼ��
void car_run_control_forward(void);		//С��ǰ��
void car_run_control_back(void);		//С������
void car_run_control_stop(void);		//С��ֹͣ
void car_run_control_left(void);		//С����ת
void car_run_control_right(void);		//С����ת

#endif

