/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-07-29     Arda.Fu      first implementation
 */
#include <rtthread.h>
#include "car_control_esp.h"
#include "car_screen.h"
#include "car_key.h"

int main(void)
{
    /* user app entry */
	car_screen_init();
	car_esp_init();
	car_key_init();
	
	
//    return 0;
}
