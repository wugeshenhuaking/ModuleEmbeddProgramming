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


/****************************����1****************************/
//���ջ��ζ���
rb_t rb_t_usart1_read;
//���ζ��л�������
unsigned char rb_t_usart1_read_buff[rb_t_usart1_read_buff_len];
//�ӻ��濽������ʹ��
unsigned char usart1_read_buff_copy[rb_t_usart1_read_buff_len];
//���ռ���
int usart1_read_count=0;


//���ͻ��ζ���
rb_t rb_t_usart1_send;
//���ζ��л�������
unsigned char rb_t_usart1_send_buff[rb_t_usart1_send_buff_len];
//������ȡ���ζ���1���ֽ�
unsigned char rb_t_usart1_send_byte;
//�����жϱ�־
unsigned char usart1_idle_flag=0;



/****************************����2****************************/
//���ջ��ζ���
rb_t rb_t_usart2_read;
//���ζ��л�������
unsigned char rb_t_usart2_read_buff[rb_t_usart2_read_buff_len];
//�ӻ��濽������ʹ��
unsigned char usart2_read_buff_copy[rb_t_usart2_read_buff_len];
//���ռ���
int usart2_read_count=0;


//�Զ�������жϼ��
int usart2_idle_read_count=0;//�ԱȽ��ո����Ƿ�ı�
int usart2_idle_cnt=0;
unsigned char usart2_idle_flag=0;//��־


/****************************����3****************************/
//���ζ��н���ʹ�õĻ�������
unsigned char rb_t_usart3_read_buff[rb_t_usart3_read_buff_len];
//�ӻ��濽������ʹ��
unsigned char usart3_read_buff_copy[rb_t_usart3_read_buff_len];


//���ζ��з���ʹ�õĻ�������
unsigned char rb_t_usart3_send_buff[rb_t_usart3_send_buff_len];
unsigned char rb_t_usart3_send_byte;//������ȡ���ζ���1���ֽ�

//�����жϱ�־
unsigned char usart3_idle_flag=0;//��־


/**
* @brief   ���ڳ�ʼ��
* @param   bound  ������
* @param   None
* @param   None
* @retval  None
* @warning None
* @example 
**/
void usart_init(u32 bound1,u32 bound2,u32 bound3){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//�������ζ���(���ڴ���1��������)
	rbCreate(&rb_t_usart1_read,rb_t_usart1_read_buff,rb_t_usart1_read_buff_len);
	//�������ζ���(���ڴ���1��������)
	rbCreate(&rb_t_usart1_send,rb_t_usart1_send_buff,rb_t_usart1_send_buff_len);
	
	
	//�������ζ���(���ڴ���2��������)
	rbCreate(&rb_t_usart2_read,rb_t_usart2_read_buff,rb_t_usart2_read_buff_len);
	
	
	//�������ζ���(���ڴ���3��������)
	rbCreate(&rb_t_usart3_send,rb_t_usart3_send_buff,rb_t_usart3_send_buff_len);
	//�������ζ���(���ڴ���3��������)
	rbCreate(&rb_t_usart3_read,rb_t_usart3_read_buff,rb_t_usart3_read_buff_len);
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2|RCC_APB1Periph_USART3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_USART1|RCC_APB2Periph_AFIO , ENABLE);
	
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//USART2_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  //USART2_RX	  GPIOA.3
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	//USART3_TX   GPIOB.10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  //USART3_RX	  GPIOB.11
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
  
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
	
	USART_InitStructure.USART_BaudRate = bound3;//���ڲ�����
	USART_Init(USART3, &USART_InitStructure); //��ʼ������3
	
	
	/*����--1*/
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
  /*����--2*/
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
  /*����--3*/
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
	
	
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//�����ж�
//	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);//�����ж�
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);//�����ж�
	
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���
	USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���
	USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���
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
		PutData(&rb_t_usart1_send,c,cnt);
		USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);
	}
	else if(USARTx == USART2){
		printf("����2�жϷ�����ο�����3����ʵ��!\r\n");
	}
	else if(USARTx == USART3){
		PutData(&rb_t_usart3_send,c,cnt);
		USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);
		
		printf("\r\n����3����:\r\n");
		PutData(&rb_t_usart1_send,c,cnt);
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
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
	if(USARTx == USART2){
		printf("����2����:\r\n");
		PutData(&rb_t_usart1_send,c,cnt);
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	}
	else if(USARTx == USART3){
		printf("����3����:\r\n");
		PutData(&rb_t_usart1_send,c,cnt);
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	}
	
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

