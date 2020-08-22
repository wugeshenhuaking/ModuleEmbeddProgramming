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

int addValue=0;
void UsartCallBackFun(char data);
int main(void)
{
  NVIC_Configuration();
	uart_init(115200);	 //串口初始化为115200
	GpioInit();
	DelayInit();
	rbCreate(&Uart1rb,Usart1SendBuff,Usart1SendLen);//创建环形队列--串口1
	UsartCallBackReg(UsartCallBackFun);//把UsartCallBackFun函数传过去
	while(1)
	{
    if(Usart1ReadFlage)//串口接收完一条完整的数据
		{
		  Usart1ReadFlage=0;
//			PutData(&Uart1rb,USART1,Usart1ReadBuff,Usart1ReadCntCopy);//数据写入环形队列,然后打开串口1发送中断发送
			
			printf("addValue = %d",addValue);
			addValue=0;
			memset(Usart1ReadBuff,NULL, sizeof(Usart1ReadBuff));//清零
		}
	}
}
void UsartCallBackFun(char data)
{
	addValue = addValue + data;//计算传过来的数据之和
}
