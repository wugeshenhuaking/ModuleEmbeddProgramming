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
#include "timer.h"
#include "usart.h"
#include "ConfigModuleNoBlock.h"

char main_buff[main_buff_len];
int  main_len;

int usart1_read_len;
int main(void)
{
	char data_read;
  NVIC_Configuration();
	usart_init(115200,115200,115200);	 //串口初始化
	delay_init();
	timer2_init();
	//不执行框架配置模组
	ConfigModuleNoBlockFlage = 1;
	while(1)
	{
		/*配置完模组*/
		if(ConfigModuleNoBlockFlage)
		{
			/*执行其它程序*/
		}
		
		ConfigModuleNoBlock();//配置模块
		
		//串口接收数据出现空闲
		if(usart1_idle_flag)
		{
			usart1_idle_flag = 0;
			//读取串口接收的数据个数
			usart1_read_len = rbCanRead(&rb_t_usart1_read);
			//读取接收的数据,数据读取到 usart1_read_buff_copy 数组
			memset(usart1_read_buff_copy,0,rb_t_usart1_read_buff_len);
			rbRead(&rb_t_usart1_read,usart1_read_buff_copy,usart1_read_len);
			
			//可以在这里判断模组返回的数据有没有问题
			//如果有问题就重新配置模组
			//下面是假设模组返回了 disconnect 就需要重新配置模组
			if(strstr((char*)usart1_read_buff_copy,"disconnect")){
				ConfigModuleNoBlockFlage=0;
				ConfigModuleNoBlockCaseValue=0;
			}
			
			if(ConfigConnectDispose != NULL){
				ConfigConnectDispose((char*)usart1_read_buff_copy,usart1_read_len);
			}
		}
	}
}












