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

/****************************串口1****************************/
//接收环形队列
USART_Ex_ rb_t rb_t_usart1_read;
#define rb_t_usart1_read_buff_len 1024
USART_Ex_ unsigned char rb_t_usart1_read_buff[rb_t_usart1_read_buff_len];
//从缓存拷贝数据使用
USART_Ex_ unsigned char usart1_read_buff_copy[rb_t_usart1_read_buff_len];
//接收计数
USART_Ex_ int usart1_read_count;


//发送环形队列
USART_Ex_ rb_t rb_t_usart1_send;
#define rb_t_usart1_send_buff_len 1024
USART_Ex_ unsigned char rb_t_usart1_send_buff[rb_t_usart1_send_buff_len];
USART_Ex_ unsigned char rb_t_usart1_send_byte;//串口提取环形队列1个字节

//空闲中断标志
USART_Ex_ unsigned char usart1_idle_flag;//标志



/****************************串口2****************************/
//接收环形队列
USART_Ex_ rb_t rb_t_usart2_read;
#define rb_t_usart2_read_buff_len 100
//环形队列缓存数组
USART_Ex_ unsigned char rb_t_usart2_read_buff[rb_t_usart2_read_buff_len];
//从缓存拷贝数据使用
USART_Ex_ unsigned char usart2_read_buff_copy[rb_t_usart2_read_buff_len];


//自定义空闲中断检测
USART_Ex_ int usart2_idle_read_count;//接收计数
USART_Ex_ unsigned char usart2_idle_flag;



/****************************串口3****************************/
USART_Ex_ rb_t rb_t_usart3_read;
//环形队列接收使用的缓存数组
#define rb_t_usart3_read_buff_len 1024
USART_Ex_ unsigned char rb_t_usart3_read_buff[rb_t_usart3_read_buff_len];
//从缓存拷贝数据使用
USART_Ex_ unsigned char usart3_read_buff_copy[rb_t_usart3_read_buff_len];


USART_Ex_ rb_t rb_t_usart3_send;
//环形队列发送使用的缓存数组
#define rb_t_usart3_send_buff_len 1024
USART_Ex_ unsigned char rb_t_usart3_send_buff[rb_t_usart3_send_buff_len];
USART_Ex_ unsigned char rb_t_usart3_send_byte;//串口提取环形队列1个字节

//空闲中断标志
USART_Ex_ unsigned char usart3_idle_flag;//标志




void usart_init(u32 bound1,u32 bound2,u32 bound3);//串口初始化
void UsartOutStrIT(USART_TypeDef* USARTx, unsigned char *c,uint32_t cnt);
void UsartOutStr(USART_TypeDef* USARTx, unsigned char *c,uint32_t cnt);//串口发送字符串数据
void UsartOutChar(USART_TypeDef* USARTx, unsigned char c);//串口发送一个字节
void Usart2IdleLoop(int IdleCnt);
#endif


