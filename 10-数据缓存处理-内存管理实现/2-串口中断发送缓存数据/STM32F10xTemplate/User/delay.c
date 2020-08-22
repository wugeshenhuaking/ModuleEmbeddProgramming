#define __DELAY_C_
#include "include.h"


u32 SysTickCntMs = 0;//延时函数使用

/**
* @brief  系统定时器初始化 1Ms中断
* @param   
* @param  None
* @param  None
* @retval None
* @example 
**/
void DelayInit(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	SysTick_Config(SystemCoreClock / 1000);//1Ms
}

/**
* @brief  延时ms
* @param  ms 延时ms
* @param  None
* @param  None
* @retval None
* @example 
**/
void delay_ms(u16 ms)
{
  SysTickCntMs = 0;
	while(SysTickCntMs<ms);
}

/**
* @brief  系统定时器中断
* @param  
* @param  None
* @param  None
* @retval None
* @example 
**/
void SysTick_Handler(void)
{	
	SysTickCntMs ++;
	
	
	if(mem_manage_struct1.SendLen == 0)//没有数据正在发送
	{
		mem_manage_struct1.Cnt++;
		if(mem_manage_struct1.Cnt>=10)//10Ms
		{
			mem_manage_struct1.Cnt = 0;
	
			//查询是不是有数据需要发送
			mem_manage_struct1.DataPtr = MemManageRead(&mem_manage_struct1,&(mem_manage_struct1.SendLen));
			
			if(mem_manage_struct1.SendLen>0)//有数据需要发送
			{
				USART_ITConfig(USART1, USART_IT_TXE, ENABLE);//使能串口发送
			}
			else//没有数据需要发送的时候降低检测时间
			{
				mem_manage_struct1.Cnt=10;
			}
		}
	}
	
	
	if(Usart1ReadCnt!=0)//串口接收到数据
	{
	  Usart1IdleCnt++;//变量累加(该变量在串口接收时清零)
		if(Usart1IdleCnt>=Usart1IdleTime)//串口 Usart1IdleTime Ms 时间没有接收到数据
		{
		  Usart1IdleCnt = 0;
			Usart1ReadCntCopy = Usart1ReadCnt;
			Usart1ReadCnt = 0;
			Usart1ReadFlage = 1;
		}
	}
}


