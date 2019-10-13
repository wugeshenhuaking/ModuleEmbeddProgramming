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

char temp[10]="qwertyuioa";
int main(void)
{
	int i=0;
  NVIC_Configuration();
	uart_init(115200);	 //串口初始化为115200
	GpioInit();
	DelayInit();
	
	while(1)
	{
    if(Usart1ReadFlage)//串口接收到一条完整的数据
		{
		  Usart1ReadFlage=0;
			
			UsartOutStrIT(temp,10);
			
//			UsartOutStr(Usart1ReadBuff,Usart1ReadCntCopy);//返回接收的数据
			memset(Usart1ReadBuff,NULL, sizeof(Usart1ReadBuff));//清零
		}
	}
}

