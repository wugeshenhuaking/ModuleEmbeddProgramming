/**
  ******************************************************************************
  * @author  yang feng wu 
  * @version V1.0.0
  * @date    2019/12/30
  * @brief   
  ******************************************************************************
	
  ******************************************************************************
  */
#include "include.h"

OS_MEM *CommTxBuffer;
u8 CommTxPart[50][64];

int main(void)
{
  NVIC_Configuration();
	uart_init(115200);	 //串口初始化为115200
	GpioInit();
	DelayInit();
	
	while(1)
	{
    if(Usart1ReadFlage)//串口接收到数据
		{
		  Usart1ReadFlage=0;
			
		}
	}
}

