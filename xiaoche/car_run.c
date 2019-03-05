/*
*Change Logs:
*Data           Author         		Notes
*2019-1-24     黄晖、肖春明      the first version
*/

#include "car_run.h"

/*引用 car_esp8266.c文件里的函数getCARDATA()获取小车的控制信息*/
extern  char getCARDATA(void);

static rt_thread_t thread = RT_NULL;

/*小车运行线程 thread的入口*/
static void car_run_entry(void * parameter)
{	int flag=0;
	
	while(1)
	{		
		
		//rt_kprintf("%c\n",getCARDATA());
		
		switch(getCARDATA())
		{
				/*控制信息为字符 ‘0’时，控制小车停止*/
			case '0':	car_run_control_stop();		break;
				/*控制信息为字符 ‘1’时，控制小车左转*/
			case '1':	car_run_control_left();		break;
				/*控制信息为字符 ‘2’时，控制小车前进*/
			case '2':	car_run_control_forward();	break;
				/*控制信息为字符 ‘3’时，控制小车后退*/
			case '3':	car_run_control_back();		break;
				/*控制信息为字符 ‘4’时，控制小车右转*/
			case '4':	car_run_control_right();	break;
				/*控制信息为字符 ‘5’时，控制小车低速行驶*/
			case '5':	if(flag!=0)			//小车状态为 ON 时，才能改变速度
							car_speed_low();		break;
				/*控制信息为字符 ‘6’时，控制小车中速行驶*/
			case '6':	if(flag!=0)
							car_speed_medium();		break;
				/*控制信息为字符 ‘7’时，控制小车全速行驶*/
			case '7':	if(flag!=0)
							car_speed_high();		break;
				/*控制信息为字符 ‘8’时，控制小车停止行驶*/
			case '8':	car_speed_stop();
						car_run_control_stop();
						flag=0;						break;
				/*控制信息为字符 ‘9’时，控制小车启动*/
			case '9':	car_speed_on();
						flag=1;				break;
			default:								break;
		}
		
		rt_thread_mdelay(50);
		
	}
}

int car_run(void)
{	
	 /* 创建动态线程 */
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

/*小车运行初始化*/
void car_run_init(void)
{
	led_init();
	car_esp8266_init();			// esp8266模块初始化
	at_client_port_init();		// URC数据处理初始化
	car_run_control_init();		//小车行走控制初始化
	car_speed_init();			//小车速度初始化
	car_screen_init();			//小车显示初始化
	car_run();					//小车运行
	
}

