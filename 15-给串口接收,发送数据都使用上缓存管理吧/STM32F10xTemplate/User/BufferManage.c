/**
  ******************************************************************************
  * @author  yang feng wu 
  * @version V1.0.0
  * @date    2020/1/28
  * @brief   
  ******************************************************************************
	ʹ��˵��:https://www.cnblogs.com/yangfengwu/p/12228402.html
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
* @brief   �������ݻ������
* @param   bms			     �������ṹ�����
* @param   buff          ���ڻ������ݵ�����
* @param   BuffLen       ���ڻ������ݵ�����ĳ���
* @param   ManageBuff    ���ڼ�¼ÿ�λ�������ֽڵ�����
* @param   ManageBuffLen ���ڼ�¼ÿ�λ�������ֽڵ����鳤��
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
* @brief   д�뻺������
* @param   bms			�������ṹ�����
* @param   buff     д�������
* @param   BuffLen  д������ݸ���
* @retval  0 Success
* @warning None
* @example 
**/
int32_t BufferManageWrite(buff_manage_struct *bms,void *buff,uint32_t BuffLen)
{
	if(rbCanWrite(&(bms->Buff))>BuffLen)//����д������
	{
		if(rbCanWrite(&(bms->ManageBuff))>4)//���Լ�¼���ݸ���
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
* @brief   �ӻ����ж�ȡ����
* @param   bms			�������ṹ�����
* @param   buff     ���ص����ݵ�ַ
* @param   None
* @retval  ȡ�������ݸ���
* @warning None
* @example 
**/
int32_t BufferManageRead(buff_manage_struct *bms,void *buff)
{
	if(rbCanRead(&(bms->ManageBuff))>=4)
	{
		rbRead(&(bms->ManageBuff), &(bms->Len) , 4);//��������������ݸ���
		if(bms->Len>0)
		{
			return rbRead(&(bms->Buff),buff, bms->Len);
		}
	}
	return 0;
}


/**
* @brief   ��ջ���
* @param   bms			�������ṹ�����
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