/**
* @brief  ����2�Զ�������жϼ��(�ŵ�1ms��ʱ��)
* @param  IdleCnt: ����ʱ��
* @param  None
* @param  None
* @retval None
* @example 
**/
void Usart2IdleLoop(int IdleCnt)
{
	if(usart2_read_count!=0)//���ڽ��յ�����
	{
		if(usart2_idle_read_count != usart2_read_count)
		{
			usart2_idle_read_count = usart2_read_count;
			usart2_idle_cnt = 0;
		}
		else
		{
			usart2_idle_cnt++;
			if(usart2_idle_cnt > IdleCnt)//�������ʱ��
			{
				usart2_idle_cnt = 0;
				usart2_read_count=0;
				usart2_idle_flag = 1;//���б�־
			}
		}
	}
}


//�����жϷ������
void USART1_IRQHandler(void)
{
	u8 Res;
	int value;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		Res =USART_ReceiveData(USART1);	//��ȡ���յ�������
		
		PutData(&rb_t_usart1_read,&Res,1);
		usart1_read_count++;
	}
	else if(USART_GetITStatus(USART1,USART_IT_IDLE) == SET)//�����ж�
	{
		USART1->DR; //���USART_IT_IDLE��־
		usart1_idle_flag = 1;
  }
	
	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
  {
    if(rbCanRead(&rb_t_usart1_send)>0)//�����������ݸ�������0
    {
			rbRead(&rb_t_usart1_send,&rb_t_usart1_send_byte,1);
			USART_SendData(USART1, rb_t_usart1_send_byte);
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


//�����жϷ������
void USART2_IRQHandler(void)
{
	u8 Res;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		Res =USART_ReceiveData(USART2);	//��ȡ���յ�������
		
		//���յ����ݴ��뻺��
		PutData(&rb_t_usart2_read,&Res,1);
		usart2_read_count++;
		
		/**** �Ѵ���2���յ�����ʹ����־�ڴ�ӡ���� ****/
		if(usart2_read_count==1) printf("\r\n����2����>>\r\n");
		PutData(&rb_t_usart1_send,&Res,1);
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	}
}


//�����жϷ������
void USART3_IRQHandler(void)
{
	u8 Res;
	static u8 flag=0;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		Res =USART_ReceiveData(USART3);	//��ȡ���յ�������
		
		PutData(&rb_t_usart3_read,&Res,1);
		
		/**** �Ѵ���3���յ�����ʹ����־�ڴ�ӡ���� ****/
		if(flag==0) printf("\r\n����3����>>\r\n");
		flag=1;
		PutData(&rb_t_usart1_send,&Res,1);
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	} 
	else if(USART_GetITStatus(USART3,USART_IT_IDLE) == SET)//�����ж�
	{
		USART3->DR; //���USART_IT_IDLE��־
		flag=0;
		usart3_idle_flag=1;
  }  
	
	if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET)
  {
    if(rbCanRead(&rb_t_usart3_send)>0)//�����������ݸ�������0
    {
			rbRead(&rb_t_usart3_send,&rb_t_usart3_send_byte,1);
			USART_SendData(USART3, rb_t_usart3_send_byte);
    }
    else
    {
      //�����ֽڽ���			
      USART_ClearITPendingBit(USART3,USART_IT_TXE);
      USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
      USART_ITConfig(USART3, USART_IT_TC, ENABLE);
    }
  }
	//�������
  if (USART_GetITStatus(USART3, USART_IT_TC) != RESET)
  {
    USART_ClearITPendingBit(USART3,USART_IT_TC);
    USART_ITConfig(USART3, USART_IT_TC, DISABLE);
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
	PutData(&rb_t_usart1_send,&data,1);
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
  return ch;
}

