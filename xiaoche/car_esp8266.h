/*
*Change Logs:
*Data           Author         Notes
*2019-1-24      Huanghui       the first version
*/
#ifndef __CAR_ESP8266_H
#define __CAR_ESP8266_H

#include <rtdevice.h>
#include <rtthread.h>
#include <at.h>
#include "car_led.h"

int car_esp8266_init(void);		// esp8266设备初始化
int at_client_port_init(void);	// URC数据处理初始化

#endif

