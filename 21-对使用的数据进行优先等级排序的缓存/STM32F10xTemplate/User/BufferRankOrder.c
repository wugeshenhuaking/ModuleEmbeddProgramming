/**
  ******************************************************************************
  * @author  yang feng wu 
  * @version V1.0.0
  * @date    2020/12/20
  * @brief   使用 Buffer 记录数据, 往里面存储的时候如果有这个数据,就把里面的数据提到 
	Buffer 的第一个位置; 如果没有这个数据就把这个数据插到 Buffer 的第一个位置.
  ******************************************************************************
  ******************************************************************************
  */
#define BufferRankOrder_c_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "BufferRankOrder.h"

/*缓存数据的数组*/
char BufferRankOrder[BufferRankOrderRowLen][BufferRankOrderListLen];


/**
* @brief   数据存储到缓存
* @param   data			     存储的数据
* @param   datalen       数据长度
* @param   HoldBuff      临时缓存的数组
* @param   HoldBuffLen   临时缓存的数组长度
* @param   error         错误变量
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
	{	//临时数组缓存足够
		if(HoldBuffLen >= BufferRankOrderRowLen*BufferRankOrderListLen){
			for(i=0;i<BufferRankOrderRowLen;i++){	
				if(memcmp(BufferRankOrder[i],data,datalen) == 0 && BufferRankOrder[i][BufferRankOrderListLen-1] == datalen)
				{	//要存储的数据已经存储在了缓存里面
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
		if(flag == 1){//要存储的数据已经存储在了缓存里面
			if(i!=0)//不是记录在第一个
			{	//清除记录
				memset(BufferRankOrder[i],0,BufferRankOrderListLen);
				for(i=0;i<BufferRankOrderRowLen;i++)
				{	//把所有的数据拷贝到临时数组(只拷贝有数据的)
					if(BufferRankOrder[i][0] != 0)
					{
						memcpy(HoldBuff+j,BufferRankOrder[i],BufferRankOrderListLen);
						j = j + BufferRankOrderListLen;
					}
					memset(BufferRankOrder[i],0,BufferRankOrderListLen);
				}
				memcpy(BufferRankOrder[0],data,datalen);//把数据拷贝到第一个位置
				BufferRankOrder[0][BufferRankOrderListLen-1] = datalen;//最后一位记录数据的长度
				memcpy(BufferRankOrder[1],HoldBuff,j);//把后面的数据拷贝进去
			}
		}
		else //没有记录
		{	//拷贝数据到临时数组
			memcpy(HoldBuff,BufferRankOrder[0],BufferRankOrderRowLen*BufferRankOrderListLen);
			memset(BufferRankOrder[0],0,BufferRankOrderRowLen*BufferRankOrderListLen);//清空
			
			memcpy(BufferRankOrder[0],data,datalen);//把数据拷贝到第一个位置
			BufferRankOrder[0][BufferRankOrderListLen-1] = datalen;//最后一位记录数据的长度
			memcpy(BufferRankOrder[1],HoldBuff,BufferRankOrderRowLen*(BufferRankOrderListLen-1));//把后面的数据拷贝进去
		}
	}
	else
	{
		if(error!=NULL) *error = 1;
		err = 1;
	}
	return err;
}



