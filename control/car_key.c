/*
*Change Logs:
*Data           Author         Notes
*2019-1-19      Huanghui       the first version
*/

#include <rtdevice.h>
#include <car_key.h>

static char CARDATA='0';

/*开关与速度按键扫描程序
**只能按一下
*/
int key_scan_speed(void)
{
	static unsigned char key_up=1;//按键按松开标志
	
	if(key_up&&(rt_pin_read(CAR_KEY_speed_low)==0||
				rt_pin_read(CAR_KEY_speed_medium)==0||
				rt_pin_read(CAR_KEY_speed_high)==0||
				rt_pin_read(CAR_KEY_on_off)==0))
	{
		rt_thread_mdelay(10);	//去抖动 
		key_up=0;				//按键按下
		
		/*确定哪个按键按下*/
		if(rt_pin_read(CAR_KEY_speed_low)==0)		return 5;
		if(rt_pin_read(CAR_KEY_speed_medium)==0)	return 6;
		if(rt_pin_read(CAR_KEY_speed_high)==0)		return 7;
		if(rt_pin_read(CAR_KEY_on_off)==0)			return 8;
	}else if(	rt_pin_read(CAR_KEY_speed_low)==1&&
				rt_pin_read(CAR_KEY_speed_medium)==1&&
				rt_pin_read(CAR_KEY_speed_high)==1&&
				rt_pin_read(CAR_KEY_on_off)==1)		key_up=1; 	 //按键松开
	
 	return 0;// 无按键按下
}

/*方向按键扫描程序
**常按
*/
int key_scan_dir(void)
{
	
	if(	rt_pin_read(CAR_KEY_left)==0||
		rt_pin_read(CAR_KEY_forward)==0||
		rt_pin_read(CAR_KEY_back)==0||
		rt_pin_read(CAR_KEY_right)==0)
	{
		rt_thread_mdelay(10);//去抖动 
		/*确定哪个按键按下*/
		if(rt_pin_read(CAR_KEY_left)==0)		return 1;
		if(rt_pin_read(CAR_KEY_forward)==0)		return 2;
		if(rt_pin_read(CAR_KEY_back)==0)		return 3;
		if(rt_pin_read(CAR_KEY_right)==0)		return 4;
	}	 
	
 	return 0;// 无按键按下
}
static rt_thread_t thread1= RT_NULL;

/*线程 thread的入口*/
static void car_key_entry(void * parameter)
{
	static int flag=0;		//开关状态，0为关，1为开
	int key_speed,key_dir;
	while(1)
	{
		key_speed=key_scan_speed();
		key_dir=key_scan_dir();
		if(key_speed==8)
		{
			
			switch(flag)
			{
				case 0:	rt_pin_write(4,PIN_LOW);//点亮LED0
						flag=1;					//设置小车状态为开
						CARDATA='9';
				
						rt_thread_mdelay(20);	//为了使 esp线程读取到字符 ‘9’，
												//而不是马上被字符 ‘0’ 覆盖掉
						break;
				case 1:	rt_pin_write(4,PIN_HIGH);//熄灭LED0
						flag=0;					//设置小车状态为关
						CARDATA='8';
						break;
			}
		}
		if(flag==1)
		{
			if(key_dir==0)		CARDATA='0';
			if(key_dir==1)		CARDATA='1';
			if(key_dir==2)		CARDATA='2';
			if(key_dir==3)		CARDATA='3';
			if(key_dir==4)		CARDATA='4';
		}
		if((flag==1)&&(key_speed!=0))			//若速度按键不按下，不执行下面代码
		{
			if(key_speed==5)	CARDATA='5';
			if(key_speed==6)	CARDATA='6';
			if(key_speed==7)	CARDATA='7';
			
			rt_thread_mdelay(20);				//为了使 esp线程读取到字符 ‘9’，
												//而不是马上被字符 ‘0’ 覆盖掉
			
		}
	}
	
}

int car_key_init(void)
{
	/*按键引脚初始化*/
	rt_pin_mode(CAR_KEY_left,PIN_MODE_INPUT_PULLUP);
	rt_pin_mode(CAR_KEY_forward,PIN_MODE_INPUT_PULLUP);
	rt_pin_mode(CAR_KEY_back,PIN_MODE_INPUT_PULLUP);
	rt_pin_mode(CAR_KEY_right,PIN_MODE_INPUT_PULLUP);
	rt_pin_mode(CAR_KEY_speed_low,PIN_MODE_INPUT_PULLUP);
	rt_pin_mode(CAR_KEY_speed_medium,PIN_MODE_INPUT_PULLUP);
	rt_pin_mode(CAR_KEY_speed_high,PIN_MODE_INPUT_PULLUP);
	rt_pin_mode(CAR_KEY_on_off,PIN_MODE_INPUT_PULLUP);
	rt_pin_mode(4,PIN_MODE_OUTPUT);
	
	/* 创建动态线程 */
    thread1= rt_thread_create(	"car_key",
								car_key_entry,
								RT_NULL,
                                512, 20, 20);
    if (thread1 != RT_NULL)
    {
        rt_thread_startup(thread1);
    }
	
	return 0;
	
}
/*获取CARDATA内容*/
char getCARDATA(void)
{
	return CARDATA;
}


