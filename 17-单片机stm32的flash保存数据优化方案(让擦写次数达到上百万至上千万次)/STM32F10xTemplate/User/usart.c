/**
  ******************************************************************************
  * @file    usart.c
  * @author  fengwu yang
  * @version V1.0.0
  * @date    2019/10/12
  * @brief   �������ú���
				
  ******************************************************************************
  */
#define USART_C_
#include <stdio.h>
#include "usart.h"
#include "BufferManage.h"


/****************************����1****************************/
unsigned char Usart1ReadBuff[Usart1ReadBuffLen]={0};  //�������ݻ���
u32  Usart1ReadCnt = 0;//���ڽ��յ������ݸ���

u8   Usart1BufferMemory[Usart1BufferMemoryLen];//�������ݻ�����
u8   Usart1BufferMemoryRead[Usart1BufferMemoryReadLen];//��ȡ������������
u32  Usart1BufferMemoryManage[Usart1BufferMemoryManageLen];//��������

unsigned char Usart1SendBuff[Usart1SendBufflen];  //���ڷ������ݻ���
u8 Usart1SendBits=0;//������ȡ���ζ���1���ֽ�

unsigned char *Usart1SendData;//�����жϷ������ݵĵ�ַ
u32   Usart1SendDataCnt=0;//�����жϷ������ݵĸ���


/****************************����2****************************/
unsigned char Usart2ReadBuff[Usart2ReadBuffLen]={0};  //�������ݻ���
u32  Usart2ReadCnt = 0;//���ڽ��յ������ݸ���

u8   Usart2BufferMemory[Usart2BufferMemoryLen];//�������ݻ�����
u8   Usart2BufferMemoryCopy[Usart2BufferMemoryCopyLen];//��ȡ������������
u32  Usart2BufferMemoryManage[Usart2BufferMemoryManageLen];//��������

unsigned char *Usart2SendData;//�����жϷ������ݵĵ�ַ
u32   Usart2SendDataCnt=0;//�����жϷ������ݵĸ���



/**
* @brief   ����1��ʼ��
* @param   bound  ������
* @param   None
* @param   None
* @retval  None
* @warning None
* @example 
**/
void uart_init(u32 bound1,u32 bound2){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	 
	
	rbCreate(&rb_t_usart1,Usart1SendBuff,Usart1SendBufflen);//�������ζ���(���ڷ�������)
	BufferManageCreate(&buff_manage_struct_usart1,Usart1BufferMemory,Usart1BufferMemoryLen,Usart1BufferMemoryManage,Usart1BufferMemoryManageLen*4);/*���ڽ��ջ���*/
	
	BufferManageCreate(&buff_manage_struct_usart2,Usart2BufferMemory,Usart2BufferMemoryLen,Usart2BufferMemoryManage,Usart2BufferMemoryManageLen*4);/*���ڽ��ջ���*/
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2|RCC_APB1Periph_USART3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_USART1|RCC_APB2Periph_AFIO , ENABLE);	//??USART1,GPIOA??
	
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
  
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10 
	
	
	
	//USART2_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  //USART2_RX	  GPIOA.3
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
	
  //USART ��ʼ������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	
	
	USART_InitStructure.USART_BaudRate = bound1;//���ڲ�����
  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	
	USART_InitStructure.USART_BaudRate = bound2;//���ڲ�����
	USART_Init(USART2, &USART_InitStructure); //��ʼ������2
	
	
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
	
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//�����ж�
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);//�����ж�
	
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���
	USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���
}


/**
* @brief  �����жϷ�������
* @param  c:���ݵ��׵�ַ  cnt:���͵����ݸ���
* @param  None
* @param  None
* @retval None
* @example 
**/
void UsartOutStrIT(USART_TypeDef* USARTx, unsigned char *c, uint32_t cnt)
{
	if(USARTx == USART1){
		PutData(&rb_t_usart1,c,cnt);
		USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);
	}
	else if(USARTx == USART2){
		Usart2SendData=c;
		Usart2SendDataCnt=cnt;
		USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);
	}
}


