#ifndef FLASH_HELPER_H_
#define FLASH_HELPER_H_

#ifndef FLASH_HELPER_C_//���û�ж���
#define FLASH_HELPER_Cx_ extern
#else
#define FLASH_HELPER_Cx_
#endif

#include "stm32f4xx_conf.h"


#define FlashHelperDebug 0 //0:�ر� 1:��

//���洢������(u32����)����,�����û�ʵ���޸�.
//�������һλ�洢��Ϊ0x55555555;�û�����ʹ�����һλ����
#define FlashHelperDataLen 500

#define FlashHelperUUID 0x55555555 //���һλ�ı�ʶ��

typedef struct flash_helper
{
	/*�洢�û����ݵ�����*/
	u32 FlashHelperData[FlashHelperDataLen];
	/*������Ա�����ֽ���*/
	u32 FlashHelperDataSize;
	/*�����Ŀ�ʼ��ַ*/
	u32 FlashHelperStartAddr;
	/*�����Ľ�����ַ*/
	u32 FlashHelperEndAddr;
	/*��¼��ǰ�����ĵ�ַ*/	
	u32 FlashHelperSaveAddr;
} flash_helper_typedef;

FLASH_HELPER_Cx_ flash_helper_typedef flash_helper_struct;


/**
* @brief  flash_helper_init
* @param  sectors_addr  ʹ����һ��������������
* @param  None
* @param  None
* @retval 0:�ɹ�
* @example 
* @waing  
**/
int flash_helper_init(u32 sectors_addr);

/**
* @brief  ���������������ֵ,���ô˺�������������д��flash
* @param  None
* @param  None
* @param  None
* @retval None
* @example 
* @waing  
**/
void flash_helper_update(void);

/**
* @brief   ��ȡ���������
* @param   index ����һλ���ݿ�ʼ��ȡ(0-)
* @param   data  ���ص�����
* @param   datalen ��ȡ�ĸ���
* @retval  0:�ɹ� 1:û�л��������
* @warning 
* @example 
**/
int flash_helper_get(u32 index,u32 *data, u32 datalen);
	
#endif













