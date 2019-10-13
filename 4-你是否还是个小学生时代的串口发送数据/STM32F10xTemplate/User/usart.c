/**
  ******************************************************************************
  * @file    usart.c
  * @author  fengwu yang
  * @version V1.0.0
  * @date    2019/10/12
  * @brief   串口配置函数
  ******************************************************************************
	一,使用说明
		主循环调用使用
			while(1)
			{
				if(Usart1ReadFlage)//串口接收到一条数据
				{
					Usart1ReadFlage=0;
					//处理数据
					UsartOutStr(Usart1ReadBuff,Usart1ReadCntCopy);//返回接收的数据
				}
			}
				
  ******************************************************************************
  */
#define USART_C_
#include "include.h"


char Usart1ReadBuff[Usart1ReadLen]={0};  //接收数据缓存
u32  Usart1ReadCnt = 0;//串口1接收到的数据个数
u32  Usart1ReadCntCopy = 0;//串口1接收到的数据个数
u32  Usart1IdleCnt = 0;//空闲检测用
u32  Usart1IdleTime = 10;//设置串口空闲时间(MS)
u8   Usart1ReadFlage=0;//串口1接收到一条完整数据
u8   Usart1ClearIdleIT=0;//清除空闲中断使用
//
char *Usart1SeadData;//串口中断发送接收发送数据的地址
u32   Usart1SeadDataCnt=0;//发送数据的个数

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
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
	
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
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
	
  USART_Cmd(USART1, ENABLE);                    //使能串口1 
}


/**
* @brief  串口中断发送字符串数据
* @param  *c:发送的数据指针  cnt:数据个数
* @param  None
* @param  None
* @retval None
* @example 
**/
void UsartOutStrIT(char *c,uint32_t cnt)
{
	Usart1SeadData=c;//发送数据的地址
	Usart1SeadDataCnt=cnt;//个数
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);//打开串口发送中断
}


/**
* @brief  串口发送字符串数据
* @param  *c:发送的数据指针  cnt:数据个数
* @param  None
* @param  None
* @retval None
* @example 
**/
void UsartOutStr(unsigned char *c,uint32_t cnt)
{
	while(cnt--)
	{
		USART_SendData(USART1, *c++);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );
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
void UsartOutChar(unsigned char c)
{
	USART_SendData(USART1,c);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );
}


void USART1_IRQHandler(void)//串口1中断服务程序
{
	u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		Res =USART_ReceiveData(USART1);	//读取接收到的数据
		
		Usart1ReadBuff[Usart1ReadCnt] = Res;	//接收的数据存入数组
		Usart1ReadCnt++;
		if(Usart1ReadCnt > Usart1ReadLen -10)//防止数组溢出
		{
			Usart1ReadCnt = 0;
		}
		Usart1IdleCnt = 0;//空闲时间变量,串口接收数据清零
	} 
	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)//需要发送数据
  {
		if(Usart1SeadDataCnt>0)
		{
			USART_SendData(USART1, *Usart1SeadData);//发送
			Usart1SeadData++;
		  Usart1SeadDataCnt--;
    }
    else//发送字节结束
    {
      USART_ClearITPendingBit(USART1,USART_IT_TXE);
      USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
      USART_ITConfig(USART1, USART_IT_TC, ENABLE);
    }
  }
  if (USART_GetITStatus(USART1, USART_IT_TC) != RESET)//发送完成
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
	if(!flage)
	{
	  flage=1;
		USART_ClearITPendingBit(USART1,USART_IT_TC);//解决printf丢失第一个字节的问题
	}
	USART_SendData(USART1, (uint8_t) ch);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
  return ch;
}

