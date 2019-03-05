/*
*Change Logs:
*Data           Author         Notes
*2019-1-16      Huanghui       the first version
*/

#include <rtdevice.h>
#include <car_run_control.h>

void car_run_control_init(void)
{
	/*���� PF0~PF3 Ϊ���ģʽ*/	
	rt_pin_mode(IN1,PIN_MODE_OUTPUT);
	rt_pin_mode(IN2,PIN_MODE_OUTPUT);
	rt_pin_mode(IN3,PIN_MODE_OUTPUT);
	rt_pin_mode(IN4,PIN_MODE_OUTPUT);
	
	car_run_control_stop();
	
}

void car_run_control_forward(void)
{
	/*����С��ǰ��*/
	rt_pin_write(IN1,PIN_HIGH);
	rt_pin_write(IN2,PIN_LOW);
	rt_pin_write(IN3,PIN_HIGH);
	rt_pin_write(IN4,PIN_LOW);
	
}

void car_run_control_back(void)
{
	/*����С������*/
	rt_pin_write(IN1,PIN_LOW);
	rt_pin_write(IN2,PIN_HIGH);
	rt_pin_write(IN3,PIN_LOW);
	rt_pin_write(IN4,PIN_HIGH);
	
}

void car_run_control_stop(void)
{
	/*����С��ֹͣ*/
	rt_pin_write(IN1,PIN_LOW);
	rt_pin_write(IN2,PIN_LOW);
	rt_pin_write(IN3,PIN_LOW);
	rt_pin_write(IN4,PIN_LOW);
	
}

void car_run_control_left(void)
{
	/*����С����ת*/
	rt_pin_write(IN1,PIN_LOW);
	rt_pin_write(IN2,PIN_HIGH);
	rt_pin_write(IN3,PIN_HIGH);
	rt_pin_write(IN4,PIN_LOW);
	
}

void car_run_control_right(void)
{
	/*����С����ת*/
	rt_pin_write(IN1,PIN_HIGH);
	rt_pin_write(IN2,PIN_LOW);
	rt_pin_write(IN3,PIN_LOW);
	rt_pin_write(IN4,PIN_HIGH);
	
}



