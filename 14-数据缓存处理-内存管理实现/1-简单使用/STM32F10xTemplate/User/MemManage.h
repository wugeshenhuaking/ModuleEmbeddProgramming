#ifndef MEMMANAGE_H_
#define MEMMANAGE_H_

#ifndef MEMMANAGE_C_//���û�ж���
#define MEMMANAGE_Cx_ extern
#else
#define MEMMANAGE_Cx_
#endif

#include <stm32f10x.h>
#include "OS_MEM.h"

#define BlocksNumber  3     //�ڴ�����
#define BlocksSize    500   //ÿ���ڴ�鳤��

#define data_type_t char 

typedef struct{
	signed int  Count;
	signed int  Cnt;
	unsigned char ReadFlage;
	unsigned char SendFlage;

	signed int  ReadLen;
	signed int  SendLen;	//�û�������ʹ�����ϱ���
	
	unsigned int  BlkReadCount;
	unsigned int  BlkWriteCount;
	
	data_type_t  *BlkAddr[BlocksNumber];  //��¼������ڴ���ַ
	unsigned int BlkNumber[BlocksNumber]; //��¼ÿ���ڴ�黺������ݸ���
	
	OS_MEM *CommTxBuffer;
	
}mem_manage_struct;

void MemManageCreate(mem_manage_struct *mms, void *buff, INT32U nblks, INT32U blksize, INT8U *err);
void MemManageWrite(mem_manage_struct *mms,void *buff,uint32_t BuffLen, INT8U *err);
data_type_t *MemManageRead(mem_manage_struct *mms,uint32_t *Length);
void MemManageFree(mem_manage_struct *mms);


//MEMMANAGE_Cx_ data_type_t CommTxPart[BlocksNumber][BlocksSize];
//MEMMANAGE_Cx_ mem_manage_struct mem_manage_struct1;

#endif

