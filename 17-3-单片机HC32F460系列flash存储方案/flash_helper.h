#ifndef FLASH_HELPER_H_
#define FLASH_HELPER_H_

#ifndef FLASH_HELPER_C_//���û�ж���
#define FLASH_HELPER_Cx_ extern
#else
#define FLASH_HELPER_Cx_
#endif

#include <string.h>
#include <stdio.h>
#include "mcu_flash.h"


#if 0 //�Ƿ��ӡ��־
#define flash_helper_printf  printf
#else
#define flash_helper_printf(...)
#endif


//���洢������(u32����)����,�����û�ʵ���޸�.
//�������һλ�洢��Ϊ0x55555555;�û�����ʹ����������һλ
#define FlashHelperDataLen 512

#define FlashHelperUUID 0x55555555 //���һλ�ı�ʶ��

typedef struct flash_helper
{
	/*�洢�û����ݵ�����*/
	uint32_t FlashHelperData[FlashHelperDataLen];
	/*������Ա�����ֽ���*/
	uint32_t FlashHelperDataSize;
	/*�����Ŀ�ʼ��ַ*/
	uint32_t FlashHelperStartAddr;
	/*�����Ľ�����ַ*/
	uint32_t FlashHelperEndAddr;
	/*��¼��ǰ�����ĵ�ַ*/	
	uint32_t FlashHelperSaveAddr;
} flash_helper_typedef;

FLASH_HELPER_Cx_ flash_helper_typedef flash_helper_struct;


/**
* @brief  flash_helper_init
* @param  sectors_addr  ʹ����һ��������������(������ʼ��ַ)
* @param  None
* @param  None
* @retval 0:�ɹ�
* @example 
* @waing  
**/
int flash_helper_init(uint32_t sectors_addr);

/**
* @brief  ���������������ֵ,���ô˺�������������д��flash
* @param  None
* @param  None
* @param  None
* @retval None
* @example 
* @waing  
**/
int flash_helper_update(void);

/**
* @brief   ��ȡ���������
* @param   index ����һλ���ݿ�ʼ��ȡ(0-)
* @param   data  ���ص�����
* @param   datalen ��ȡ�ĸ���
* @retval  0:�ɹ� 1:û�л��������
* @warning 
* @example 
**/
int flash_helper_get(uint32_t index,uint32_t *data, uint32_t datalen);
	
#endif













