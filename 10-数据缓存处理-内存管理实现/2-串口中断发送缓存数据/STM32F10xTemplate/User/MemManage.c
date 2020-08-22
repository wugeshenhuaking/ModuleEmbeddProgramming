/*******************************************************************************
	Դ��˵��: https://www.cnblogs.com/yangfengwu/p/12238511.html
 *******************************************************************************/

#define MEMMANAGE_C_
#include "MemManage.h"
#include "OS_MEM.h"
#include "string.h"


mem_manage_struct mem_manage_struct1;

/**
* @brief   �������ݻ������
* @param   mms			�������ṹ�����
* @param   buff     ���ڴ洢���ݵĶ�ά����
* @param   nblks    ��������(���������)
* @param   blksize  ÿ�������Ĵ�С(���������)
* @param   err      ���صĴ�����Ϣ
* @retval  None
* @warning None
* @example 
**/
void MemManageCreate(mem_manage_struct *mms, void *buff, INT32U nblks, INT32U blksize, INT8U *err)
{
	unsigned int i;
	OSMemInit();
	
	mms->CommTxBuffer = OSMemCreate(buff,nblks,blksize,err);//������̬�ڴ����
	
	
	mms->BlkReadCount=0;
	mms->BlkWriteCount=0;
	for(i=0;i<BlocksNumber;i++)
	{
	  mms->BlkNumber[i] = 0;
	}
}


/**
* @brief   д�뻺������
* @param   mms			�������ṹ�����
* @param   buff     д�������
* @param   BuffLen  д������ݸ���
* @param   err      ���صĴ�����Ϣ
* @retval  None
* @warning None
* @example 
**/
void MemManageWrite(mem_manage_struct *mms,void *buff,uint32_t BuffLen, INT8U *err)
{
	OS_ENTER_CRITICAL();//��ֹ�жϴ��
	if(mms->BlkNumber[mms->BlkWriteCount]==0)//ѭ�������Ժ�,ȷ����һ��������ȡ������
	{
		mms->BlkAddr[mms->BlkWriteCount] = OSMemGet(mms->CommTxBuffer,err);//����һ���ڴ��
		
		if(*err==0)
		{
			memcpy(mms->BlkAddr[mms->BlkWriteCount],buff,BuffLen*(sizeof(data_type_t)));//�����ݿ������ڴ��
			mms->BlkNumber[mms->BlkWriteCount] = BuffLen;//��¼�洢�����ݸ���
			mms->BlkWriteCount++;//д�����
			
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
	OS_EXIT_CRITICAL();//���ж�
}


/**
* @brief   �ӻ����ж�ȡ����
* @param   bms			�������ṹ�����
* @param   Length   ���ص����ݳ���
* @param   None
* @retval  ���ݵ��׵�ַ
* @warning �����ѭ�����ж϶����ô˺���: �ر��ж�(); ���ô˺���(); ���ж�();
* @example 
**/
data_type_t *MemManageRead(mem_manage_struct *mms,uint32_t *Length)
{
	*Length = mms->BlkNumber[mms->BlkReadCount];
	if(*Length >0)//�洢������
	{
		return mms->BlkAddr[mms->BlkReadCount];
	}
	return NULL;
}

/**
* @brief   ���� MemManageRead �����Ժ���Ҫ���õĺ���
* @param   mms			�������ṹ�����
* @param   None
* @param   None
* @retval  None
* @warning None
* @example 
**/
void MemManageFree(mem_manage_struct *mms)
{
	OS_ENTER_CRITICAL();//��ֹ�жϴ��
	
	mms->BlkNumber[mms->BlkReadCount]=0;
	OSMemPut(mms->CommTxBuffer,mms->BlkAddr[mms->BlkReadCount]);//�ͷ��ڴ��
	mms->BlkReadCount++;
	
	if(mms->BlkReadCount >= BlocksNumber)
	{
		mms->BlkReadCount=0;
	}
	OS_EXIT_CRITICAL();//���ж�
}




