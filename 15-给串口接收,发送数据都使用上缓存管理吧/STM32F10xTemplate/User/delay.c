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
	
	if(buff_manage_struct1.SendLen == 0)//û���������ڷ���
	{
		buff_manage_struct1.Cnt++;//�ۼ�
		if(buff_manage_struct1.Cnt>=10)//10Ms
		{
			buff_manage_struct1.Cnt = 0;
			
			//��ȡ���ݵ� Usart1SendBuff ����
			buff_manage_struct1.SendLen = BufferManageRead(&buff_manage_struct1,Usart1SendBuff);
		}
	}
}


