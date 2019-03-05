/*
*Change Logs:
*Data           Author         Notes
*2019-1-24      Huanghui       the first version
*/

#include <rtthread.h>
#include "car_key.h"
#include "car_control_esp.h"



/* esp8266模块初始化*/
int car_control_esp_init(void)
{
	/* AT client 初始化,使用uart3设备，最大接收数据长度为512*/
	char uart[]="uart3";
	at_client_init(uart,512);
	
	/*定义响应结构体句柄*/
    at_response_t resp = RT_NULL;
    int result = 0;

	/*创建响应结构体*/
    resp = at_create_resp(256, 0, rt_tick_from_millisecond(5000));
    if (resp == RT_NULL)
    {
        rt_kprintf("No memory for response structure!");        
    }
		
	

    /* close echo */
    at_exec_cmd(resp, "ATE0");
	rt_thread_mdelay(5);

	/* 发送AT指令，开启单连接 */
    result = at_exec_cmd(resp, "AT+CIPMUX=0");
	rt_thread_mdelay(5);
    if (result != RT_EOK)
    {
        rt_kprintf("AT client send commands failed or return response error!");
        goto __exit;		//发送指令失败，跳转到删除响应结构体
    }
	else rt_kprintf("开启单连接成功!\n");
	
	/* 发送AT指令，建立tcp连接 */
    result = at_exec_cmd(resp, "AT+CIPSTART=\"TCP\",\"192.168.4.1\",8080");
	rt_thread_mdelay(5);
    if (result != RT_EOK)
    {
        rt_kprintf("AT client send commands failed or return response error!");
        goto __exit;		//发送指令失败，跳转到删除响应结构体
    }
	else rt_kprintf("tcp连接成功!\n");
	
	/* 发送AT指令，开启透传模式 */
    result = at_exec_cmd(resp, "AT+CIPMODE=1");
	rt_thread_mdelay(5);
    if (result != RT_EOK)
    {
        rt_kprintf("AT client send commands failed or return response error!");
        goto __exit;		//发送指令失败，跳转到删除响应结构体
    }
	else rt_kprintf("开启透传模式成功!\n");
	
	/* 发送AT指令，开始传输  */
	result = at_exec_cmd(resp, "AT+CIPSEND");
	rt_thread_mdelay(5);
    if (result != RT_EOK)
    {
        rt_kprintf("AT client send commands failed or return response error!");
        goto __exit;		//发送指令失败，跳转到删除响应结构体
    }
	else 
	{
		rt_kprintf("传输开始! \n");
		//led_on();			//设置 esp8266为服务器成功，点亮 led灯
	}

    
__exit:
	
    if(resp)
    {
		/*删除响应结构体*/
        at_delete_resp(resp);
    }
	
	return 0;
}
/////////////////////////////////////////

extern char getCARDATA(void);//使用外部函数

static rt_thread_t thread = RT_NULL;

/*线程 thread的入口*/
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
	 /* 创建动态线程 */
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

