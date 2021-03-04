#ifndef __DELAY_H
#define __DELAY_H

#ifndef __DELAY_C_
#define __DELAY_Ex_  extern
#else 
#define __DELAY_Ex_
#endif

#include "stm32f4xx_conf.h"
 
/**
* @brief  系统定时器初始化 1Ms中断
* @param   
* @param  None
* @param  None
* @retval None
* @example 
**/
void delay_init(void);
/**
* @brief  延时ms
* @param  ms 延时ms
* @param  None
* @param  None
* @retval None
* @example 
**/
void delay_ms(u16 ms);
#endif





























