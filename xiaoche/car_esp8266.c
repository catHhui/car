/*
*Change Logs:
*Data           Author         Notes
*2019-1-24      Huanghui       the first version
*/

#include "car_esp8266.h"

/*存放小车控制信息,为字符 ‘1’~‘9’，赋初值为字符 ‘8’*/
char CARDATA=NULL;			//小车停止行驶

/* esp8266模块初始化*/
int car_esp8266_init(void)
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

	/* 发送AT指令，开启多连接 */
    result = at_exec_cmd(resp, "AT+CIPMUX=1");
	rt_thread_mdelay(5);
    if (result != RT_EOK)
    {
        rt_kprintf("AT client send commands failed or return response error!");
        goto __exit;		//发送指令失败，跳转到删除响应结构体
    }
	else rt_kprintf("开启多连接成功!\n");
	
	/* 发送AT指令，开启 SERVER 模式，设置端口为 8080  */
	result = at_exec_cmd(resp, "AT+CIPSERVER=1,8080");
	rt_thread_mdelay(5);
    if (result != RT_EOK)
    {
        rt_kprintf("AT client send commands failed or return response error!");
        goto __exit;		//发送指令失败，跳转到删除响应结构体
    }
	else 
	{
		rt_kprintf("开启 SERVER 模式成功!\n");
		led_on();			//设置 esp8266为服务器成功，点亮 led灯
	}

    
__exit:
	
    if(resp)
    {
		/*删除响应结构体*/
        at_delete_resp(resp);
    }
	
	return 0;
}

/////////////////////////////////////////////////////////////////
// URC 数据执行函数
static void urc_func(const char *data, rt_size_t size)
{
	//int i;
	rt_kprintf("收到数据为：\n");
	rt_kprintf("%s\n",data);
	
	CARDATA=data[9];
	
	rt_kprintf("控制信息为：\n%c\n",CARDATA);
	
}

/* URC数据前缀为 +IPD ，后缀为 d ，执行函数为 urc_func*/
static struct at_urc urc_table[] = {
    {"+IPD","d",     urc_func},
};

int at_client_port_init(void)
{
    /* 添加 URC 数据至 URC 列表中，当接收到同时匹配 URC 前缀和后缀的数据，执行 URC 函数  */
    at_set_urc_table(urc_table, sizeof(urc_table) / sizeof(urc_table[0]));
    return RT_EOK;
}

char getCARDATA(void)
{
	return CARDATA;
}

