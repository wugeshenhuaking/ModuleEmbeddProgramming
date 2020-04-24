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
	
	if(buff_manage_struct1.SendLen == 0)//没有数据正在发送
	{
		buff_manage_struct1.Cnt++;//累加
		if(buff_manage_struct1.Cnt>=10)//10Ms
		{
			buff_manage_struct1.Cnt = 0;
			
			//提取数据到 Usart1SendBuff 数组
			buff_manage_struct1.SendLen = BufferManageRead(&buff_manage_struct1,Usart1SendBuff);
		}
	}
}


