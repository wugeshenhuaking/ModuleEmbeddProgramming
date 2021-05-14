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
	usart_init(115200,115200,115200);	 //���ڳ�ʼ��
	delay_init();
	timer2_init();
	//��ִ�п������ģ��
	ConfigModuleNoBlockFlage = 1;
	while(1)
	{
		/*������ģ��*/
		if(ConfigModuleNoBlockFlage)
		{
			/*ִ����������*/
		}
		
		ConfigModuleNoBlock();//����ģ��
		
		//���ڽ������ݳ��ֿ���
		if(usart1_idle_flag)
		{
			usart1_idle_flag = 0;
			//��ȡ���ڽ��յ����ݸ���
			usart1_read_len = rbCanRead(&rb_t_usart1_read);
			//��ȡ���յ�����,���ݶ�ȡ�� usart1_read_buff_copy ����
			memset(usart1_read_buff_copy,0,rb_t_usart1_read_buff_len);
			rbRead(&rb_t_usart1_read,usart1_read_buff_copy,usart1_read_len);
			
			//�����������ж�ģ�鷵�ص�������û������
			//������������������ģ��
			//�����Ǽ���ģ�鷵���� disconnect ����Ҫ��������ģ��
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












