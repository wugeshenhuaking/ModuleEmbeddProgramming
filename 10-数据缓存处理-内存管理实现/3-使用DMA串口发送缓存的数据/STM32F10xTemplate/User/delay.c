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
	
	
	if(mem_manage_struct1.SendLen == 0)//û���������ڷ���
	{
		mem_manage_struct1.Cnt++;
		if(mem_manage_struct1.Cnt>=10)//10Ms
		{
			mem_manage_struct1.Cnt = 0;
	
			//��ѯ�ǲ�����������Ҫ����
			mem_manage_struct1.DataPtr = MemManageRead(&mem_manage_struct1,&(mem_manage_struct1.SendLen));
			
			if(mem_manage_struct1.SendLen>0)//��������Ҫ����
			{
				USART_ITConfig(USART1, USART_IT_TXE, ENABLE);//ʹ�ܴ��ڷ���
			}
			else//û��������Ҫ���͵�ʱ�򽵵ͼ��ʱ��
			{
				mem_manage_struct1.Cnt=10;
			}
		}
	}
	
	
	if(Usart1ReadCnt!=0)//���ڽ��յ�����
	{
	  Usart1IdleCnt++;//�����ۼ�(�ñ����ڴ��ڽ���ʱ����)
		if(Usart1IdleCnt>=Usart1IdleTime)//���� Usart1IdleTime Ms ʱ��û�н��յ�����
		{
		  Usart1IdleCnt = 0;
			Usart1ReadCntCopy = Usart1ReadCnt;
			Usart1ReadCnt = 0;
			Usart1ReadFlage = 1;
		}
	}
}


