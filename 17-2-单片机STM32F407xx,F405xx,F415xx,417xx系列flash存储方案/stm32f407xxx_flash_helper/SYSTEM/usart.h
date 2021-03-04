#ifndef __USART_H
#define __USART_H

#ifndef USART_C_//如果没有定义
#define USART_Ex_ extern
#else
#define USART_Ex_
#endif

#include <stdio.h>
#include "stm32f4xx_conf.h"
#include "LoopList.h"

/****************************串口1****************************/
//发送环形队列
USART_Ex_ rb_t rb_t_send_usart1;

//环形队列数组 (发送)
#define rb_t_send_usart1_buff_len 2048
USART_Ex_ unsigned char rb_t_send_usart1_buff[rb_t_send_usart1_buff_len];


/**
* @brief   串口初始化
* @param   bound  波特率
* @param   None
* @param   None
* @retval  None
* @warning None
* @example 
**/
void uart_init(u32 bound1,u32 bound2);

/**
* @brief  串口发送字符串数据
* @param  *c:发送的数据指针  cnt:数据个数
* @param  None
* @param  None
* @retval None
* @example 
**/
void UsartOutStr(USART_TypeDef* USARTx, unsigned char *c,uint32_t cnt);

/**
* @brief  串口发送一个字节
* @param  *c:发送的数据指针  cnt:数据个数
* @param  None
* @param  None
* @retval None
* @example 
**/
void UsartOutChar(USART_TypeDef* USARTx, unsigned char c);

#endif


