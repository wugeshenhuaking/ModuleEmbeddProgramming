
/**
  ******************************************************************************
  * @file    key.c
  * @author  yang feng wu 
  * @version V1.0.0
  * @date    2019/10/13
  * @brief   �ַ���������
  ******************************************************************************
  ******************************************************************************
  */


#define _TIME_C_

#include "timer.h"
#include "usart.h"
#include "ConfigModuleNoBlock.h"

int timer2Value = 0;

/**
* @brief  ��ʱ��2����
* @param  None
* @param  None
* @param  None
* @retval None
* @example 
**/
void timer2_init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;	
	//��ʱ��2
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_InitStructure);
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	/* Resets the TIM2 */
  TIM_DeInit(TIM2);
	//������ʱ�ӷָ
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	// ѡ���˼�����ģʽ��
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	//��ֵ
	TIM_TimeBaseStructure.TIM_Period = 10;//��ʱʱ��1ms��һ��
	//������������Ϊ TIMx ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ��72M / 7199+1 = 0.01M
	TIM_TimeBaseStructure.TIM_Prescaler = 7199;
	
	//TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	/* Enables the TIM2 counter */
  TIM_Cmd(TIM2, ENABLE);
	
	/* Enables the TIM2 Capture Compare channel 1 Interrupt source */
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE );
}

/**
* @brief  ��ʱ��2�жϺ���
* @param  None
* @param  None
* @param  None
* @retval None
* @example 
**/
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		
		ConfigModuleNoBlockCnt++;
		timer2Value++;
		
		Usart2IdleLoop(10);
	}
}



















