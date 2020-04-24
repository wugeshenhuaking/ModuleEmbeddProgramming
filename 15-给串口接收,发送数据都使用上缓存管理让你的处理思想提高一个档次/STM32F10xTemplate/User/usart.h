#ifndef __USART_H
#define __USART_H
#include <stm32f10x.h>
#ifndef USART_C_//���û�ж���
#define USART_Ex_ extern
#else
#define USART_Ex_
#endif


#define Usart1ReadLen 150   //�������ݻ��������С
#define Usart1SendLen 1024  //�������ݻ��������С


USART_Ex_ char Usart1ReadBuff[Usart1ReadLen];  //�������ݻ���
USART_Ex_ char Usart1SendBuff[Usart1SendLen];  //�������ݻ���
USART_Ex_ u32  Usart1ReadCnt;//����1���յ������ݸ���
USART_Ex_ u32  Usart1ReadCntCopy;//����1���յ������ݸ���
USART_Ex_ u32  Usart1IdleCnt;//���м����
USART_Ex_ u32  Usart1IdleTime;//���ô��ڿ���ʱ��(MS)
USART_Ex_ u8   Usart1ReadFlage;//����1���յ�һ����������


void uart_init(u32 bound);//����1��ʼ��
void UsartOutStr(unsigned char *c,uint32_t cnt);//���ڷ����ַ�������
void UsartOutChar(unsigned char c);//���ڷ���һ���ֽ�
void UsartOutStrIT(unsigned char *c,uint32_t cnt);
#endif


