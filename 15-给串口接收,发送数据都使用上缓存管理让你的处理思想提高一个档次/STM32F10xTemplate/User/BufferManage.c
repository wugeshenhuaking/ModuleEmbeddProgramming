/**
  ******************************************************************************
  * @author  yang feng wu 
  * @version V1.0.0
  * @date    2020/1/28
  * @brief   
  ******************************************************************************
	使用说明:https://www.cnblogs.com/yangfengwu/p/12228402.html
  ******************************************************************************
  */

#define BUFFMANAGE_C_
#include "BufferManage.h"
#include "LoopList.h"
#include <stdio.h>

//#include "include.h"


buff_manage_struct buff_manage_struct1;
buff_manage_struct buff_manage_struct2;

/**
* @brief   创建数据缓存管理
* @param   bms			     缓存管理结构体变量
* @param   buff          用于缓存数据的数组
* @param   BuffLen       用于缓存数据的数组的长度
* @param   ManageBuff    用于记录每次缓存多少字节的数组
* @param   ManageBuffLen 用于记录每次缓存多少字节的数组长度
* @retval  None
* @warning None
* @example 
**/
int32_t BufferManageCreate(buff_manage_struct *bms,void *buff,uint32_t BuffLen,void *ManageBuff,uint32_t ManageBuffLen)
{
	rbCreate(&(bms->Buff),buff,BuffLen);
	rbCreate(&(bms->ManageBuff),ManageBuff,ManageBuffLen);
	
	bms->Count=0;
	bms->Cnt=0;
	bms->ReadFlage=0;
	bms->ReadLen=0;
	bms->SendFlage=0;
	bms->SendLen=0;
	return 0;
}


/**
* @brief   写入缓存数据
* @param   bms			缓存管理结构体变量
* @param   buff     写入的数据
* @param   BuffLen  写入的数据个数
* @retval  0 Success
* @warning None
* @example 
**/
int32_t BufferManageWrite(buff_manage_struct *bms,void *buff,uint32_t BuffLen)
{
	if(rbCanWrite(&(bms->Buff))>BuffLen)//可以写入数据
	{
		if(rbCanWrite(&(bms->ManageBuff))>4)//可以记录数据个数
		{			
			PutData(&(bms->Buff) ,buff, BuffLen);
			PutData(&(bms->ManageBuff) ,&BuffLen, 4);
			return 0;
		}
		else  return -2;
	}
	else return -3;
}


/**
* @brief   从缓存中读取数据
* @param   bms			缓存管理结构体变量
* @param   buff     返回的数据地址
* @param   None
* @retval  取出的数据个数
* @warning None
* @example 
**/
int32_t BufferManageRead(buff_manage_struct *bms,void *buff)
{
	if(rbCanRead(&(bms->ManageBuff))>=4)
	{
		rbRead(&(bms->ManageBuff), &(bms->Len) , 4);//读出来存入的数据个数
		if(bms->Len>0)
		{
			return rbRead(&(bms->Buff),buff, bms->Len);
		}
	}
	return 0;
}


/**
* @brief   清空缓存
* @param   bms			缓存管理结构体变量
* @param   None
* @param   None
* @retval  None
* @warning None
* @example 
**/
void BufferManageClear(buff_manage_struct *bms)
{
	__disable_irq();
	
	bms->Buff.rbHead = bms->Buff.rbBuff;
	bms->Buff.rbTail = bms->Buff.rbBuff;
	
	bms->ManageBuff.rbHead = bms->ManageBuff.rbBuff;
	bms->ManageBuff.rbTail = bms->ManageBuff.rbBuff;
	
	bms->Count=0;
	bms->Cnt=0;
	bms->ReadFlage=0;
	bms->ReadLen=0;
	bms->SendFlage=0;
	bms->SendLen=0;
	
	__enable_irq();
}







