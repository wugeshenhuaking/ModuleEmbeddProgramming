#ifndef mcu_flash_h_
#define mcu_flash_h_

#ifndef mcu_flash_c_
#define mcu_flash_cx_ extern
#else
#define mcu_flash_cx_ 
#endif

#include "hc32_ddl.h"
#include <stdio.h>


#if 1 //是否打印日志
#define mcu_flash_printf  printf
#else
#define mcu_flash_printf(...)
#endif


/*设置Flash*/
#define FLASH_MCU_BASE 0          //Flash基地址
#define FLASH_SECTOR_SIZE (8*1024) 	//一个扇区大小(KB)



/**
* @brief  指定地址读取一个字
* @param  faddr  读取的地址
* @param  none
* @param  none
* @retval 读取的字
* @example 
* @waing  
**/
uint32_t mcu_flash_read_word(uint32_t faddr);


/**
* @brief  指定地址读取指定长度的字
* @param  ReadAddr:起始地址
* @param  pBuffer:数据指针
* @param  NumToRead:读取的个数
* @retval 读取的字
* @example 
* @waing  
**/
void mcu_flash_read_words(uint32_t ReadAddr,uint32_t *pBuffer,uint32_t NumToRead);


/**
* @brief  擦除一个或者多个扇区
* @param  sector_start_index  要擦除的扇区起始
* @param  sector_stop_index   要擦除的扇区结束
* @param  None
* @retval 0:成功
* @example 
1.擦除第3个扇区 mcu_flash_erase_sector(3*FLASH_SECTOR_SIZE, 3*FLASH_SECTOR_SIZE);
2.擦除第3个扇区和第4个扇区 mcu_flash_erase_sector(3*FLASH_SECTOR_SIZE, 4*FLASH_SECTOR_SIZE);
* @waing  
**/
int mcu_flash_erase_sector(uint32_t sector_start_addr,uint32_t sector_stop_addr);


/**
* @brief  指定地址写入一个字(u32)(需要事先擦除才可使用此函数)
* @param  WriteAddr  开始写入的地址
* @param  data    写入的数据
* @param  none
* @retval 0:成功
* @example 
* @waing  
**/
int mcu_flash_write_word(uint32_t WriteAddr,uint32_t data);


/**
* @brief  指定地址写入指定长度的字(需要事先擦除才可使用此函数)
* @param  WriteAddr  开始写入的地址
* @param  pBuffer    写入的数据
* @param  NumToWrite 写入的数据个数
* @retval 0:成功
* @example 
写数据到0x0007C000地址
uint32_t data[255];
mcu_flash_write_words(0x0007C000,data,255);
* @waing  
**/
int mcu_flash_write_words(uint32_t WriteAddr,uint32_t *pBuffer,uint32_t NumToWrite);


#endif

