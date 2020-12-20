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

/*BufferRankOrder ��Ҫ��������ʱ��������*/
#define  MainBufferLen 1024
unsigned char MainBuffer[MainBufferLen];//��������,ȫ��ͨ��

int main(void)
{
	int i=0;
  NVIC_Configuration();
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	uart_dma_init();
	Timer2_Config();
	
	printf("start\r\n");
	
	//��¼6��0�ַ�
	BufferRankOrderInsert("000000",6,(char *)MainBuffer,MainBufferLen,NULL);
	//��¼6��1�ַ�
	BufferRankOrderInsert("111111",6,(char *)MainBuffer,MainBufferLen,NULL);	
	//��¼6��2�ַ�
	BufferRankOrderInsert("222222",6,(char *)MainBuffer,MainBufferLen,NULL);	
	//�ٴμ�¼6��1�ַ�
	BufferRankOrderInsert("111111",6,(char *)MainBuffer,MainBufferLen,NULL);
	
	
	for(i=0;i<BufferRankOrderRowLen;i++)
	{	//��һ�д洢������(���ݸ�������0)
		if(BufferRankOrder[i][BufferRankOrderListLen-1] != 0)
		{
			printf("���ݸ���=%d\r\n",BufferRankOrder[i][BufferRankOrderListLen-1]);
			//��ӡ�洢������
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




















