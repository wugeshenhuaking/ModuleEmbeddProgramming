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
	
	if(Usart1ReadCnt!=0)//串口接收到数据
	{
	  Usart1IdleCnt++;//变量累加(该变量在串口接收时清零)
		if(Usart1IdleCnt>=Usart1IdleTime)//串口 Usart1IdleTime Ms 时间没有接收到数据
		{
		  Usart1IdleCnt = 0;
			Usart1ReadCntCopy = Usart1ReadCnt;
			Usart1ReadCnt = 0;
			Usart1ReadFlage = 1;//置位标志位
		}
	}
}


