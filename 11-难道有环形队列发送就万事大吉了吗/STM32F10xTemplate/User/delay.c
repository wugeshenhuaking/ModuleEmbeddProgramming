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
	
	if(Usart1ManageSendDatLen == 0)//û���ڷ�������
	{
		Usart1ManageSendDelayCnt++;
		if(Usart1ManageSendDelayCnt>=1000)//�ӳ�10Ms
		{
			Usart1ManageSendDelayCnt = 0;
			if(rbCanRead(&Uart1rbManage)>0)//�ǲ�������Ҫ���͵�����
			{
				//ȡ�����Ҫ���͵����ݸ���
				rbRead(&Uart1rbManage, &Usart1ManageSendDatLen, 1);
				USART_ITConfig(USART1, USART_IT_TXE, ENABLE);//�򿪷����ж�
			}
			else
			{
				//û�����ݷ��͵�ʱ��1Ms�ж�һ��,�ӳ�1Ms
			  Usart1ManageSendDelayCnt=10;
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


