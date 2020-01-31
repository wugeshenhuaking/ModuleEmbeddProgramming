#ifndef MEMMANAGE_H_
#define MEMMANAGE_H_

#ifndef MEMMANAGE_C_//如果没有定义
#define MEMMANAGE_Cx_ extern
#else
#define MEMMANAGE_Cx_
#endif

#include <stm32f10x.h>
#include "OS_MEM.h"

#define BlocksNumber  3     //内存块个数
#define BlocksSize    500   //每个内存块长度

#define data_type_t char 

typedef struct{
	signed int  Count;
	signed int  Cnt;
	unsigned char ReadFlage;
	unsigned char SendFlage;

	signed int  ReadLen;
	signed int  SendLen;	//用户可自由使用以上变量
	
	unsigned int  BlkReadCount;
	unsigned int  BlkWriteCount;
	
	data_type_t  *BlkAddr[BlocksNumber];  //记录申请的内存块地址
	unsigned int BlkNumber[BlocksNumber]; //记录每个内存块缓存的数据个数
	
	OS_MEM *CommTxBuffer;
	
}mem_manage_struct;

void MemManageCreate(mem_manage_struct *mms, void *buff, INT32U nblks, INT32U blksize, INT8U *err);
void MemManageWrite(mem_manage_struct *mms,void *buff,uint32_t BuffLen, INT8U *err);
data_type_t *MemManageRead(mem_manage_struct *mms,uint32_t *Length);
void MemManageFree(mem_manage_struct *mms);


//MEMMANAGE_Cx_ data_type_t CommTxPart[BlocksNumber][BlocksSize];
//MEMMANAGE_Cx_ mem_manage_struct mem_manage_struct1;

#endif

