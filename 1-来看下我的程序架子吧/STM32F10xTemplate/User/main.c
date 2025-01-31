/**
  ******************************************************************************
  * @author  yang feng wu 
  * @version V1.0.0
  * @date    2019/10/12
  * @brief   
  ******************************************************************************
	
  ******************************************************************************
  */
#include "include.h"

/*
#include <stm32f10x.h>
#include "System.h"
#include "delay.h"
#include "usart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "gpio.h"
#include "test.h"
*/


int main(void)
{
  NVIC_Configuration();
	uart_init(115200);	 //串口初始化为115200
	GpioInit();
	DelayInit();
	
	TestValue = 10;
	
	printf("%d\r\n",TestValue);
	
	while(1)
	{
    if(Usart1ReadFlage)//串口接收到数据
		{
		  Usart1ReadFlage=0;
			UsartOutStr(Usart1ReadBuff,Usart1ReadCntCopy);
			memset(Usart1ReadBuff,NULL, sizeof(Usart1ReadBuff));//清零
		}
	}
}

