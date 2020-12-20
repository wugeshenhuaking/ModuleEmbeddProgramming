/**
  ******************************************************************************
  * @file    usart.c
  * @author  fengwu yang
  * @version V1.0.0
  * @date    2019/10/12
  * @brief   �������ú���
  ******************************************************************************			
  ******************************************************************************
  */
#define USART_C_
#include "stdio.h"
#include "usart.h"
#include "BufferManage.h"

#include "LoopList.h"

unsigned char Usart1ReadBuff[Usart1ReadBuffLen]={0};  //�������ݻ���
u32 Usart1ReadCnt = 0;//���ڽ��յ������ݸ���

u8  Usart1BufferMemory[Usart1BufferMemoryLen];//�������ݻ�����
u32 Usart1BufferMemoryManage[Usart1BufferMemoryManageLen];//��������
u8  Usart1BufferMemoryCopy[Usart1BufferMemoryCopyLen];//��ȡ������������

u8	Usart1LoopListSendBuff[Usart1LoopListSendBuffLen];//���ڻ��ζ��з��ͻ���


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
	/*��������*/
	BufferManageCreate(&buff_manage_struct_usart1,Usart1BufferMemory,Usart1BufferMemoryLen,Usart1BufferMemoryManage,Usart1BufferMemoryManageLen*4);
	/*�������ζ���*/
	rbCreate(&rb_t_usart1_send,Usart1LoopListSendBuff,Usart1LoopListSendBuffLen);
	
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
	
  
  //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	
	
  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//�����ж�
	
	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);//DMA��ʽ��������
	
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 
}

/**
* @brief   ����DMA��ʼ��
* @param   None
* @param   None
* @retval  None
* @warning None
* @example 
**/
void uart_dma_init(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	          /*����DMAʱ��*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART1->DR);/*�����ַ*/
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)Usart1ReadBuff;   /*�ڴ��ַ*/
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;	          /*����:���赽�ڴ�*/
	DMA_InitStructure.DMA_BufferSize = Usart1ReadBuffLen;         /*����������*/
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;/*�����ַ����*/	 
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;         /*�ڴ��ַ����*/	
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;/*�������ݵ�λ*/	
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;        /*�ڴ����ݵ�λ 8bit*/ 
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;     /*DMAģʽ��һ�δ��䣬ѭ��*/	 
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;/*���ȼ�����*/	  
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;       /*��ֹ�ڴ浽�ڴ�Ĵ���	*/
	DMA_Init(DMA1_Channel5, &DMA_InitStructure);       /*����DMA1��ͨ��*/		    	   
	DMA_Cmd (DMA1_Channel5,ENABLE);					           /*ʹ��DMA*/
}


/**
* @brief  ���ڷ����ַ�������
* @param  *c:���͵�����ָ��  cnt:���ݸ���
* @param  None
* @param  None
* @retval None
* @example 
**/
void UsartOutStr(USART_TypeDef* USARTx,unsigned char *c,uint32_t cnt)
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
void UsartOutChar(USART_TypeDef* USARTx,unsigned char c)
{
	USART_SendData(USARTx,c);
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
}


/**
* @brief  �����жϷ�������
* @param  c:���ݵ��׵�ַ  cnt:���͵����ݸ���
* @param  None
* @param  None
* @retval None
* @example 
**/
void UsartOutStrIT(USART_TypeDef* USARTx,unsigned char *c,uint32_t cnt)
{
	if(USARTx == USART1)
	{
		PutData(&rb_t_usart1_send,c,cnt);//���͵�����д�뻷�ζ��л���
		USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);//ʹ�ܷ����ж�
	}
}


void USART1_IRQHandler(void)//����1�жϷ������
{
	u8 Res;
	int value;
	if(USART_GetITStatus(USART1,USART_IT_IDLE) == SET)//�����ж�
	{
		USART1->DR; //���USART_IT_IDLE��־
		
		DMA_Cmd(DMA1_Channel5,DISABLE);//ʧ��
		
		Usart1ReadCnt = Usart1ReadBuffLen - DMA_GetCurrDataCounter(DMA1_Channel5);//��ȡDMA���յ����ݸ���
		
	  BufferManageWrite(&buff_manage_struct_usart1,Usart1ReadBuff,Usart1ReadCnt,&value);//�����ݴ��뻺��
		
		DMA_SetCurrDataCounter(DMA1_Channel5,Usart1ReadBuffLen);//��������DMA����
		DMA_Cmd(DMA1_Channel5,ENABLE);//ʹ��
  } 
	
	
	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)//�����ж���λ
  {
    if(rbCanRead(&rb_t_usart1_send)>0)//�л��������
    {
			rbRead(&rb_t_usart1_send,&Res,1);//ȡ��һ������
			USART_SendData(USART1, Res);//��������
    }
    else //�����ֽڽ���
    {
      USART_ClearITPendingBit(USART1,USART_IT_TXE);
      USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
      USART_ITConfig(USART1, USART_IT_TC, ENABLE);
    }
  }
	
  if(USART_GetITStatus(USART1, USART_IT_TC) != RESET)//�������
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
	uint8_t data = ch;
	if(!flage)
	{
	  flage=1;
		USART_ClearITPendingBit(USART1,USART_IT_TC);//���printf��ʧ��һ���ֽڵ�����
	}
	
	PutData(&rb_t_usart1_send,&data,1);//���͵�����д�뻷�ζ��л���
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);//ʹ�ܴ���1�����ж�
  return ch;
}

