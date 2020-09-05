/**
  ******************************************************************************
  * @author  yang feng wu 
  * @version V1.0.0
  * @date    2019/10/12
  * @brief   
  ******************************************************************************
  ******************************************************************************
  */
#include "main.h"
#include <stdio.h>
#include <string.h>
#include "System.h"
#include "delay.h"
#include "usart.h"
#include "gpio.h"
#include "timer.h"
#include "iwdg.h"

#include "stmflash.h"
#include "flash_helper.h"

void PWR_PVD_Init(void)
{      
    RCC->APB1ENR|=1<<28;    //??PORTB??
    PWR->CR |= 7<<5; //2.9V ????
    PWR->CR |= 1<<4; //PVD??   
    EXTI->IMR|=1<<16;
    EXTI->RTSR|=1<<16;
    EXTI->EMR |=1<<16;
    EXTI->SWIER |= 1<<16;
}

void PVD_IRQHandler(void)
{
	EXTI->PR |=1<<16;//???   
	if (((PWR->CSR)&(1<<2))!=0)
	{
		printf("11111111111122222222223333333\r\n");
	}        
}


int main(void)
{
	int i,j;
	u16 data;
  NVIC_Configuration();
	uart_init(115200,115200);	 //���ڳ�ʼ��Ϊ115200
	GpioInit();

	DelayInit();
	
	printf("start\r\n");
	
	PWR_PVD_Init();//���Ե���洢
	
	/*��ʼ���洢*/
	FlashHelperInit(FLASH_DATA_ADDR_1,FLASH_DATA_ADDR_2,FLASH_DATA_ADDR_3,FLASH_DATA_ADDR_4);
	/*��ȡ��ǰ���������*/
	printf("��ǰ���������:%d\r\n",flash_helper_struct.FlashHelperData[1]);
	
	/*������д�����黺��,Ĭ�Ϸ�Χ 1-18 */
	flash_helper_struct.FlashHelperData[1] = 20;
	FlashHelperUpdate();//ˢ��
	
	/*��ȡ����洢������,����ĺ�����Ҫ�����ŵ���!*/
	data = FlashHelperGetIndex(1);//1������,Ҫ���ϵ������±걣��һ��!
	
	printf("��ȡ������:%d\r\n",data);
	

	
	while(1)
	{
		IWDG_Feed();//ι��
	}
}







