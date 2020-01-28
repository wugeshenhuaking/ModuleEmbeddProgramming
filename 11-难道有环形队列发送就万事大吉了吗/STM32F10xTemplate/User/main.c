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
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	GpioInit();
	DelayInit();
	
	rbCreate(&Uart1rb,Usart1SendBuff,Usart1SendLen);//�������ζ���--����1
	//�������ζ���--������ÿһ������
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
					PutData(&Uart1rb,temp,10);//����д�뻷�ζ���
					SendCount[0] = 10;//��η��͵����ݸ���
					PutData(&Uart1rbManage,SendCount,1);//����д�뻷�ζ���,��¼���Ҫ���͵����ݸ���
				}
			}
			
			PutData(&Uart1rb,temp1,15);//����д�뻷�ζ���
			SendCount[0] = 15;//��η��͵����ݸ���
			PutData(&Uart1rbManage,SendCount,1);//����д�뻷�ζ���,��¼���Ҫ���͵����ݸ���
		}

		
//		delay_ms(5000);
    if(Usart1ReadFlage)//���ڽ�����һ������������
		{
		  Usart1ReadFlage=0;
			PutData(&Uart1rb,temp,10);//����д�뻷�ζ���,Ȼ��򿪴���1�����жϷ���
			PutData(&Uart1rb,temp,10);//����д�뻷�ζ���,Ȼ��򿪴���1�����жϷ���
		
//			UsartOutStr(Usart1ReadBuff,Usart1ReadCntCopy);
			memset(Usart1ReadBuff,NULL, sizeof(Usart1ReadBuff));//����
		}
	}
}

