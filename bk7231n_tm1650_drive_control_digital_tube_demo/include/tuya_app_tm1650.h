/*
 * @Author: xjw
 * @email: fudi.xu@tuya.com
 * @LastEditors: xjw
 * @file name: app_tm1650.h
 * @Description: tm1650 test init process include file
 * @Copyright: HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @Company: http://www.tuya.com
 * @Date: 2021-05-09 16:50:03
 * @LastEditTime: 2021-05-10 16:50:14
 */

#ifndef __TUYA_APP_TM1650_H__
#define __TUYA_APP_TM1650_H__

#include "uni_log.h"
#include "tuya_cloud_error_code.h"
#include "tuya_cloud_com_defs.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/***********************************************************
*************************variable define********************
***********************************************************/
#define DP_NUM1 101
#define DP_NUM2 102
#define DP_NUM3 103
#define DP_NUM4 104

typedef enum{
    APP_NORMAL,       //normal mode
    APP_PRODTEST      //prodact test mode
}APP_MODE;


typedef struct {
    UINT8_T dp_id;
    
    int value;
}DP_VALUE_T;
/********************************************************************************
 * FUNCTION:       app_plant_init
 * DESCRIPTION:    application initialization
 * INPUT:          mode:application mode
 * OUTPUT:         none
 * RETURN:         none
 * OTHERS:         none
 * HISTORY:        2021-05-09
 *******************************************************************************/
OPERATE_RET app_tm1650_init(IN APP_MODE mode);

/********************************************************************************
 * FUNCTION:       deal_dp_proc
 * DESCRIPTION:    deal the data sented by app
 * INPUT:          root:app issued data structure
 * OUTPUT:         none
 * RETURN:         none
 * OTHERS:         none
 * HISTORY:        2021-05-09
 *******************************************************************************/
VOID deal_dp_proc(IN CONST TY_OBJ_DP_S *root);

/*********************************************************************************
 * FUNCTION:       app_report_all_dp_status
 * DESCRIPTION:    report all dp date
 * INPUT:          none
 * OUTPUT:         none
 * RETURN:         none
 * OTHERS:         dp_cnt needs to be modified when adding or deleting the dp function
 * HISTORY:        2021-05-09
 *******************************************************************************/
VOID app_report_all_dp_status(VOID);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif  /* __LIHGT_INIT_H__ */