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
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	GpioInit();
	DelayInit();
	rbCreate(&Uart1rb,Usart1SendBuff,Usart1SendLen);//�������ζ���--����1
	
//	ConfigModuleNoBlockFlage = 1;//�������ú���ִ��
	
	while(1)
	{
		ConfigModuleNoBlock();//����ģ��
		if(Usart1ReadFlage)//���ڽ��յ�һ������
		{
			Usart1ReadFlage=0;
			if(ConfigConnectDispose != NULL)
			{
			  ConfigConnectDispose(Usart1ReadBuff);//����ģ�鷵�ص�����
			}
			
			if(ConfigModuleNoBlockFlage == 1)//һ��ʼ�����óɹ���
			{
				if(strstr(Usart1ReadBuff,"CLOSED"))//���յ�CLOSED,�豸���ӳ�������
				{
					ConfigModuleNoBlockFlage=0;
					ConfigModuleNoBlockCaseValue=0;
				}
			}
			memset(Usart1ReadBuff,0,Usart1ReadCntCopy);
		}
		
		
		if(maindelay>=500)//֤��������һֱ������
		{
			maindelay =0 ;
			PCout(13) = ~PCout(13);
		}
	}
}

