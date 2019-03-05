/*
*Change Logs:
*Data           Author         Notes
*2019-1-15   xiaochunming       the first version
*/

#include <car_pwm.h>

struct rt_device_pwm  *pwm_device=RT_NULL;	//����pwm���

int car_pwm_init(void)
{
	/*����pwm�豸*/
	pwm_device=(struct rt_device_pwm *)rt_device_find(CAR_PWM_DEVICE);
	if(pwm_device==RT_NULL)
	{
		return -RT_ERROR;
	}
	
	return 0;
}

int car_pwm_on(void)
{
	rt_pwm_enable(pwm_device,CAR_PWM_CH_A);	//ʹ��С����Ӧ��pwmͨ��
	rt_pwm_enable(pwm_device,CAR_PWM_CH_B);
	
	return 0;
}

int car_pwm_off(void)
{
	rt_pwm_disable(pwm_device,CAR_PWM_CH_A);	//ʧ��С����Ӧ��pwmͨ��
	rt_pwm_disable(pwm_device,CAR_PWM_CH_B);
	
	return 0;
}

int car_pwm_set(uint32_t period,uint32_t pulse)
{
	/*���� PWM API �趨 ���ں�ռ�ձ�*/
	rt_pwm_set(pwm_device,CAR_PWM_CH_A,period,pulse);
	rt_pwm_set(pwm_device,CAR_PWM_CH_B,period,pulse);
	
	return 0;
}
