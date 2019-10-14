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

int maindelay=0;
int main(void)
{
  NVIC_Configuration();
	uart_init(115200);	 //串口初始化为115200
	GpioInit();
	DelayInit();
	rbCreate(&Uart1rb,Usart1SendBuff,Usart1SendLen);//创建环形队列--串口1
	
//	ConfigModuleNoBlockFlage = 1;//不让配置函数执行
	
	while(1)
	{
		ConfigModuleNoBlock();//配置模块
		if(Usart1ReadFlage)//串口接收到一条数据
		{
			Usart1ReadFlage=0;
			if(ConfigConnectDispose != NULL)
			{
			  ConfigConnectDispose(Usart1ReadBuff);//处理模块返回的数据
			}
			
			if(ConfigModuleNoBlockFlage == 1)//一开始是配置成功的
			{
				if(strstr(Usart1ReadBuff,"CLOSED"))//接收到CLOSED,设备连接出现问题
				{
					ConfigModuleNoBlockFlage=0;
					ConfigModuleNoBlockCaseValue=0;
				}
			}
			memset(Usart1ReadBuff,0,Usart1ReadCntCopy);
		}
		
		
		if(maindelay>=500)//证明主程序一直在运行
		{
			maindelay =0 ;
			PCout(13) = ~PCout(13);
		}
	}
}

