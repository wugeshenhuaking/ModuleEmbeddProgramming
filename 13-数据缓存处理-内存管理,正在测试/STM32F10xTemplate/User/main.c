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
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	GpioInit();
	DelayInit();
	
	while(1)
	{
    if(Usart1ReadFlage)//���ڽ��յ�����
		{
		  Usart1ReadFlage=0;
			
		}
	}
}

