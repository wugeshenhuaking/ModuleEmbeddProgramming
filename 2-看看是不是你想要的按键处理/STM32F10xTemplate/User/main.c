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


int main(void)
{
  NVIC_Configuration();
	uart_init(115200);	 //串口初始化为115200
	GpioInit();
	DelayInit();
	
	while(1)
	{
		SmartConfigKey();
		//例2:检测到按键按下,然后根据按下时间执行某段代码
		if(KeySmartConfig[3] == 1)
		{
			if(KeySmartConfig[5]>=3000)//按下时间大于3S
			{
				KeySmartConfig[3] = 0;//清零以后,只有按键松开再按下的时候才会进入
				printf("按键按下时间超过3S\r\n");
			}
		}
		
		//例3:检测到按键松开执行某段代码
		if(KeySmartConfig[4] == 1)
		{
			KeySmartConfig[4] = 0;//清零以后,只有按键按下然后松开的时候才会进入
			printf("按键松开\r\n");
		}
		
		
    if(Usart1ReadFlage)//串口接收到数据
		{
		  Usart1ReadFlage=0;
			UsartOutStr(Usart1ReadBuff,Usart1ReadCntCopy);
			memset(Usart1ReadBuff,NULL, sizeof(Usart1ReadBuff));//清零
		}
	}
}

