#ifndef FLASH_HELPER_H_
#define FLASH_HELPER_H_

#ifndef FLASH_HELPER_C_//���û�ж���
#define FLASH_HELPER_Cx_ extern
#else
#define FLASH_HELPER_Cx_
#endif
#include "stm32f10x.h"
#include "stmflash.h"


/*Ĭ�ϲ�д����*/
/*FlashHelperMaxLen/FlashHelperDataLen*4*Flash��д����*/
/*510/20*4*10000 = 100���*/
/*1022/20*4*10000 = 204���*/

//#define FlashHelperDebug  

#if STM32_FLASH_SIZE<256  //Flash����
#define FlashHelperMaxLen 510
#else 
#define FlashHelperMaxLen 1022
#endif	

#define FlashHelperDataLen 20 //���洢�����ݸ���(u16),�����û�ʵ���޸�.


#define FlashHelperPageNumber  4   //�������(�޸Ĵ˲���,��Ҫ�޸����ӵײ����)
#define FlashHelperAddressOffset 4 //�洢��ַƫ���ֽ���(�����޸�)

typedef struct flash_helper
{
	/*�洢�û�����,�û������ݴ洢�ڴ�����*/
	u16 FlashHelperData[FlashHelperDataLen];
	u16 FlashHelperTail;
	/*���������õķ����׵�ַ*/
	u32 FlashHelperPageAddr[FlashHelperPageNumber];
	/*��¼��ǰ�����ĵ�ַ*/	
	u32 FlashHelperFlashAddr;
	u32 FlashHelperFlashAddrCopy;
	
} flash_helper_typedef;

FLASH_HELPER_Cx_ flash_helper_typedef flash_helper_struct;


void FlashHelperUpdate(void);
void FlashHelperInit(u32 ADDR1,u32 ADDR2,u32 ADDR3,u32 ADDR4);
u16 FlashHelperGetIndex(u16 index);
#endif



