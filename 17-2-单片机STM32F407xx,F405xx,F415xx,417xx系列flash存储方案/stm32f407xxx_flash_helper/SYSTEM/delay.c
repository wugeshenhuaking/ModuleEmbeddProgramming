#define __DELAY_C_

#include "delay.h"

u32 SysTickCntMs = 0;//��ʱ����ʹ��

/**
* @brief  ϵͳ��ʱ����ʼ�� 1Ms�ж�
* @param   
* @param  None
* @param  None
* @retval None
* @example 
**/
void delay_init(void)
{
 	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	SysTick_Config(SystemCoreClock / 1000);//1Ms
}
			 


/**
* @brief  ϵͳ��ʱ���ж�
* @param  
* @param  None
* @param  None
* @retval None
* @example 
**/
void SysTick_Handler(void)
{	
	SysTickCntMs ++;
}

/**
* @brief  ��ʱms
* @param  ms ��ʱms
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




