#ifndef __USART_H
#define __USART_H
#include <stm32f10x.h>
#ifndef USART_C_//���û�ж���
#define USART_Ex_ extern
#else
#define USART_Ex_
#endif


#define Usart1ReadLen 150  //����1�������������С
#define Usart1SendLen 500  //����������ֽ���

#define Usart1ManageSendBuffLen 10  //����������ķ������������ĸ���

USART_Ex_ char Usart1ReadBuff[Usart1ReadLen];  //�������ݻ���
USART_Ex_ u32  Usart1ReadCnt;//����1���յ������ݸ���
USART_Ex_ u32  Usart1ReadCntCopy;//����1���յ������ݸ���
USART_Ex_ u32  Usart1IdleCnt;//���м����
USART_Ex_ u32  Usart1IdleTime;//���ô��ڿ���ʱ��(MS)
USART_Ex_ u8   Usart1ReadFlage;//����1���յ�һ����������
USART_Ex_ u8   Usart1SendBuff[Usart1SendLen];  //�������ݻ���--���ζ�����

USART_Ex_ u8   Usart1ManageSendBuff[Usart1ManageSendBuffLen];//������ÿһ������--���ζ�����
USART_Ex_ u32  Usart1ManageSendDatLen;//���ζ��ж�ȡ������,��ѯ�����Ҫ���͵����ݸ���
USART_Ex_ u32  Usart1ManageSendDelayCnt;//������һ�����ݷ��͵�ʱ��

void uart_init(u32 bound);//����1��ʼ��
void UsartOutStr(unsigned char *c,uint32_t cnt);//���ڷ����ַ�������
void UsartOutChar(unsigned char c);//���ڷ���һ���ֽ�
#endif


