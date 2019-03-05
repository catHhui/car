/*
*Change Logs:
*Data           Author         Notes
*2019-1-27    xiaochunming      the first version
*/


#include "car_screen.h"

/*���� car_esp8266.c�ļ���ĺ���getCARDATA()��ȡС���Ŀ�����Ϣ*/
extern  char getCARDATA(void);

static rt_thread_t thread1 = RT_NULL;

#define SAMPLE_UART_NAME       "uart2"  /* �����豸���� */
static rt_device_t serial;              /* �����豸��� */

/*�����򴮿������͵���Ϣ*/
char STR[]={0xff,0xff,0xff,0xff};
char str0[]="t0.txt=\"ON  \"";
char str1[]="t0.txt=\"OFF \"";
char str2[]="t3.txt=\"��  \"";
char str3[]="t3.txt=\"ǰ  \"";
char str4[]="t3.txt=\"��  \"";
char str5[]="t3.txt=\"��  \"";
char str6[]="t3.txt=\"NULL\"";
char str7[]="t4.txt=\"����\"";
char str8[]="t4.txt=\"����\"";
char str9[]="t4.txt=\"����\"";
char str10[]="t4.txt=\"ֹͣ\"";


/*��������ʾ�߳� thread1�����*/
static void car_screen_entry(void * parameter)
{
	char ch=NULL;		//��Ŵ�������Ҫ��ӡ����Ϣ��Ŀ����
						//��С��������Ϣ�ı�ʱ��������ֻҪ��ӡһ��
	char *str;			//�����ַ�ָ�룬Ϊ����������
	static int flag=0;			//С�����ر�־��0Ϊ�أ�1Ϊ��
	
	while(1)
	{
		/******�жϵ�ǰ��������ʾ��Ϣ�Ƿ�Ϊ����***
		 ******���Ǿʹ�ӡ������Ϣ			   ***/
		if(ch!=getCARDATA())
		{
			
			ch=getCARDATA();		//���´�������Ҫ��ӡ����Ϣ
			
			switch(ch)
			{
				
				case '0':	str=str6;		break;
				case '1':	str=str2;		break;
				case '2':	str=str3;		break;
				case '3':	str=str4;		break;
				case '4':	str=str5;		break;
				case '5':	if(flag==1)		//С��״̬Ϊ ON ʱ���Ŵ�ӡ�ٶ���Ϣ
								str=str7;	break;
				case '6':	if(flag==1)
								str=str8;	break;
				case '7':	if(flag==1)
								str=str9;	break;
				case '8':	str=str1;
							flag=0;
							/*С��״̬Ϊ OFFʱ�����Ӵ�������ӡ��Ϣ*/
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
			
			/* �򴮿��������ַ�������ӡС��״̬��Ϣ */
			rt_device_write(serial, 0,str,13);
			rt_device_write(serial, 0, STR, (sizeof(STR) - 1));
			
			
		}
		rt_thread_mdelay(20);
	}
}
int car_screen_init(void)
{	
	 /* ���ò��� */
	struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
	
	/* ���Ҵ����豸 */
	serial = rt_device_find(SAMPLE_UART_NAME);

	/* ���жϽ��ռ���ѯ����ģʽ�򿪴����豸 */
	rt_device_open(serial,RT_DEVICE_FLAG_INT_RX);
	
	config.baud_rate = BAUD_RATE_9600;
	rt_device_control(serial, RT_DEVICE_CTRL_CONFIG, &config);
	
	
	 /* ������̬�߳� */
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
