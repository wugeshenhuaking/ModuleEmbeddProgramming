/**
  ******************************************************************************
  * @author  yang feng wu 
  * @version V1.0.0
  * @date    2020/6/11
  * @brief   
  ******************************************************************************
  ******************************************************************************
  */
#include "main.h"
#include "system.h"
#include "usart.h"
#include "timer.h"
#include <stdio.h>

#include "BufferRankOrder.h"

/*BufferRankOrder 需要借助的临时缓存数组*/
#define  MainBufferLen 1024
unsigned char MainBuffer[MainBufferLen];//缓存数据,全局通用

int main(void)
{
	int i=0;
  NVIC_Configuration();
	uart_init(115200);	 //串口初始化为115200
	uart_dma_init();
	Timer2_Config();
	
	printf("start\r\n");
	
	//记录6个0字符
	BufferRankOrderInsert("000000",6,(char *)MainBuffer,MainBufferLen,NULL);
	//记录6个1字符
	BufferRankOrderInsert("111111",6,(char *)MainBuffer,MainBufferLen,NULL);	
	//记录6个2字符
	BufferRankOrderInsert("222222",6,(char *)MainBuffer,MainBufferLen,NULL);	
	//再次记录6个1字符
	BufferRankOrderInsert("111111",6,(char *)MainBuffer,MainBufferLen,NULL);
	
	
	for(i=0;i<BufferRankOrderRowLen;i++)
	{	//这一行存储了数据(数据个数不是0)
		if(BufferRankOrder[i][BufferRankOrderListLen-1] != 0)
		{
			printf("数据个数=%d\r\n",BufferRankOrder[i][BufferRankOrderListLen-1]);
			//打印存储的数据
			UsartOutStrIT(USART1,BufferRankOrder[i],BufferRankOrder[i][BufferRankOrderListLen-1]);
			printf("\r\n");
		}
		else
		{
			break;
		}
	}
	
	while(1)
	{
		
	}
}




















