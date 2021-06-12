/*
 * @file name: tm1650.c
 * @Descripttion: 
 * @Author: xjw
 * @email: fudi.xu@tuya.com
 * @Copyright: HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @Company: http://www.tuya.com
 * @Date: 2021-05-09 16:45:15
 * @LastEditors: xjw
 * @LastEditTime: 2021-05-10 12:05:48
 */

#ifndef __TUYA_TM1650_H__
#define __TUYA_TM1650_H__

#include "uni_log.h"
#include "tuya_cloud_error_code.h"
#include "tuya_pin.h"
#include "tuya_i2c.h"
#include "tuya_hal_system.h"



void tm1650_led_init(void);
void tm1650_close(void);
#endif