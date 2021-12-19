#ifndef mcu_flash_h_
#define mcu_flash_h_

#ifndef mcu_flash_c_
#define mcu_flash_cx_ extern
#else
#define mcu_flash_cx_ 
#endif

#include "hc32_ddl.h"
#include <stdio.h>


#if 1 //�Ƿ��ӡ��־
#define mcu_flash_printf  printf
#else
#define mcu_flash_printf(...)
#endif


/*����Flash*/
#define FLASH_MCU_BASE 0          //Flash����ַ
#define FLASH_SECTOR_SIZE (8*1024) 	//һ��������С(KB)



/**
* @brief  ָ����ַ��ȡһ����
* @param  faddr  ��ȡ�ĵ�ַ
* @param  none
* @param  none
* @retval ��ȡ����
* @example 
* @waing  
**/
uint32_t mcu_flash_read_word(uint32_t faddr);


/**
* @brief  ָ����ַ��ȡָ�����ȵ���
* @param  ReadAddr:��ʼ��ַ
* @param  pBuffer:����ָ��
* @param  NumToRead:��ȡ�ĸ���
* @retval ��ȡ����
* @example 
* @waing  
**/
void mcu_flash_read_words(uint32_t ReadAddr,uint32_t *pBuffer,uint32_t NumToRead);


/**
* @brief  ����һ�����߶������
* @param  sector_start_index  Ҫ������������ʼ
* @param  sector_stop_index   Ҫ��������������
* @param  None
* @retval 0:�ɹ�
* @example 
1.������3������ mcu_flash_erase_sector(3*FLASH_SECTOR_SIZE, 3*FLASH_SECTOR_SIZE);
2.������3�������͵�4������ mcu_flash_erase_sector(3*FLASH_SECTOR_SIZE, 4*FLASH_SECTOR_SIZE);
* @waing  
**/
int mcu_flash_erase_sector(uint32_t sector_start_addr,uint32_t sector_stop_addr);


/**
* @brief  ָ����ַд��һ����(u32)(��Ҫ���Ȳ����ſ�ʹ�ô˺���)
* @param  WriteAddr  ��ʼд��ĵ�ַ
* @param  data    д�������
* @param  none
* @retval 0:�ɹ�
* @example 
* @waing  
**/
int mcu_flash_write_word(uint32_t WriteAddr,uint32_t data);


/**
* @brief  ָ����ַд��ָ�����ȵ���(��Ҫ���Ȳ����ſ�ʹ�ô˺���)
* @param  WriteAddr  ��ʼд��ĵ�ַ
* @param  pBuffer    д�������
* @param  NumToWrite д������ݸ���
* @retval 0:�ɹ�
* @example 
д���ݵ�0x0007C000��ַ
uint32_t data[255];
mcu_flash_write_words(0x0007C000,data,255);
* @waing  
**/
int mcu_flash_write_words(uint32_t WriteAddr,uint32_t *pBuffer,uint32_t NumToWrite);


#endif

