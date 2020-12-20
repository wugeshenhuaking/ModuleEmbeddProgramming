/**
  ******************************************************************************
  * @author  yang feng wu 
  * @version V1.0.0
  * @date    2020/12/20
  * @brief   ʹ�� Buffer ��¼����, ������洢��ʱ��������������,�Ͱ�����������ᵽ 
	Buffer �ĵ�һ��λ��; ���û��������ݾͰ�������ݲ嵽 Buffer �ĵ�һ��λ��.
  ******************************************************************************
  ******************************************************************************
  */
#define BufferRankOrder_c_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "BufferRankOrder.h"

/*�������ݵ�����*/
char BufferRankOrder[BufferRankOrderRowLen][BufferRankOrderListLen];


/**
* @brief   ���ݴ洢������
* @param   data			     �洢������
* @param   datalen       ���ݳ���
* @param   HoldBuff      ��ʱ���������
* @param   HoldBuffLen   ��ʱ��������鳤��
* @param   error         �������
* @retval  0:success   others:error code
* @warning None
* @example 
**/
char BufferRankOrderInsert(char *data,int datalen,char *HoldBuff,int HoldBuffLen,char *error)
{
	char err = 0;
	int i=0,j=0,flag=0;
	memset(HoldBuff,0,HoldBuffLen);
	if(data != NULL && datalen < BufferRankOrderListLen)
	{	//��ʱ���黺���㹻
		if(HoldBuffLen >= BufferRankOrderRowLen*BufferRankOrderListLen){
			for(i=0;i<BufferRankOrderRowLen;i++){	
				if(memcmp(BufferRankOrder[i],data,datalen) == 0 && BufferRankOrder[i][BufferRankOrderListLen-1] == datalen)
				{	//Ҫ�洢�������Ѿ��洢���˻�������
					flag = 1;
					break;
				}
			}
		}
		else
		{
			if(error!=NULL) *error = 2;
			err = 2;
		}
		if(flag == 1){//Ҫ�洢�������Ѿ��洢���˻�������
			if(i!=0)//���Ǽ�¼�ڵ�һ��
			{	//�����¼
				memset(BufferRankOrder[i],0,BufferRankOrderListLen);
				for(i=0;i<BufferRankOrderRowLen;i++)
				{	//�����е����ݿ�������ʱ����(ֻ���������ݵ�)
					if(BufferRankOrder[i][0] != 0)
					{
						memcpy(HoldBuff+j,BufferRankOrder[i],BufferRankOrderListLen);
						j = j + BufferRankOrderListLen;
					}
					memset(BufferRankOrder[i],0,BufferRankOrderListLen);
				}
				memcpy(BufferRankOrder[0],data,datalen);//�����ݿ�������һ��λ��
				BufferRankOrder[0][BufferRankOrderListLen-1] = datalen;//���һλ��¼���ݵĳ���
				memcpy(BufferRankOrder[1],HoldBuff,j);//�Ѻ�������ݿ�����ȥ
			}
		}
		else //û�м�¼
		{	//�������ݵ���ʱ����
			memcpy(HoldBuff,BufferRankOrder[0],BufferRankOrderRowLen*BufferRankOrderListLen);
			memset(BufferRankOrder[0],0,BufferRankOrderRowLen*BufferRankOrderListLen);//���
			
			memcpy(BufferRankOrder[0],data,datalen);//�����ݿ�������һ��λ��
			BufferRankOrder[0][BufferRankOrderListLen-1] = datalen;//���һλ��¼���ݵĳ���
			memcpy(BufferRankOrder[1],HoldBuff,BufferRankOrderRowLen*(BufferRankOrderListLen-1));//�Ѻ�������ݿ�����ȥ
		}
	}
	else
	{
		if(error!=NULL) *error = 1;
		err = 1;
	}
	return err;
}