/**
* @brief  ���ڷ����ַ�������
* @param  *c:���͵�����ָ��  cnt:���ݸ���
* @param  None
* @param  None
* @retval None
* @example 
**/
void UsartOutStr(USART_TypeDef* USARTx, unsigned char *c,uint32_t cnt)
{
	while(cnt--)
	{
		USART_SendData(USARTx, *c++);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
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
void UsartOutChar(USART_TypeDef* USARTx, unsigned char c)
{
	USART_SendData(USARTx,c);
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
}



void USART1_IRQHandler(void)//����1�жϷ������
{
	u8 Res;
	int value;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		Res =USART_ReceiveData(USART1);	//��ȡ���յ�������
		
		Usart1ReadBuff[Usart1ReadCnt] = Res;	//���յ����ݴ�������
		Usart1ReadCnt++;
		if(Usart1ReadCnt > Usart1ReadBuffLen -10)//��ֹ�������
		{
			Usart1ReadCnt = 0;
		}
	} 
	else if(USART_GetITStatus(USART1,USART_IT_IDLE) == SET)//�����ж�
	{
		USART1->DR; //���USART_IT_IDLE��־
		//�����ݴ��뻺��
	  BufferManageWrite(&buff_manage_struct_usart1,Usart1ReadBuff,Usart1ReadCnt,&value);
		Usart1ReadCnt=0;
  }  
	
	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
  {
    if(rbCanRead(&rb_t_usart1)>0)//�����������ݸ�������0
    {
			rbRead(&rb_t_usart1,&Usart1SendBits,1);
			USART_SendData(USART1, Usart1SendBits);
    }
    else
    {
      //�����ֽڽ���			
      USART_ClearITPendingBit(USART1,USART_IT_TXE);
      USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
      USART_ITConfig(USART1, USART_IT_TC, ENABLE);
    }
  }
	//�������
  if (USART_GetITStatus(USART1, USART_IT_TC) != RESET)
  {
    USART_ClearITPendingBit(USART1,USART_IT_TC);
    USART_ITConfig(USART1, USART_IT_TC, DISABLE);
  }
} 





void USART2_IRQHandler(void)//����2�жϷ������
{
	u8 Res;
	int value;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		Res =USART_ReceiveData(USART2);	//��ȡ���յ�������
		
		Usart2ReadBuff[Usart2ReadCnt] = Res;	//���յ����ݴ�������
		Usart2ReadCnt++;
		if(Usart2ReadCnt > Usart2ReadBuffLen -10)//��ֹ�������
		{
			Usart2ReadCnt = 0;
		}
	} 
	else if(USART_GetITStatus(USART2,USART_IT_IDLE) == SET)//�����ж�
	{
		USART2->DR; //���USART_IT_IDLE��־
		//�����ݴ��뻺��
	  BufferManageWrite(&buff_manage_struct_usart2,Usart2ReadBuff,Usart2ReadCnt,&value);		
		Usart2ReadCnt=0;
  }  
	
	if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
  {
    if(Usart2SendDataCnt>0)//�����������ݸ�������0
    {
			USART_SendData(USART2, *Usart2SendData);
			Usart2SendData++;
		  Usart2SendDataCnt--;
    }
    else
    {
      USART_ClearITPendingBit(USART2,USART_IT_TXE);
      USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
      USART_ITConfig(USART2, USART_IT_TC, ENABLE);
    }
  }
	//�������
  if (USART_GetITStatus(USART2, USART_IT_TC) != RESET)
  {
    USART_ClearITPendingBit(USART2,USART_IT_TC);
    USART_ITConfig(USART2, USART_IT_TC, DISABLE);
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
	uint8_t data = ch;
	if(!flage)
	{
	  flage=1;
		USART_ClearITPendingBit(USART1,USART_IT_TC);//���printf��ʧ��һ���ֽڵ�����
	}
	PutData(&rb_t_usart1,&data,1);
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
  return ch;
}

