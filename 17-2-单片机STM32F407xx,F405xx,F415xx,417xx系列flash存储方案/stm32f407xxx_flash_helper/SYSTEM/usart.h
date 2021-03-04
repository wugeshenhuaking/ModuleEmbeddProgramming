#ifndef __USART_H
#define __USART_H

#ifndef USART_C_//���û�ж���
#define USART_Ex_ extern
#else
#define USART_Ex_
#endif

#include <stdio.h>
#include "stm32f4xx_conf.h"
#include "LoopList.h"

/****************************����1****************************/
//���ͻ��ζ���
USART_Ex_ rb_t rb_t_send_usart1;

//���ζ������� (����)
#define rb_t_send_usart1_buff_len 2048
USART_Ex_ unsigned char rb_t_send_usart1_buff[rb_t_send_usart1_buff_len];


/**
* @brief   ���ڳ�ʼ��
* @param   bound  ������
* @param   None
* @param   None
* @retval  None
* @warning None
* @example 
**/
void uart_init(u32 bound1,u32 bound2);

/**
* @brief  ���ڷ����ַ�������
* @param  *c:���͵�����ָ��  cnt:���ݸ���
* @param  None
* @param  None
* @retval None
* @example 
**/
void UsartOutStr(USART_TypeDef* USARTx, unsigned char *c,uint32_t cnt);

/**
* @brief  ���ڷ���һ���ֽ�
* @param  *c:���͵�����ָ��  cnt:���ݸ���
* @param  None
* @param  None
* @retval None
* @example 
**/
void UsartOutChar(USART_TypeDef* USARTx, unsigned char c);

#endif


