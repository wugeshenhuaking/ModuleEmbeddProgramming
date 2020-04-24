#ifndef __USART_H
#define __USART_H
#include <stm32f10x.h>
#ifndef USART_C_//如果没有定义
#define USART_Ex_ extern
#else
#define USART_Ex_
#endif


#define Usart1ReadLen 150   //接收数据缓存数组大小
#define Usart1SendLen 1024  //发送数据缓存数组大小


USART_Ex_ char Usart1ReadBuff[Usart1ReadLen];  //接收数据缓存
USART_Ex_ char Usart1SendBuff[Usart1SendLen];  //发送数据缓存
USART_Ex_ u32  Usart1ReadCnt;//串口1接收到的数据个数
USART_Ex_ u32  Usart1ReadCntCopy;//串口1接收到的数据个数
USART_Ex_ u32  Usart1IdleCnt;//空闲检测用
USART_Ex_ u32  Usart1IdleTime;//设置串口空闲时间(MS)
USART_Ex_ u8   Usart1ReadFlage;//串口1接收到一条完整数据


void uart_init(u32 bound);//串口1初始化
void UsartOutStr(unsigned char *c,uint32_t cnt);//串口发送字符串数据
void UsartOutChar(unsigned char c);//串口发送一个字节
void UsartOutStrIT(unsigned char *c,uint32_t cnt);
#endif


