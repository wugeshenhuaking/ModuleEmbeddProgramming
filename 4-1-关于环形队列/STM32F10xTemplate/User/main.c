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
	usart_init(115200,115200,115200);	 //���ڳ�ʼ��
	delay_init();
	
	while(1)
	{
		//������ڻ�������������
		if(rbCanRead(&rb_t_usart1_read)>0)
		{
			//��ȡһ������
			rbRead(&rb_t_usart1_read,&data_read,1);
			//ʹ�ô���1���ͳ�ȥ
			USART_SendData(USART1, data_read);
		}
	}
}












