/*
*Change Logs:
*Data           Author         		Notes
*2019-1-24     ���͡�Ф����      the first version
*/

#include "car_run.h"

/*���� car_esp8266.c�ļ���ĺ���getCARDATA()��ȡС���Ŀ�����Ϣ*/
extern  char getCARDATA(void);

static rt_thread_t thread = RT_NULL;

/*С�������߳� thread�����*/
static void car_run_entry(void * parameter)
{	int flag=0;
	
	while(1)
	{		
		
		//rt_kprintf("%c\n",getCARDATA());
		
		switch(getCARDATA())
		{
				/*������ϢΪ�ַ� ��0��ʱ������С��ֹͣ*/
			case '0':	car_run_control_stop();		break;
				/*������ϢΪ�ַ� ��1��ʱ������С����ת*/
			case '1':	car_run_control_left();		break;
				/*������ϢΪ�ַ� ��2��ʱ������С��ǰ��*/
			case '2':	car_run_control_forward();	break;
				/*������ϢΪ�ַ� ��3��ʱ������С������*/
			case '3':	car_run_control_back();		break;
				/*������ϢΪ�ַ� ��4��ʱ������С����ת*/
			case '4':	car_run_control_right();	break;
				/*������ϢΪ�ַ� ��5��ʱ������С��������ʻ*/
			case '5':	if(flag!=0)			//С��״̬Ϊ ON ʱ�����ܸı��ٶ�
							car_speed_low();		break;
				/*������ϢΪ�ַ� ��6��ʱ������С��������ʻ*/
			case '6':	if(flag!=0)
							car_speed_medium();		break;
				/*������ϢΪ�ַ� ��7��ʱ������С��ȫ����ʻ*/
			case '7':	if(flag!=0)
							car_speed_high();		break;
				/*������ϢΪ�ַ� ��8��ʱ������С��ֹͣ��ʻ*/
			case '8':	car_speed_stop();
						car_run_control_stop();
						flag=0;						break;
				/*������ϢΪ�ַ� ��9��ʱ������С������*/
			case '9':	car_speed_on();
						flag=1;				break;
			default:								break;
		}
		
		rt_thread_mdelay(50);
		
	}
}

int car_run(void)
{	
	 /* ������̬�߳� */
    thread= rt_thread_create(	"car",
								car_run_entry,
								RT_NULL,
                                512, 20, 20);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
	
	return 0;
}

/*С�����г�ʼ��*/
void car_run_init(void)
{
	led_init();
	car_esp8266_init();			// esp8266ģ���ʼ��
	at_client_port_init();		// URC���ݴ����ʼ��
	car_run_control_init();		//С�����߿��Ƴ�ʼ��
	car_speed_init();			//С���ٶȳ�ʼ��
	car_screen_init();			//С����ʾ��ʼ��
	car_run();					//С������
	
}

