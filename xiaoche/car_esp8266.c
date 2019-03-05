/*
*Change Logs:
*Data           Author         Notes
*2019-1-24      Huanghui       the first version
*/

#include "car_esp8266.h"

/*���С��������Ϣ,Ϊ�ַ� ��1��~��9��������ֵΪ�ַ� ��8��*/
char CARDATA=NULL;			//С��ֹͣ��ʻ

/* esp8266ģ���ʼ��*/
int car_esp8266_init(void)
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
    result = at_exec_cmd(resp, "AT+CIPMUX=1");
	rt_thread_mdelay(5);
    if (result != RT_EOK)
    {
        rt_kprintf("AT client send commands failed or return response error!");
        goto __exit;		//����ָ��ʧ�ܣ���ת��ɾ����Ӧ�ṹ��
    }
	else rt_kprintf("���������ӳɹ�!\n");
	
	/* ����ATָ����� SERVER ģʽ�����ö˿�Ϊ 8080  */
	result = at_exec_cmd(resp, "AT+CIPSERVER=1,8080");
	rt_thread_mdelay(5);
    if (result != RT_EOK)
    {
        rt_kprintf("AT client send commands failed or return response error!");
        goto __exit;		//����ָ��ʧ�ܣ���ת��ɾ����Ӧ�ṹ��
    }
	else 
	{
		rt_kprintf("���� SERVER ģʽ�ɹ�!\n");
		led_on();			//���� esp8266Ϊ�������ɹ������� led��
	}

    
__exit:
	
    if(resp)
    {
		/*ɾ����Ӧ�ṹ��*/
        at_delete_resp(resp);
    }
	
	return 0;
}

/////////////////////////////////////////////////////////////////
// URC ����ִ�к���
static void urc_func(const char *data, rt_size_t size)
{
	//int i;
	rt_kprintf("�յ�����Ϊ��\n");
	rt_kprintf("%s\n",data);
	
	CARDATA=data[9];
	
	rt_kprintf("������ϢΪ��\n%c\n",CARDATA);
	
}

/* URC����ǰ׺Ϊ +IPD ����׺Ϊ d ��ִ�к���Ϊ urc_func*/
static struct at_urc urc_table[] = {
    {"+IPD","d",     urc_func},
};

int at_client_port_init(void)
{
    /* ��� URC ������ URC �б��У������յ�ͬʱƥ�� URC ǰ׺�ͺ�׺�����ݣ�ִ�� URC ����  */
    at_set_urc_table(urc_table, sizeof(urc_table) / sizeof(urc_table[0]));
    return RT_EOK;
}

char getCARDATA(void)
{
	return CARDATA;
}

