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
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	GpioInit();
	DelayInit();
	
	TestValue = 10;
	
	printf("%d\r\n",TestValue);
	
	while(1)
	{
    if(Usart1ReadFlage)//���ڽ��յ�����
		{
		  Usart1ReadFlage=0;
			UsartOutStr(Usart1ReadBuff,Usart1ReadCntCopy);
			memset(Usart1ReadBuff,NULL, sizeof(Usart1ReadBuff));//����
		}
	}
}

