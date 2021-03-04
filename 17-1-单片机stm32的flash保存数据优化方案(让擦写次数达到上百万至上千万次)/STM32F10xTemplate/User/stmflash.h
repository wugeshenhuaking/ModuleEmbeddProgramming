#ifndef __STMFLASH_H__
#define __STMFLASH_H__
#include <stm32f10x.h>


//用户根据自己的需要设置
#define STM32_FLASH_SIZE 64 	 		//所选STM32的FLASH容量大小(单位为K)
#define STM32_FLASH_WREN 1        //使能FLASH写入(0，不是能;1，使能)

#define STM32_FLASH_BASE 0x8000000 	//STM32 FLASH的起始地址

//数据存储地址(默认存储到最后4页)
#if STM32_FLASH_SIZE == 64 //1KB每页
	#define FLASH_DATA_ADDR_1  (STM32_FLASH_BASE+1024*60)
	#define FLASH_DATA_ADDR_2  (STM32_FLASH_BASE+1024*61)
	#define FLASH_DATA_ADDR_3  (STM32_FLASH_BASE+1024*62)
	#define FLASH_DATA_ADDR_4  (STM32_FLASH_BASE+1024*63)
#elif STM32_FLASH_SIZE == 128 //1KB每页
	#define FLASH_DATA_ADDR_1  (STM32_FLASH_BASE+1024*124)
	#define FLASH_DATA_ADDR_2  (STM32_FLASH_BASE+1024*125)
	#define FLASH_DATA_ADDR_3  (STM32_FLASH_BASE+1024*126)
	#define FLASH_DATA_ADDR_4  (STM32_FLASH_BASE+1024*127)
#elif STM32_FLASH_SIZE == 256 //2KB每页
	#define FLASH_DATA_ADDR_1  (STM32_FLASH_BASE+1024*248)
	#define FLASH_DATA_ADDR_2  (STM32_FLASH_BASE+1024*250)
	#define FLASH_DATA_ADDR_3  (STM32_FLASH_BASE+1024*252)
	#define FLASH_DATA_ADDR_4  (STM32_FLASH_BASE+1024*254)
#elif STM32_FLASH_SIZE == 512 //2KB每页	
	#define FLASH_DATA_ADDR_1  (STM32_FLASH_BASE+1024*504)
	#define FLASH_DATA_ADDR_2  (STM32_FLASH_BASE+1024*506)
	#define FLASH_DATA_ADDR_3  (STM32_FLASH_BASE+1024*508)
	#define FLASH_DATA_ADDR_4  (STM32_FLASH_BASE+1024*510)
#else
	#define FLASH_DATA_ADDR_1  (STM32_FLASH_BASE+1024*(STM32_FLASH_SIZE-4))
	#define FLASH_DATA_ADDR_2  (STM32_FLASH_BASE+1024*(STM32_FLASH_SIZE-3))
	#define FLASH_DATA_ADDR_3  (STM32_FLASH_BASE+1024*(STM32_FLASH_SIZE-2))
	#define FLASH_DATA_ADDR_4  (STM32_FLASH_BASE+1024*(STM32_FLASH_SIZE-1))
#endif

u16 STMFLASH_ReadHalfWord(u32 faddr);		  //读出半字  
void STMFLASH_WriteLenByte(u32 WriteAddr,u32 DataToWrite,u16 Len);	//指定地址开始写入指定长度的数据
u32 STMFLASH_ReadLenByte(u32 ReadAddr,u16 Len);						//指定地址开始读取指定长度数据
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);		//从指定地址开始写入指定长度的数据
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);   		//从指定地址开始读出指定长度的数据

char WriteFlashHalfWord(uint32_t WriteAddress,u16 data);
char FlashErasePage(uint32_t EraseAddress,u16 PageCnt);	
char FlashErasePages(uint32_t EraseAddress,u16 PageCnt);
void WriteFlashHalfWords(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);
#endif

















