/**
  ******************************************************************************
  * @author  yang feng wu 
  * @version V1.0.0
  * @date    2020/10/10
  * @brief   main
  ******************************************************************************
  ******************************************************************************
*/
	
#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mcu_sys.h"
#include "delay.h"
#include "usart.h"
#include "LoopList.h"

int main(void)
{
	char data_read;
  NVIC_Configuration();
	usart_init(115200,115200,115200);	 //串口初始化
	delay_init();
	
	while(1)
	{
		//如果串口缓存里面有数据
		if(rbCanRead(&rb_t_usart1_read)>0)
		{
			//读取一个数据
			rbRead(&rb_t_usart1_read,&data_read,1);
			//使用串口1发送出去
			USART_SendData(USART1, data_read);
		}
	}
}












