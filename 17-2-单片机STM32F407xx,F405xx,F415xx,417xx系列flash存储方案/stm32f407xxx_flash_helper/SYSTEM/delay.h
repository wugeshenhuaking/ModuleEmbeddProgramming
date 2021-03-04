#ifndef __DELAY_H
#define __DELAY_H

#ifndef __DELAY_C_
#define __DELAY_Ex_  extern
#else 
#define __DELAY_Ex_
#endif

#include "stm32f4xx_conf.h"
 
/**
* @brief  ϵͳ��ʱ����ʼ�� 1Ms�ж�
* @param   
* @param  None
* @param  None
* @retval None
* @example 
**/
void delay_init(void);
/**
* @brief  ��ʱms
* @param  ms ��ʱms
* @param  None
* @param  None
* @retval None
* @example 
**/
void delay_ms(u16 ms);
#endif





























