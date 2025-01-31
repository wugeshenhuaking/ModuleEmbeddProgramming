/**
  ******************************************************************************
  * @file    usart.c
  * @author  fengwu yang
  * @version V1.0.0
  * @date    2019/10/12
  * @brief   串口配置函数
				
  ******************************************************************************
  */
#define USART_C_
#include <stdio.h>
#include "usart.h"
#include "BufferManage.h"


/****************************串口1****************************/
unsigned char Usart1ReadBuff[Usart1ReadBuffLen]={0};  //接收数据缓存
u32  Usart1ReadCnt = 0;//串口接收到的数据个数

u8   Usart1BufferMemory[Usart1BufferMemoryLen];//接收数据缓存区
u8   Usart1BufferMemoryRead[Usart1BufferMemoryReadLen];//提取缓存区的数据
u32  Usart1BufferMemoryManage[Usart1BufferMemoryManageLen];//管理缓存区

unsigned char Usart1SendBuff[Usart1SendBufflen];  //串口发送数据缓存
u8 Usart1SendBits=0;//串口提取环形队列1个字节

unsigned char *Usart1SendData;//串口中断发送数据的地址
u32   Usart1SendDataCnt=0;//串口中断发送数据的个数


/****************************串口2****************************/
unsigned char Usart2ReadBuff[Usart2ReadBuffLen]={0};  //接收数据缓存
u32  Usart2ReadCnt = 0;//串口接收到的数据个数

u8   Usart2BufferMemory[Usart2BufferMemoryLen];//接收数据缓存区
u8   Usart2BufferMemoryCopy[Usart2BufferMemoryCopyLen];//提取缓存区的数据
u32  Usart2BufferMemoryManage[Usart2BufferMemoryManageLen];//管理缓存区

unsigned char *Usart2SendData;//串口中断发送数据的地址
u32   Usart2SendDataCnt=0;//串口中断发送数据的个数



/**
* @brief   串口1初始化
* @param   bound  波特率
* @param   None
* @param   None
* @retval  None
* @warning None
* @example 
**/
void uart_init(u32 bound1,u32 bound2){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	 
	
	rbCreate(&rb_t_usart1,Usart1SendBuff,Usart1SendBufflen);//创建环形队列(用于发送数据)
	BufferManageCreate(&buff_manage_struct_usart1,Usart1BufferMemory,Usart1BufferMemoryLen,Usart1BufferMemoryManage,Usart1BufferMemoryManageLen*4);/*串口接收缓存*/
	
	BufferManageCreate(&buff_manage_struct_usart2,Usart2BufferMemory,Usart2BufferMemoryLen,Usart2BufferMemoryManage,Usart2BufferMemoryManageLen*4);/*串口接收缓存*/
	
	
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
	
	
	
	//USART2_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  //USART2_RX	  GPIOA.3
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
	
  //USART 初始化设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	
	
	USART_InitStructure.USART_BaudRate = bound1;//串口波特率
  USART_Init(USART1, &USART_InitStructure); //初始化串口1
	
	USART_InitStructure.USART_BaudRate = bound2;//串口波特率
	USART_Init(USART2, &USART_InitStructure); //初始化串口2
	
	
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
	
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//空闲中断
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);//空闲中断
	
  USART_Cmd(USART1, ENABLE);                    //使能串口
	USART_Cmd(USART2, ENABLE);                    //使能串口
}


/**
* @brief  串口中断发送数据
* @param  c:数据的首地址  cnt:发送的数据个数
* @param  None
* @param  None
* @retval None
* @example 
**/
void UsartOutStrIT(USART_TypeDef* USARTx, unsigned char *c, uint32_t cnt)
{
	if(USARTx == USART1){
		PutData(&rb_t_usart1,c,cnt);
		USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);
	}
	else if(USARTx == USART2){
		Usart2SendData=c;
		Usart2SendDataCnt=cnt;
		USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);
	}
}


/**
* @brief  串口发送字符串数据
* @param  *c:发送的数据指针  cnt:数据个数
* @param  None
* @param  None
* @retval None
* @example 
**/
void UsartOutStr(USART_TypeDef* USARTx, unsigned char *c,uint32_t cnt)
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
void UsartOutChar(USART_TypeDef* USARTx, unsigned char c)
{
	USART_SendData(USARTx,c);
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
}



void USART1_IRQHandler(void)//串口1中断服务程序
{
	u8 Res;
	int value;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		Res =USART_ReceiveData(USART1);	//读取接收到的数据
		
		Usart1ReadBuff[Usart1ReadCnt] = Res;	//接收的数据存入数组
		Usart1ReadCnt++;
		if(Usart1ReadCnt > Usart1ReadBuffLen -10)//防止数组溢出
		{
			Usart1ReadCnt = 0;
		}
	} 
	else if(USART_GetITStatus(USART1,USART_IT_IDLE) == SET)//空闲中断
	{
		USART1->DR; //清除USART_IT_IDLE标志
		//把数据存入缓存
	  BufferManageWrite(&buff_manage_struct_usart1,Usart1ReadBuff,Usart1ReadCnt,&value);
		Usart1ReadCnt=0;
  }  
	
	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
  {
    if(rbCanRead(&rb_t_usart1)>0)//如果里面的数据个数大于0
    {
			rbRead(&rb_t_usart1,&Usart1SendBits,1);
			USART_SendData(USART1, Usart1SendBits);
    }
    else
    {
      //发送字节结束			
      USART_ClearITPendingBit(USART1,USART_IT_TXE);
      USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
      USART_ITConfig(USART1, USART_IT_TC, ENABLE);
    }
  }
	//发送完成
  if (USART_GetITStatus(USART1, USART_IT_TC) != RESET)
  {
    USART_ClearITPendingBit(USART1,USART_IT_TC);
    USART_ITConfig(USART1, USART_IT_TC, DISABLE);
  }
} 





void USART2_IRQHandler(void)//串口2中断服务程序
{
	u8 Res;
	int value;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		Res =USART_ReceiveData(USART2);	//读取接收到的数据
		
		Usart2ReadBuff[Usart2ReadCnt] = Res;	//接收的数据存入数组
		Usart2ReadCnt++;
		if(Usart2ReadCnt > Usart2ReadBuffLen -10)//防止数组溢出
		{
			Usart2ReadCnt = 0;
		}
	} 
	else if(USART_GetITStatus(USART2,USART_IT_IDLE) == SET)//空闲中断
	{
		USART2->DR; //清除USART_IT_IDLE标志
		//把数据存入缓存
	  BufferManageWrite(&buff_manage_struct_usart2,Usart2ReadBuff,Usart2ReadCnt,&value);		
		Usart2ReadCnt=0;
  }  
	
	if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
  {
    if(Usart2SendDataCnt>0)//如果里面的数据个数大于0
    {
			USART_SendData(USART2, *Usart2SendData);
			Usart2SendData++;
		  Usart2SendDataCnt--;
    }
    else
    {
      USART_ClearITPendingBit(USART2,USART_IT_TXE);
      USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
      USART_ITConfig(USART2, USART_IT_TC, ENABLE);
    }
  }
	//发送完成
  if (USART_GetITStatus(USART2, USART_IT_TC) != RESET)
  {
    USART_ClearITPendingBit(USART2,USART_IT_TC);
    USART_ITConfig(USART2, USART_IT_TC, DISABLE);
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
	PutData(&rb_t_usart1,&data,1);
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
  return ch;
}

