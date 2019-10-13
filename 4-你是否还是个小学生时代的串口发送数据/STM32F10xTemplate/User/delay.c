#define __DELAY_C_
#include "include.h"
u32 SysTickCntMs = 0;//��ʱ����ʹ��

/**
* @brief  ϵͳ��ʱ����ʼ�� 1Ms�ж�
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
	
	if(Usart1ReadCnt!=0)//���ڽ��յ�����
	{
	  Usart1IdleCnt++;//�����ۼ�(�ñ����ڴ��ڽ���ʱ����)
		if(Usart1IdleCnt>=Usart1IdleTime)//���� Usart1IdleTime Ms ʱ��û�н��յ�����
		{
		  Usart1IdleCnt = 0;
			Usart1ReadCntCopy = Usart1ReadCnt;
			Usart1ReadCnt = 0;
			Usart1ReadFlage = 1;//��λ��־λ
		}
	}
}


