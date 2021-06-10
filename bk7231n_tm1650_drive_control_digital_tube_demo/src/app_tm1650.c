/*
 * @Author: xjw
 * @email: fudi.xu@tuya.com
 * @LastEditors: xjw
 * @file name: app_tm1650.c
 * @Description: tm1650 test init process
 * @Copyright: HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @Company: http://www.tuya.com
 * @Date: 2021-5-09 15:22:03
 * @LastEditTime: 2021-05-10 17:35:04
 */
/* Includes ------------------------------------------------------------------*/
#include "tuya_iot_wifi_api.h"
#include "tuya_hal_thread.h"
#include "tuya_hal_system.h"
#include "uni_thread.h"
/* Private includes ----------------------------------------------------------*/
#include "tm1650.h"
#include "app_tm1650.h"

/* Private variables ---------------------------------------------------------*/
DP_VALUE_T displaynum1_s = {
    .dp_id = DP_NUM1,
    .value = 0,
};
DP_VALUE_T displaynum2_s = {
    .dp_id = DP_NUM2,
    .value = 0,
};
DP_VALUE_T displaynum3_s = {
    .dp_id = DP_NUM3,
    .value = 0,
};
DP_VALUE_T displaynum4_s = {
    .dp_id = DP_NUM4,
    .value = 0,
};
/* Private function prototypes -----------------------------------------------*/
STATIC VOID app_data_report_thread(PVOID_T pArg);
/* Private functions ---------------------------------------------------------*/
/*TM1650 test init*/
/**
 * @Function: app_tm1650_init
 * @Description: tm1650 IIC communication control digital tube display init
 * @Input: APP_MODE：Application mode
 * @Output: none
 * @Return: op_ret   execution result
 * @Others: 
 */
OPERATE_RET app_tm1650_init(IN APP_MODE mode)
{
    OPERATE_RET op_ret = OPRT_OK;

    if(APP_NORMAL == mode) {
        tm1650_led_init();

        tuya_hal_thread_create(NULL, "thread_data_report", 512*4, TRD_PRIO_5, app_data_report_thread, NULL);
    }else {
        //not factory test mode
    }

    return op_ret;
}
/**
 * @Function: app_data_report_thread
 * @Description: dp data report thread function
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: 
 */
STATIC VOID app_data_report_thread(PVOID_T pArg)
{   
    while(1) {

        app_report_all_dp_status();
        /*delay 10s */
        tuya_hal_system_sleep(10*1000);
    }
}

/**
 * @Function: app_report_all_dp_status
 * @Description: app dp data report function
 * @Input: none 
 * @Output: none
 * @Return: none
 * @Others: 
 */
VOID app_report_all_dp_status(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;

    INT_T dp_cnt = 0;
    dp_cnt = 4;

    TY_OBJ_DP_S *dp_arr = (TY_OBJ_DP_S *)Malloc(dp_cnt*SIZEOF(TY_OBJ_DP_S));
    if(NULL == dp_arr) {
        PR_ERR("malloc failed");
        return;
    }

    memset(dp_arr, 0, dp_cnt*SIZEOF(TY_OBJ_DP_S));

    dp_arr[0].dpid = displaynum1_s.dp_id;
    dp_arr[0].type = PROP_VALUE;
    dp_arr[0].time_stamp = 0;
    dp_arr[0].value.dp_value = displaynum1_s.value;

    dp_arr[1].dpid = displaynum2_s.dp_id;
    dp_arr[1].type = PROP_VALUE;
    dp_arr[1].time_stamp = 0;
    dp_arr[1].value.dp_value = displaynum2_s.value;

    dp_arr[2].dpid = displaynum3_s.dp_id;
    dp_arr[2].type = PROP_VALUE;
    dp_arr[2].time_stamp = 0;
    dp_arr[2].value.dp_value = displaynum3_s.value;

    dp_arr[3].dpid = displaynum3_s.dp_id;
    dp_arr[3].type = PROP_VALUE;
    dp_arr[3].time_stamp = 0;
    dp_arr[3].value.dp_value = displaynum3_s.value;

    op_ret = dev_report_dp_json_async(NULL,dp_arr,dp_cnt);
    Free(dp_arr);
    if(OPRT_OK != op_ret) {
        PR_ERR("dev_report_dp_json_async relay_config data error,err_num",op_ret);
    }

    PR_DEBUG("dp_query report_all_dp_data");
    return;
}

/**
 * @Function: deal_dp_proc
 * @Description: dp data deal function
 * @Input: TY_OBJ_DP_S 
 * @Output: none
 * @Return: none
 * @Others: 
 */
VOID deal_dp_proc(IN CONST TY_OBJ_DP_S *root)
{
    UCHAR_T dpid;

    dpid = root->dpid;
    PR_DEBUG("dpid:%d",dpid);
    
    switch (dpid) {
    
    case DP_NUM1:
    {
        TM1650_SetNumber(1, 7, root->value.dp_value);
    }
        break;
    case DP_NUM2:
    {
        TM1650_SetNumber(2, 7, root->value.dp_value);
    }
        break;
    case DP_NUM3:
    {
        TM1650_SetNumber(3, 7, root->value.dp_value);
    }
        break;
    case DP_NUM4:
    {
        TM1650_SetNumber(4, 7, root->value.dp_value);
    }
        break;
    default:
        break;
    }

    app_report_all_dp_status();

    return;

}