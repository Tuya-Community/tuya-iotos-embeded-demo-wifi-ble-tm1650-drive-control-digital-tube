/*
 * @file name: 
 * @Descripttion: 
 * @Author: xjw
 * @email: fudi.xu@tuya.com
 * @Copyright: HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @Company: http://www.tuya.com
 * @Date: 2021-05-09 16:35:33
 * @LastEditors: xjw
 * @LastEditTime: 2021-05-10 15:21:28
 */
#include "tm1650.h"
typedef struct {
    tuya_i2c_t    *i2c;
} tm1650_dev_t;
/*============================ PROTOTYPES ====================================*/
void tm1650_led_init(void);
void tm1650_init(tm1650_dev_t *dev);
void tm1650_close(void);
void TM1650_Write(uint8_t addr, uint8_t data, tm1650_dev_t *dev);
void TM1650_SetDisplay(uint8_t brightness, uint8_t mode, uint8_t state);
void TM1650_SetNumber(uint8_t index, uint8_t mode,uint8_t num);
/*============================ IMPLEMENTATION ================================*/
static tm1650_dev_t tm1650_dev;
static uint8_t s_7number[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};   // 7段显示方式0~9
static uint8_t s_8number[10] = {0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF};   // 8段显示方式0~9
/**
 * @Function: tm1650_led_init
 * @Description: tm1650_led display init
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: 
 */
void tm1650_led_init(void)
{
	/*SCL_PIN:PA24 SDA_PIN:PA26*/
    tuya_i2c_sw_cfg_t   sw_cfg;
    TUYA_I2C_SW_CFG_INIT(&sw_cfg, TUYA_PA24, TUYA_PA26, 1);
    tuya_sw_i2c_register(TUYA_I2C0, &sw_cfg);
    tm1650_init(&tm1650_dev);

}
/**
 * @Function: tm1650 init
 * @Description: Equip with IIC equipment and set the gray level of digital tube
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: 
 */
void tm1650_init(tm1650_dev_t *dev)
{
    uint8_t buffer[2];
	//! looking for IIC handle
    dev->i2c = tuya_driver_find(TUYA_DRV_I2C, TUYA_I2C0);
    //! no device addr
    TUYA_I2C_MASTER_CFG(dev->i2c, 0x00);
    tuya_i2c_init(dev->i2c);

    buffer[0] = 0x48;             //! register addr
    buffer[1] = 0x71;      //! power set

    tuya_i2c_master_send(dev->i2c, 0x00, TUYA_I2C_NO_START | TUYA_I2C_WR, buffer, 2);
}
/**
 * @Function: tm1650_close
 * @Description: Turn off the digital display
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: 
 */
void tm1650_close(void)
{
    TM1650_Write(0x68, 0x00, &tm1650_dev);
    TM1650_Write(0x6a, 0x00, &tm1650_dev);
    TM1650_Write(0x6e, 0x00, &tm1650_dev);
}

/**
 * @Function: TM1650_Write
 * @Description: Write data to TM1650
 * @Input: addr:register addr   data: 
 * @Output: none
 * @Return: none
 * @Others: 
 */
void TM1650_Write(uint8_t addr, uint8_t data, tm1650_dev_t *dev)
{          
    uint8_t     buffer[2];
    buffer[0] = addr;   //! register addr
    buffer[1] = data;      //! Transmitted data
    tuya_i2c_master_send(dev->i2c, 0x00, TUYA_I2C_NO_START | TUYA_I2C_WR, buffer, 2);
}

/**
 * @Function: TM1650_SetDisplay
 * @Description: Setting display parameters
 * @Input: brightness:1-8   mode: Paragraph 7/Paragraph 8   state :display on/off
 * @Output: none
 * @Return: none
 * @Others: 
 */
void TM1650_SetDisplay(uint8_t brightness, uint8_t mode, uint8_t state)
{       
    if(state)
    {
        if(mode == 7)                                                   // 7段显示方式
        {
            TM1650_Write(0x48, brightness*16 + 1*4 + 1, &tm1650_dev);
        }
        else if(mode == 8)                                              // 8段显示方式
        {
            TM1650_Write(0x48, brightness*16 + 1, &tm1650_dev);                      
        }
    }
    else
    {
        TM1650_Write(0x48, 0x00,&tm1650_dev);                                       // 关闭显示
    }
}

/**
 * @Function: TM1650_SetNumber
 * @Description: display num
 * @Input: index:Which number  mode: Paragraph 7/Paragraph 8   num :Display number
 * @Output: none
 * @Return: none
 * @Others: 
 */
void TM1650_SetNumber(uint8_t index, uint8_t mode, uint8_t num)
{
    uint8_t indexAddr = 0;
    uint8_t numValue = 0;
    
    if(index == 1)
    {
        indexAddr = 0x68;
    }
    else if(index == 2)
    {
        indexAddr = 0x6A;
    }
    else if(index == 3)
    {
        indexAddr = 0x6C;
    }
    else if(index == 4)
    {
        indexAddr = 0x6E;
    }
    
    if(mode == 7)                                                       // 7段显示方式
    {
        numValue = s_7number[num];
    }
    else if(mode == 8)                                                  // 8段显示方式
    {
        numValue = s_8number[num];                      
    }
    
    TM1650_Write(indexAddr, numValue, &tm1650_dev);
}

