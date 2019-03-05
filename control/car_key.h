/*
*Change Logs:
*Data           Author         Notes
*2019-1-19      Huanghui       the first version
*/

#ifndef __CAR_KEY_H
#define __CAR_KEY_H

#include <rtthread.h>
#include "car_led.h"






#define  CAR_KEY_left			10		//PF0
#define  CAR_KEY_forward		11		//PF1
#define  CAR_KEY_back			12		//PF2
#define  CAR_KEY_right			13		//PF3
#define  CAR_KEY_speed_low		14		//PF4
#define  CAR_KEY_speed_medium	15		//PF5
#define  CAR_KEY_speed_high		18		//PF6
#define  CAR_KEY_on_off			19		//PF7

int car_key_init(void);

#endif

