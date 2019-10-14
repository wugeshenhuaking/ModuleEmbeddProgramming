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

void Init8266(void);
char state=0;
int main(void)
{
  NVIC_Configuration();
	uart_init(115200);	 //串口初始化为115200
	GpioInit();
	DelayInit();
	
	rbCreate(&Uart1rb,Usart1SendBuff,Usart1SendLen);//创建环形队列--串口1
	Init8266();
	
	while(state==0){
		state = ConfigModuleBlock("AT+RST\r\n","ready",NULL);//复位模块
	}
	
	while(1)
	{
	}
}
void Init8266(void)
{
	ConfigModuleBlock("AT+RST\r\n","ready",NULL);//复位模块
	ConfigModuleBlock("+++","+++",NULL);//退出透传
	ConfigModuleBlock("AT+RESTORE\r\n","ready",NULL);//恢复出厂设置
	ConfigModuleBlock("AT+CWMODE_DEF=1\r\n","OK",NULL);//模式1
	ConfigModuleBlock("AT+CWAUTOCONN=1\r\n","OK",NULL);//自动连接路由器
  ConfigModuleBlock("AT+CWJAP_DEF=\"qqqqq\",\"11223344\"\r\n","OK","WIFI CONNECTED");//连接路由器
	ConfigModuleBlock("AT+RST\r\n","ready","OK");//复位
}

