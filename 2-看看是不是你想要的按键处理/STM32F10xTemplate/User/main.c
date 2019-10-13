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


int main(void)
{
  NVIC_Configuration();
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	GpioInit();
	DelayInit();
	
	while(1)
	{
		SmartConfigKey();
		//��2:��⵽��������,Ȼ����ݰ���ʱ��ִ��ĳ�δ���
		if(KeySmartConfig[3] == 1)
		{
			if(KeySmartConfig[5]>=3000)//����ʱ�����3S
			{
				KeySmartConfig[3] = 0;//�����Ժ�,ֻ�а����ɿ��ٰ��µ�ʱ��Ż����
				printf("��������ʱ�䳬��3S\r\n");
			}
		}
		
		//��3:��⵽�����ɿ�ִ��ĳ�δ���
		if(KeySmartConfig[4] == 1)
		{
			KeySmartConfig[4] = 0;//�����Ժ�,ֻ�а�������Ȼ���ɿ���ʱ��Ż����
			printf("�����ɿ�\r\n");
		}
		
		
    if(Usart1ReadFlage)//���ڽ��յ�����
		{
		  Usart1ReadFlage=0;
			UsartOutStr(Usart1ReadBuff,Usart1ReadCntCopy);
			memset(Usart1ReadBuff,NULL, sizeof(Usart1ReadBuff));//����
		}
	}
}

