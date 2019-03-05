/*
*Change Logs:
*Data           Author         Notes
*2019-1-27    xiaochunming      the first version
*/


#include "car_screen.h"

/*引用 car_esp8266.c文件里的函数getCARDATA()获取小车的控制信息*/
extern  char getCARDATA(void);

static rt_thread_t thread1 = RT_NULL;

#define SAMPLE_UART_NAME       "uart2"  /* 串口设备名称 */
static rt_device_t serial;              /* 串口设备句柄 */

/*定义向串口屏发送的信息*/
char STR[]={0xff,0xff,0xff,0xff};
char str0[]="t0.txt=\"ON  \"";
char str1[]="t0.txt=\"OFF \"";
char str2[]="t3.txt=\"左  \"";
char str3[]="t3.txt=\"前  \"";
char str4[]="t3.txt=\"后  \"";
char str5[]="t3.txt=\"右  \"";
char str6[]="t3.txt=\"NULL\"";
char str7[]="t4.txt=\"低速\"";
char str8[]="t4.txt=\"中速\"";
char str9[]="t4.txt=\"高速\"";
char str10[]="t4.txt=\"停止\"";


/*串口屏显示线程 thread1的入口*/
static void car_screen_entry(void * parameter)
{
	char ch=NULL;		//存放串口屏需要打印的信息，目的是
						//当小车控制信息改变时，串口屏只要打印一遍
	char *str;			//定义字符指针，为了缩减代码
	static int flag=0;			//小车开关标志，0为关，1为开
	
	while(1)
	{
		/******判断当前串口屏显示信息是否为最新***
		 ******不是就打印最新信息			   ***/
		if(ch!=getCARDATA())
		{
			
			ch=getCARDATA();		//更新串口屏需要打印的信息
			
			switch(ch)
			{
				
				case '0':	str=str6;		break;
				case '1':	str=str2;		break;
				case '2':	str=str3;		break;
				case '3':	str=str4;		break;
				case '4':	str=str5;		break;
				case '5':	if(flag==1)		//小车状态为 ON 时，才打印速度信息
								str=str7;	break;
				case '6':	if(flag==1)
								str=str8;	break;
				case '7':	if(flag==1)
								str=str9;	break;
				case '8':	str=str1;
							flag=0;
							/*小车状态为 OFF时，增加串口屏打印信息*/
							rt_device_write(serial, 0,str6,13);
							rt_device_write(serial, 0, STR, (sizeof(STR) - 1));
							rt_device_write(serial, 0,str10,13);
							rt_device_write(serial, 0, STR, (sizeof(STR) - 1));
											break;
				case '9':	str=str0;
							flag=1;
							rt_device_write(serial, 0,str7,13);
							rt_device_write(serial, 0, STR, (sizeof(STR) - 1));
											break;
				default:					break;		
			}
			
			/* 向串口屏发送字符串，打印小车状态信息 */
			rt_device_write(serial, 0,str,13);
			rt_device_write(serial, 0, STR, (sizeof(STR) - 1));
			
			
		}
		rt_thread_mdelay(20);
	}
}
int car_screen_init(void)
{	
	 /* 配置参数 */
	struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
	
	/* 查找串口设备 */
	serial = rt_device_find(SAMPLE_UART_NAME);

	/* 以中断接收及轮询发送模式打开串口设备 */
	rt_device_open(serial,RT_DEVICE_FLAG_INT_RX);
	
	config.baud_rate = BAUD_RATE_9600;
	rt_device_control(serial, RT_DEVICE_CTRL_CONFIG, &config);
	
	
	 /* 创建动态线程 */
    thread1= rt_thread_create(	"car_screen",
								car_screen_entry,
								RT_NULL,
                                512, 20, 20);
    if (thread1 != RT_NULL)
    {
        rt_thread_startup(thread1);
    }
	
	return 0;
}
