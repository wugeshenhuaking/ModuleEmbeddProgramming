/**
  ******************************************************************************
  * @file    usart.c
  * @author  fengwu yang
  * @version V1.0.0
  * @date    2019/10/12
  * @brief   串口配置函数
  ******************************************************************************			
  ******************************************************************************
  */
#define USART_C_
#include "stdio.h"
#include "usart.h"
#include "BufferManage.h"

#include "LoopList.h"

unsigned char Usart1ReadBuff[Usart1ReadBuffLen]={0};  //接收数据缓存
u32 Usart1ReadCnt = 0;//串口接收到的数据个数

u8  Usart1BufferMemory[Usart1BufferMemoryLen];//接收数据缓存区
u32 Usart1BufferMemoryManage[Usart1BufferMemoryManageLen];//管理缓存区
u8  Usart1BufferMemoryCopy[Usart1BufferMemoryCopyLen];//提取缓存区的数据

u8	Usart1LoopListSendBuff[Usart1LoopListSendBuffLen];//串口环形队列发送缓存


/**
* @brief   串口1初始化
* @param   bound  波特率
* @param   None
* @param   None
* @retval  None
* @warning None
* @example 
**/
void uart_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	/*创建缓存*/
	BufferManageCreate(&buff_manage_struct_usart1,Usart1BufferMemory,Usart1BufferMemoryLen,Usart1BufferMemoryManage,Usart1BufferMemoryManageLen*4);
	/*创建环形队列*/
	rbCreate(&rb_t_usart1_send,Usart1LoopListSendBuff,Usart1LoopListSendBuffLen);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2|RCC_APB1Periph_USART3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_USART1|RCC_APB2Periph_AFIO , ENABLE);	//??USART1,GPIOA??
	
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
  
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10 
	
  
  //USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	
	
  USART_Init(USART1, &USART_InitStructure); //初始化串口1
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//空闲中断
	
	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);//DMA方式接收数据
	
  USART_Cmd(USART1, ENABLE);                    //使能串口1 
}

/**
* @brief   串口DMA初始化
* @param   None
* @param   None
* @retval  None
* @warning None
* @example 
**/
void uart_dma_init(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	          /*开启DMA时钟*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART1->DR);/*外设地址*/
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)Usart1ReadBuff;   /*内存地址*/
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;	          /*方向:外设到内存*/
	DMA_InitStructure.DMA_BufferSize = Usart1ReadBuffLen;         /*缓存区长度*/
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;/*外设地址不增*/	 
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;         /*内存地址自增*/	
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;/*外设数据单位*/	
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;        /*内存数据单位 8bit*/ 
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;     /*DMA模式：一次传输，循环*/	 
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;/*优先级：高*/	  
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;       /*禁止内存到内存的传输	*/
	DMA_Init(DMA1_Channel5, &DMA_InitStructure);       /*配置DMA1的通道*/		    	   
	DMA_Cmd (DMA1_Channel5,ENABLE);					           /*使能DMA*/
}


/**
* @brief  串口发送字符串数据
* @param  *c:发送的数据指针  cnt:数据个数
* @param  None
* @param  None
* @retval None
* @example 
**/
void UsartOutStr(USART_TypeDef* USARTx,unsigned char *c,uint32_t cnt)
{
	while(cnt--)
	{
		USART_SendData(USARTx, *c++);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
	}
}


/**
* @brief  串口发送一个字节
* @param  *c:发送的数据指针  cnt:数据个数
* @param  None
* @param  None
* @retval None
* @example 
**/
void UsartOutChar(USART_TypeDef* USARTx,unsigned char c)
{
	USART_SendData(USARTx,c);
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
}


/**
* @brief  串口中断发送数据
* @param  c:数据的首地址  cnt:发送的数据个数
* @param  None
* @param  None
* @retval None
* @example 
**/
void UsartOutStrIT(USART_TypeDef* USARTx,unsigned char *c,uint32_t cnt)
{
	if(USARTx == USART1)
	{
		PutData(&rb_t_usart1_send,c,cnt);//发送的数据写入环形队列缓存
		USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);//使能发送中断
	}
}


void USART1_IRQHandler(void)//串口1中断服务程序
{
	u8 Res;
	int value;
	if(USART_GetITStatus(USART1,USART_IT_IDLE) == SET)//空闲中断
	{
		USART1->DR; //清除USART_IT_IDLE标志
		
		DMA_Cmd(DMA1_Channel5,DISABLE);//失能
		
		Usart1ReadCnt = Usart1ReadBuffLen - DMA_GetCurrDataCounter(DMA1_Channel5);//获取DMA接收的数据个数
		
	  BufferManageWrite(&buff_manage_struct_usart1,Usart1ReadBuff,Usart1ReadCnt,&value);//把数据存入缓存
		
		DMA_SetCurrDataCounter(DMA1_Channel5,Usart1ReadBuffLen);//重新配置DMA计数
		DMA_Cmd(DMA1_Channel5,ENABLE);//使能
  } 
	
	
	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)//发送中断置位
  {
    if(rbCanRead(&rb_t_usart1_send)>0)//有缓存的数据
    {
			rbRead(&rb_t_usart1_send,&Res,1);//取出一个数据
			USART_SendData(USART1, Res);//发送数据
    }
    else //发送字节结束
    {
      USART_ClearITPendingBit(USART1,USART_IT_TXE);
      USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
      USART_ITConfig(USART1, USART_IT_TC, ENABLE);
    }
  }
	
  if(USART_GetITStatus(USART1, USART_IT_TC) != RESET)//发送完成
  {
    USART_ClearITPendingBit(USART1,USART_IT_TC);
    USART_ITConfig(USART1, USART_IT_TC, DISABLE);
  }
} 

/**
* @brief  使用microLib的方法,使用printf
* @warningg 勾选 microLib
* @param  None
* @param  None
* @param  None
* @retval None
* @example 
**/

int fputc(int ch, FILE *f)
{
	static char flage=0;
	uint8_t data = ch;
	if(!flage)
	{
	  flage=1;
		USART_ClearITPendingBit(USART1,USART_IT_TC);//解决printf丢失第一个字节的问题
	}
	
	PutData(&rb_t_usart1_send,&data,1);//发送的数据写入环形队列缓存
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);//使能串口1发送中断
  return ch;
}

