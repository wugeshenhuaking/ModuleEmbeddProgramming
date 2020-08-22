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
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	GpioInit();
	DelayInit();
	
	rbCreate(&Uart1rb,Usart1SendBuff,Usart1SendLen);//�������ζ���--����1
	Init8266();
	
	while(state==0){
		state = ConfigModuleBlock("AT+RST\r\n","ready",NULL);//��λģ��
	}
	
	while(1)
	{
	}
}
void Init8266(void)
{
	ConfigModuleBlock("AT+RST\r\n","ready",NULL);//��λģ��
	ConfigModuleBlock("+++","+++",NULL);//�˳�͸��
	ConfigModuleBlock("AT+RESTORE\r\n","ready",NULL);//�ָ���������
	ConfigModuleBlock("AT+CWMODE_DEF=1\r\n","OK",NULL);//ģʽ1
	ConfigModuleBlock("AT+CWAUTOCONN=1\r\n","OK",NULL);//�Զ�����·����
  ConfigModuleBlock("AT+CWJAP_DEF=\"qqqqq\",\"11223344\"\r\n","OK","WIFI CONNECTED");//����·����
	ConfigModuleBlock("AT+RST\r\n","ready","OK");//��λ
}

