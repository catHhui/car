/*
*Change Logs:
*Data           Author         Notes
*2019-1-24      Huanghui       the first version
*/

#include <rtthread.h>
#include "car_key.h"
#include "car_control_esp.h"



/* esp8266ģ���ʼ��*/
int car_control_esp_init(void)
{
	/* AT client ��ʼ��,ʹ��uart3�豸�����������ݳ���Ϊ512*/
	char uart[]="uart3";
	at_client_init(uart,512);
	
	/*������Ӧ�ṹ����*/
    at_response_t resp = RT_NULL;
    int result = 0;

	/*������Ӧ�ṹ��*/
    resp = at_create_resp(256, 0, rt_tick_from_millisecond(5000));
    if (resp == RT_NULL)
    {
        rt_kprintf("No memory for response structure!");        
    }
		
	

    /* close echo */
    at_exec_cmd(resp, "ATE0");
	rt_thread_mdelay(5);

	/* ����ATָ����������� */
    result = at_exec_cmd(resp, "AT+CIPMUX=0");
	rt_thread_mdelay(5);
    if (result != RT_EOK)
    {
        rt_kprintf("AT client send commands failed or return response error!");
        goto __exit;		//����ָ��ʧ�ܣ���ת��ɾ����Ӧ�ṹ��
    }
	else rt_kprintf("���������ӳɹ�!\n");
	
	/* ����ATָ�����tcp���� */
    result = at_exec_cmd(resp, "AT+CIPSTART=\"TCP\",\"192.168.4.1\",8080");
	rt_thread_mdelay(5);
    if (result != RT_EOK)
    {
        rt_kprintf("AT client send commands failed or return response error!");
        goto __exit;		//����ָ��ʧ�ܣ���ת��ɾ����Ӧ�ṹ��
    }
	else rt_kprintf("tcp���ӳɹ�!\n");
	
	/* ����ATָ�����͸��ģʽ */
    result = at_exec_cmd(resp, "AT+CIPMODE=1");
	rt_thread_mdelay(5);
    if (result != RT_EOK)
    {
        rt_kprintf("AT client send commands failed or return response error!");
        goto __exit;		//����ָ��ʧ�ܣ���ת��ɾ����Ӧ�ṹ��
    }
	else rt_kprintf("����͸��ģʽ�ɹ�!\n");
	
	/* ����ATָ���ʼ����  */
	result = at_exec_cmd(resp, "AT+CIPSEND");
	rt_thread_mdelay(5);
    if (result != RT_EOK)
    {
        rt_kprintf("AT client send commands failed or return response error!");
        goto __exit;		//����ָ��ʧ�ܣ���ת��ɾ����Ӧ�ṹ��
    }
	else 
	{
		rt_kprintf("���俪ʼ! \n");
		//led_on();			//���� esp8266Ϊ�������ɹ������� led��
	}

    
__exit:
	
    if(resp)
    {
		/*ɾ����Ӧ�ṹ��*/
        at_delete_resp(resp);
    }
	
	return 0;
}
/////////////////////////////////////////

extern char getCARDATA(void);//ʹ���ⲿ����

static rt_thread_t thread = RT_NULL;

/*�߳� thread�����*/
static void car_senddate_entry(void * parameter)
{
	char date[]="0d";
	
	while(1)
	{
		if(date[0]!=getCARDATA())
		{
			date[0]=getCARDATA();
			at_client_send(date,2);
			rt_kprintf("%s\n",date);
			//rt_thread_mdelay(1000);
		}
	}
	
}

int car_senddata(void)
{	
	 /* ������̬�߳� */
    thread= rt_thread_create(	"car_esp",
								car_senddate_entry,
								RT_NULL,
                                512, 20, 20);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
	
	return 0;
}

int car_esp_init(void)
{
	
	car_control_esp_init();
	//car_key_init();
	car_senddata();
	
	
	return 0;
}

