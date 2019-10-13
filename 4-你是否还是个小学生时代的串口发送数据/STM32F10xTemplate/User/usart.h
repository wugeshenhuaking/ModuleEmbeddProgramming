#ifndef __USART_H
#define __USART_H
#include <stm32f10x.h>
#ifndef USART_C_//���û�ж���
#define USART_C_ extern
#else
#define USART_C_
#endif


#define Usart1ReadLen 150  //����1�������������С
USART_C_ char Usart1ReadBuff[Usart1ReadLen];  //�������ݻ���
USART_C_ u32  Usart1ReadCnt;//����1���յ������ݸ���
USART_C_ u32  Usart1ReadCntCopy;//����1���յ������ݸ���
USART_C_ u32  Usart1IdleCnt;//���м����
USART_C_ u32  Usart1IdleTime;//���ô��ڿ���ʱ��(MS)
USART_C_ u8   Usart1ReadFlage;//����1���յ�һ����������


void uart_init(u32 bound);//����1��ʼ��
void UsartOutStr(unsigned char *c,uint32_t cnt);//���ڷ����ַ�������
void UsartOutChar(unsigned char c);//���ڷ���һ���ֽ�

void UsartOutStrIT(char *c,uint32_t cnt);//�����жϷ����ַ�������
#endif


