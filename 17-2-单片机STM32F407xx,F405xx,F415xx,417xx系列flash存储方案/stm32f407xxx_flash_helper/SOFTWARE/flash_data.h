#ifndef FLASH_DATA_Cc_
#define FLASH_DATA_Cc_

#ifndef FLASH_DATA_Cx_//如果没有定义
#define FLASH_DATA_Cx_ extern
#else
#define FLASH_DATA_Cx_
#endif

#include "stm32f4xx_conf.h"

//设置转速
void flash_data_set_speed(u32 data);
//获取设置的转速
u32 flash_data_get_speed(char mode);

//设置计数值
void flash_data_set_count(u32 data);
//获取设置的计数值
u32 flash_data_get_count(char mode);


//设置水位0,湿度1,xxx值2,xxxx值3
void flash_data_set_water_humidity_xxx_xxxx(char type,char data);
//获取水位0,湿度1,xxx值2,xxxx值3
//返回255,说明错误
char flash_data_get_water_humidity_xxx_xxxx(char type,char mode);


//设置一个最长不到1000字节的字符串
void flash_data_set_1000bytes(char *data,u32 data_len);
//获取一个最长1000字节的字符串
//data 的长度是1000字节
void flash_data_get_1000bytes(char *data,char mode);


#endif
