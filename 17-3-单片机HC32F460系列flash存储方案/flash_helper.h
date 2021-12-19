#ifndef FLASH_HELPER_H_
#define FLASH_HELPER_H_

#ifndef FLASH_HELPER_C_//如果没有定义
#define FLASH_HELPER_Cx_ extern
#else
#define FLASH_HELPER_Cx_
#endif

#include <string.h>
#include <stdio.h>
#include "mcu_flash.h"


#if 0 //是否打印日志
#define flash_helper_printf  printf
#else
#define flash_helper_printf(...)
#endif


//最大存储的数据(u32类型)个数,根据用户实际修改.
//数组最后一位存储的为0x55555555;用户不能使用数组的最后一位
#define FlashHelperDataLen 512

#define FlashHelperUUID 0x55555555 //最后一位的标识符

typedef struct flash_helper
{
	/*存储用户数据的数组*/
	uint32_t FlashHelperData[FlashHelperDataLen];
	/*数组可以保存的字节数*/
	uint32_t FlashHelperDataSize;
	/*扇区的开始地址*/
	uint32_t FlashHelperStartAddr;
	/*扇区的结束地址*/
	uint32_t FlashHelperEndAddr;
	/*记录当前操作的地址*/	
	uint32_t FlashHelperSaveAddr;
} flash_helper_typedef;

FLASH_HELPER_Cx_ flash_helper_typedef flash_helper_struct;


/**
* @brief  flash_helper_init
* @param  sectors_addr  使用哪一个扇区保存数据(扇区开始地址)
* @param  None
* @param  None
* @retval 0:成功
* @example 
* @waing  
**/
int flash_helper_init(uint32_t sectors_addr);

/**
* @brief  更改完数组里面的值,调用此函数把数组数据写入flash
* @param  None
* @param  None
* @param  None
* @retval None
* @example 
* @waing  
**/
int flash_helper_update(void);

/**
* @brief   获取缓存的数据
* @param   index 从哪一位数据开始获取(0-)
* @param   data  返回的数据
* @param   datalen 获取的个数
* @retval  0:成功 1:没有缓存的数据
* @warning 
* @example 
**/
int flash_helper_get(uint32_t index,uint32_t *data, uint32_t datalen);
	
#endif













