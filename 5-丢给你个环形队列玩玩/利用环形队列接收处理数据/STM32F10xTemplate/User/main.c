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

u8 ReadDat[10];//���滷�ζ��ж���������
int len=0;//�鿴���ζ�����������ݸ���
int main(void)
{
  NVIC_Configuration();
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	GpioInit();
	DelayInit();
	
	rbCreate(&rb_test,rb_temp,20);//�����齻�����ζ���ȥ����
	
	while(1)
	{
		if(rbCanRead(&rb_test)>=10)//���ζ�����������ݸ������ڵ���10������
		{
			rbRead(&rb_test, &ReadDat, 10);//ȡ����10������
			printf("%d\r\n",ReadDat[0]+ReadDat[1]+ReadDat[2]+ReadDat[3]+ReadDat[4]+ReadDat[5]+ReadDat[6]+ReadDat[7]+ReadDat[8]+ReadDat[9]);
		}
		
    if(Usart1ReadFlage)//���ڽ�����һ������������
		{
		  Usart1ReadFlage=0;
			
			len = rbCanRead(&rb_test);
			if(len<10)
			{
				memset(ReadDat,0,20);//�����������ݱ�Ϊ0
				rbRead(&rb_test, &ReadDat, len);//������ʣ�������
				printf("%d\r\n",ReadDat[0]+ReadDat[1]+ReadDat[2]+ReadDat[3]+ReadDat[4]+ReadDat[5]+ReadDat[6]+ReadDat[7]+ReadDat[8]+ReadDat[9]);
			}
			
//			UsartOutStr(Usart1ReadBuff,Usart1ReadCntCopy);
			memset(Usart1ReadBuff,NULL, sizeof(Usart1ReadBuff));//����
		}
	}
}

