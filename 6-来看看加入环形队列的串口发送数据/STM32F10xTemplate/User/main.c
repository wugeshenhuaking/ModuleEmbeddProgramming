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

char temp[10]="qwertyuiop";
int main(void)
{
  NVIC_Configuration();
	uart_init(115200);	 //串口初始化为115200
	GpioInit();
	DelayInit();
	
	rbCreate(&Uart1rb,Usart1SendBuff,Usart1SendLen);//创建环形队列--串口1
	while(1)
	{
		PutData(&Uart1rb,USART1,temp,10);//数据写入环形队列,然后打开串口1发送中断发送
		PutData(&Uart1rb,USART1,temp,10);//数据写入环形队列,然后打开串口1发送中断发送

		delay_ms(10);
    if(Usart1ReadFlage)//串口接收完一条完整的数据
		{
		  Usart1ReadFlage=0;
			PutData(&Uart1rb,USART1,temp,10);//数据写入环形队列,然后打开串口1发送中断发送
			PutData(&Uart1rb,USART1,temp,10);//数据写入环形队列,然后打开串口1发送中断发送
		
//			UsartOutStr(Usart1ReadBuff,Usart1ReadCntCopy);
			memset(Usart1ReadBuff,NULL, sizeof(Usart1ReadBuff));//清零
		}
	}
}

