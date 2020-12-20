#ifndef __USART_H
#define __USART_H
#include <stm32f10x.h>
#ifndef USART_C_//如果没有定义
#define USART_Ex_ extern
#else
#define USART_Ex_
#endif

#include "BufferManage.h"
#include "LoopList.h"

USART_Ex_ buff_manage_struct buff_manage_struct_usart1;//缓存管理变量

USART_Ex_ rb_t rb_t_usart1_send;//环形队列管理变量

#define Usart1ReadBuffLen 150  //串口1接收数据数组大小

#define Usart1BufferMemoryLen 1024     //串口接收缓存区大小
#define Usart1BufferMemoryCopyLen 150  //提取缓存区的数据的数组大小
#define Usart1BufferMemoryManageLen 20 //串口接收缓存区管理

#define Usart1LoopListSendBuffLen 1024

USART_Ex_ unsigned char Usart1ReadBuff[Usart1ReadBuffLen];//接收数据缓存
USART_Ex_ u32  Usart1ReadCnt;//串口1接收到的数据个数


USART_Ex_ u8  Usart1BufferMemory[Usart1BufferMemoryLen];//接收数据缓存区
USART_Ex_ u8  Usart1BufferMemoryCopy[Usart1BufferMemoryCopyLen];//提取缓存区的数据的数组
USART_Ex_ u32 Usart1BufferMemoryManage[Usart1BufferMemoryManageLen];//管理缓存区

USART_Ex_ u8	Usart1LoopListSendBuff[Usart1LoopListSendBuffLen];//串口环形队列发送缓存

void uart_init(u32 bound);//串口1初始化
void uart_dma_init(void);//串口DMA初始化
void UsartOutStr(USART_TypeDef* USARTx,unsigned char *c,uint32_t cnt);//串口发送字符串数据
void UsartOutStrIT(USART_TypeDef* USARTx,unsigned char *c,uint32_t cnt);
void UsartOutChar(USART_TypeDef* USARTx,unsigned char c);//串口发送一个字节
#endif


