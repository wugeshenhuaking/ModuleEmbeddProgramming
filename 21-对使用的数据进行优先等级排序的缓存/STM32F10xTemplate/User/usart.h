#ifndef __USART_H
#define __USART_H
#include <stm32f10x.h>
#ifndef USART_C_//���û�ж���
#define USART_Ex_ extern
#else
#define USART_Ex_
#endif

#include "BufferManage.h"
#include "LoopList.h"

USART_Ex_ buff_manage_struct buff_manage_struct_usart1;//����������

USART_Ex_ rb_t rb_t_usart1_send;//���ζ��й������

#define Usart1ReadBuffLen 150  //����1�������������С

#define Usart1BufferMemoryLen 1024     //���ڽ��ջ�������С
#define Usart1BufferMemoryCopyLen 150  //��ȡ�����������ݵ������С
#define Usart1BufferMemoryManageLen 20 //���ڽ��ջ���������

#define Usart1LoopListSendBuffLen 1024

USART_Ex_ unsigned char Usart1ReadBuff[Usart1ReadBuffLen];//�������ݻ���
USART_Ex_ u32  Usart1ReadCnt;//����1���յ������ݸ���


USART_Ex_ u8  Usart1BufferMemory[Usart1BufferMemoryLen];//�������ݻ�����
USART_Ex_ u8  Usart1BufferMemoryCopy[Usart1BufferMemoryCopyLen];//��ȡ�����������ݵ�����
USART_Ex_ u32 Usart1BufferMemoryManage[Usart1BufferMemoryManageLen];//��������

USART_Ex_ u8	Usart1LoopListSendBuff[Usart1LoopListSendBuffLen];//���ڻ��ζ��з��ͻ���

void uart_init(u32 bound);//����1��ʼ��
void uart_dma_init(void);//����DMA��ʼ��
void UsartOutStr(USART_TypeDef* USARTx,unsigned char *c,uint32_t cnt);//���ڷ����ַ�������
void UsartOutStrIT(USART_TypeDef* USARTx,unsigned char *c,uint32_t cnt);
void UsartOutChar(USART_TypeDef* USARTx,unsigned char c);//���ڷ���һ���ֽ�
#endif


