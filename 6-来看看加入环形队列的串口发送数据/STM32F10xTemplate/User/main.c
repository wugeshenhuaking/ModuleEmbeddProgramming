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
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	GpioInit();
	DelayInit();
	
	rbCreate(&Uart1rb,Usart1SendBuff,Usart1SendLen);//�������ζ���--����1
	while(1)
	{
		PutData(&Uart1rb,USART1,temp,10);//����д�뻷�ζ���,Ȼ��򿪴���1�����жϷ���
		PutData(&Uart1rb,USART1,temp,10);//����д�뻷�ζ���,Ȼ��򿪴���1�����жϷ���

		delay_ms(10);
    if(Usart1ReadFlage)//���ڽ�����һ������������
		{
		  Usart1ReadFlage=0;
			PutData(&Uart1rb,USART1,temp,10);//����д�뻷�ζ���,Ȼ��򿪴���1�����жϷ���
			PutData(&Uart1rb,USART1,temp,10);//����д�뻷�ζ���,Ȼ��򿪴���1�����жϷ���
		
//			UsartOutStr(Usart1ReadBuff,Usart1ReadCntCopy);
			memset(Usart1ReadBuff,NULL, sizeof(Usart1ReadBuff));//����
		}
	}
}

