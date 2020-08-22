/*******************************************************************************
	源码说明: https://www.cnblogs.com/yangfengwu/p/12238511.html
 *******************************************************************************/

#define MEMMANAGE_C_
#include "MemManage.h"
#include "OS_MEM.h"
#include "string.h"


mem_manage_struct mem_manage_struct1;

/**
* @brief   创建数据缓存管理
* @param   mms			缓存管理结构体变量
* @param   buff     用于存储数据的二维数组
* @param   nblks    分区数量(数组的行数)
* @param   blksize  每个分区的大小(数组的列数)
* @param   err      返回的错误信息
* @retval  None
* @warning None
* @example 
**/
void MemManageCreate(mem_manage_struct *mms, void *buff, INT32U nblks, INT32U blksize, INT8U *err)
{
	unsigned int i;
	OSMemInit();
	
	mms->CommTxBuffer = OSMemCreate(buff,nblks,blksize,err);//创建动态内存分区
	
	
	mms->BlkReadCount=0;
	mms->BlkWriteCount=0;
	for(i=0;i<BlocksNumber;i++)
	{
	  mms->BlkNumber[i] = 0;
	}
}


/**
* @brief   写入缓存数据
* @param   mms			缓存管理结构体变量
* @param   buff     写入的数据
* @param   BuffLen  写入的数据个数
* @param   err      返回的错误信息
* @retval  None
* @warning None
* @example 
**/
void MemManageWrite(mem_manage_struct *mms,void *buff,uint32_t BuffLen, INT8U *err)
{
	OS_ENTER_CRITICAL();//禁止中断打断
	if(mms->BlkNumber[mms->BlkWriteCount]==0)//循环过来以后,确定第一条数据提取出来了
	{
		mms->BlkAddr[mms->BlkWriteCount] = OSMemGet(mms->CommTxBuffer,err);//申请一个内存块
		
		if(*err==0)
		{
			memcpy(mms->BlkAddr[mms->BlkWriteCount],buff,BuffLen*(sizeof(data_type_t)));//把数据拷贝到内存块
			mms->BlkNumber[mms->BlkWriteCount] = BuffLen;//记录存储的数据个数
			mms->BlkWriteCount++;//写入计数
			
			if(mms->BlkWriteCount>=BlocksNumber)
			{
				mms->BlkWriteCount=0;
			}
		}
	}
	else
	{
		*err = OS_MEM_NO_FREE_BLKS;
	}
	OS_EXIT_CRITICAL();//打开中断
}


/**
* @brief   从缓存中读取数据
* @param   bms			缓存管理结构体变量
* @param   Length   返回的数据长度
* @param   None
* @retval  数据的首地址
* @warning 如果主循环和中断都调用此函数: 关闭中断(); 调用此函数(); 打开中断();
* @example 
**/
data_type_t *MemManageRead(mem_manage_struct *mms,uint32_t *Length)
{
	*Length = mms->BlkNumber[mms->BlkReadCount];
	if(*Length >0)//存储了数据
	{
		return mms->BlkAddr[mms->BlkReadCount];
	}
	return NULL;
}

/**
* @brief   调用 MemManageRead 结束以后需要调用的函数
* @param   mms			缓存管理结构体变量
* @param   None
* @param   None
* @retval  None
* @warning None
* @example 
**/
void MemManageFree(mem_manage_struct *mms)
{
	OS_ENTER_CRITICAL();//禁止中断打断
	
	mms->BlkNumber[mms->BlkReadCount]=0;
	OSMemPut(mms->CommTxBuffer,mms->BlkAddr[mms->BlkReadCount]);//释放内存块
	mms->BlkReadCount++;
	
	if(mms->BlkReadCount >= BlocksNumber)
	{
		mms->BlkReadCount=0;
	}
	OS_EXIT_CRITICAL();//打开中断
}




