/**
  ******************************************************************************
  * @file    usart.c
  * @author  fengwu yang
  * @version V1.0.0
  * @date    2019/10/12
  * @brief   �������ú���
  ******************************************************************************
	һ,ʹ��˵��
		��ѭ������ʹ��
			while(1)
			{
				if(Usart1ReadFlage)//���ڽ��յ�һ������
				{
					Usart1ReadFlage=0;
					//��������
					UsartOutStr(Usart1ReadBuff,Usart1ReadCntCopy);//���ؽ��յ�����
				}
			}
				
  ******************************************************************************
  */
#define USART_C_
#include "include.h"


char Usart1ReadBuff[Usart1ReadLen]={0};  //�������ݻ���
u32  Usart1ReadCnt = 0;//����1���յ������ݸ���
u32  Usart1ReadCntCopy = 0;//����1���յ������ݸ���
u32  Usart1IdleCnt = 0;//���м����
u32  Usart1IdleTime = 10;//���ô��ڿ���ʱ��(MS)
u8   Usart1ReadFlage=0;//����1���յ�һ����������
u8   Usart1ClearIdleIT=0;//��������ж�ʹ��
//
char *Usart1SeadData;//�����жϷ��ͽ��շ������ݵĵ�ַ
u32   Usart1SeadDataCnt=0;//�������ݵĸ���

/**
* @brief   ����1��ʼ��
* @param   bound  ������
* @param   None
* @param   None
* @retval  None
* @warning None
* @example 
**/
void uart_init(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
	
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  
	
  
  //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
	
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 
}


/**
* @brief  �����жϷ����ַ�������
* @param  *c:���͵�����ָ��  cnt:���ݸ���
* @param  None
* @param  None
* @retval None
* @example 
**/
void UsartOutStrIT(char *c,uint32_t cnt)
{
	Usart1SeadData=c;//�������ݵĵ�ַ
	Usart1SeadDataCnt=cnt;//����
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);//�򿪴��ڷ����ж�
}


/**
* @brief  ���ڷ����ַ�������
* @param  *c:���͵�����ָ��  cnt:���ݸ���
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
* @brief  ���ڷ���һ���ֽ�
* @param  *c:���͵�����ָ��  cnt:���ݸ���
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


void USART1_IRQHandler(void)//����1�жϷ������
{
	u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		Res =USART_ReceiveData(USART1);	//��ȡ���յ�������
		
		Usart1ReadBuff[Usart1ReadCnt] = Res;	//���յ����ݴ�������
		Usart1ReadCnt++;
		if(Usart1ReadCnt > Usart1ReadLen -10)//��ֹ�������
		{
			Usart1ReadCnt = 0;
		}
		Usart1IdleCnt = 0;//����ʱ�����,���ڽ�����������
	} 
	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)//��Ҫ��������
  {
		if(Usart1SeadDataCnt>0)
		{
			USART_SendData(USART1, *Usart1SeadData);//����
			Usart1SeadData++;
		  Usart1SeadDataCnt--;
    }
    else//�����ֽڽ���
    {
      USART_ClearITPendingBit(USART1,USART_IT_TXE);
      USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
      USART_ITConfig(USART1, USART_IT_TC, ENABLE);
    }
  }
  if (USART_GetITStatus(USART1, USART_IT_TC) != RESET)//�������
  {
    USART_ClearITPendingBit(USART1,USART_IT_TC);
    USART_ITConfig(USART1, USART_IT_TC, DISABLE);
  }
} 

/**
* @brief  ʹ��microLib�ķ���,ʹ��printf
* @warningg ��ѡ microLib
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
		USART_ClearITPendingBit(USART1,USART_IT_TC);//���printf��ʧ��һ���ֽڵ�����
	}
	USART_SendData(USART1, (uint8_t) ch);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
  return ch;
}

