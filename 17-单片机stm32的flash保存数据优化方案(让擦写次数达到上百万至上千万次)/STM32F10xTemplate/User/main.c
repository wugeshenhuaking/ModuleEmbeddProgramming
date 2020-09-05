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
	uart_init(115200,115200);	 //串口初始化为115200
	GpioInit();

	DelayInit();
	
	printf("start\r\n");
	
	PWR_PVD_Init();//测试掉电存储
	
	/*初始化存储*/
	FlashHelperInit(FLASH_DATA_ADDR_1,FLASH_DATA_ADDR_2,FLASH_DATA_ADDR_3,FLASH_DATA_ADDR_4);
	/*获取先前存入的数据*/
	printf("先前存入的数据:%d\r\n",flash_helper_struct.FlashHelperData[1]);
	
	/*把数据写入数组缓存,默认范围 1-18 */
	flash_helper_struct.FlashHelperData[1] = 20;
	FlashHelperUpdate();//刷新
	
	/*获取上面存储的数据,下面的函数需要紧接着调用!*/
	data = FlashHelperGetIndex(1);//1是索引,要和上的数组下标保持一致!
	
	printf("获取的数据:%d\r\n",data);
	

	
	while(1)
	{
		IWDG_Feed();//喂狗
	}
}







