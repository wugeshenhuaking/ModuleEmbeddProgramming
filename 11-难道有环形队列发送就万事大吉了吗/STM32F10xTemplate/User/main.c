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

char temp[11]="qwertyuiop";
char temp1[15]="aaaaaaaaaaaaaaa";

uint8_t SendCount[1] = {0};
int main(void)
{
  NVIC_Configuration();
	uart_init(115200);	 //串口初始化为115200
	GpioInit();
	DelayInit();
	
	rbCreate(&Uart1rb,Usart1SendBuff,Usart1SendLen);//创建环形队列--串口1
	//创建环形队列--管理发送每一条数据
	rbCreate(&Uart1rbManage,Usart1ManageSendBuff,Usart1ManageSendBuffLen);
	
	while(1)
	{
		if(SysTickCntMs>=5000)
		{
			SysTickCntMs=0;
			
			
			if(rbCanWrite(&Uart1rb)>=10)
			{
				if(rbCanWrite(&Uart1rbManage)>=1)
				{
					PutData(&Uart1rb,temp,10);//数据写入环形队列
					SendCount[0] = 10;//这次发送的数据个数
					PutData(&Uart1rbManage,SendCount,1);//数据写入环形队列,记录这次要发送的数据个数
				}
			}
			
			PutData(&Uart1rb,temp1,15);//数据写入环形队列
			SendCount[0] = 15;//这次发送的数据个数
			PutData(&Uart1rbManage,SendCount,1);//数据写入环形队列,记录这次要发送的数据个数
		}

		
//		delay_ms(5000);
    if(Usart1ReadFlage)//串口接收完一条完整的数据
		{
		  Usart1ReadFlage=0;
			PutData(&Uart1rb,temp,10);//数据写入环形队列,然后打开串口1发送中断发送
			PutData(&Uart1rb,temp,10);//数据写入环形队列,然后打开串口1发送中断发送
		
//			UsartOutStr(Usart1ReadBuff,Usart1ReadCntCopy);
			memset(Usart1ReadBuff,NULL, sizeof(Usart1ReadBuff));//清零
		}
	}
}

