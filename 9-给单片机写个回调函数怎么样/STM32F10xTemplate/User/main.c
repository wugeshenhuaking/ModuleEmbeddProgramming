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
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	GpioInit();
	DelayInit();
	rbCreate(&Uart1rb,Usart1SendBuff,Usart1SendLen);//�������ζ���--����1
	UsartCallBackReg(UsartCallBackFun);//��UsartCallBackFun��������ȥ
	while(1)
	{
    if(Usart1ReadFlage)//���ڽ�����һ������������
		{
		  Usart1ReadFlage=0;
//			PutData(&Uart1rb,USART1,Usart1ReadBuff,Usart1ReadCntCopy);//����д�뻷�ζ���,Ȼ��򿪴���1�����жϷ���
			
			printf("addValue = %d",addValue);
			addValue=0;
			memset(Usart1ReadBuff,NULL, sizeof(Usart1ReadBuff));//����
		}
	}
}
void UsartCallBackFun(char data)
{
	addValue = addValue + data;//���㴫����������֮��
}
