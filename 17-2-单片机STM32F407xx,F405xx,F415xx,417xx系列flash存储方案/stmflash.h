#ifndef __STMFLASH_H__
#define __STMFLASH_H__

#include "stm32f4xx_conf.h"

//FLASH��ʼ��ַ
#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH����ʼ��ַ
 

//FLASH ��������ʼ��ַ
#define ADDR_FLASH_SECTOR_0     ((u32)0x08000000) 	//����0��ʼ��ַ, 16 Kbytes  
#define ADDR_FLASH_SECTOR_1     ((u32)0x08004000) 	//����1��ʼ��ַ, 16 Kbytes  
#define ADDR_FLASH_SECTOR_2     ((u32)0x08008000) 	//����2��ʼ��ַ, 16 Kbytes  
#define ADDR_FLASH_SECTOR_3     ((u32)0x0800C000) 	//����3��ʼ��ַ, 16 Kbytes  
#define ADDR_FLASH_SECTOR_4     ((u32)0x08010000) 	//����4��ʼ��ַ, 64 Kbytes  
#define ADDR_FLASH_SECTOR_5     ((u32)0x08020000) 	//����5��ʼ��ַ, 128 Kbytes  
#define ADDR_FLASH_SECTOR_6     ((u32)0x08040000) 	//����6��ʼ��ַ, 128 Kbytes  
#define ADDR_FLASH_SECTOR_7     ((u32)0x08060000) 	//����7��ʼ��ַ, 128 Kbytes  
#define ADDR_FLASH_SECTOR_8     ((u32)0x08080000) 	//����8��ʼ��ַ, 128 Kbytes  
#define ADDR_FLASH_SECTOR_9     ((u32)0x080A0000) 	//����9��ʼ��ַ, 128 Kbytes  
#define ADDR_FLASH_SECTOR_10    ((u32)0x080C0000) 	//����10��ʼ��ַ,128 Kbytes  
#define ADDR_FLASH_SECTOR_11    ((u32)0x080E0000) 	//����11��ʼ��ַ,128 Kbytes  


/**
* @brief  ����ĳһ������
* @param  sector_start_addr  Ҫ������������ʼ��ַ
* @param  sector_stop_addr   Ҫ����������������ַ
* @param  None
* @retval 0:�ɹ�
* @example 
* @waing  
**/
int FlashEraseSector(u32 sector_start_addr,u32 sector_stop_addr);

/**
* @brief  ָ����ַд��ָ�����ȵ���(��Ҫ���Ȳ����ſ�ʹ�ô˺���)
* @param  WriteAddr  ��ʼд��ĵ�ַ
* @param  pBuffer    д�������
* @param  NumToWrite д������ݸ���
* @retval 0:�ɹ�
* @example 
* @waing  
**/
int FlashWriteWords(u32 WriteAddr,u32 *pBuffer,u32 NumToWrite);

/**
* @brief  ָ����ַ��ȡһ����
* @param  faddr  ��ȡ�ĵ�ַ
* @param  none
* @param  none
* @retval ��ȡ����
* @example 
* @waing  
**/
u32 STMFLASH_ReadWord(u32 faddr);


/**
* @brief  ָ����ַ��ȡָ�����ȵ���
* @param  ReadAddr:��ʼ��ַ
* @param  pBuffer:����ָ��
* @param  NumToRead:��ȡ�ĸ���
* @retval ��ȡ����
* @example 
* @waing  
**/
void STMFLASH_Read(u32 ReadAddr,u32 *pBuffer,u32 NumToRead);   		//��ָ����ַ��ʼ����ָ�����ȵ�����
						   
#endif

















