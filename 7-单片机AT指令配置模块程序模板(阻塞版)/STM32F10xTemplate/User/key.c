/**
  ******************************************************************************
  * @file    key.c
  * @author  fengwu yang
  * @version V1.0.0
  * @date    2019/10/12
  * @brief   �������ģ��
  ******************************************************************************
  һ,ʹ��˵��:�������(PB5)
		1,�����³������1ms��ʱ���ж���
			if(KeySmartConfig[1])
				KeySmartConfig[5]++;
			else
				KeySmartConfig[5]=0;

			if(KeySmartConfig[2])
				KeySmartConfig[6]++;
			else
				KeySmartConfig[6]=0;
		
		2,��ѭ������ʹ��
			while(1)
			{
				SmartConfigKey();
				
				//��1:��⵽��������ִ��ĳ�δ���
				if(KeySmartConfig[3] == 1)
				{
					KeySmartConfig[3] = 0;//�����Ժ�,ֻ�а����ɿ��ٰ��µ�ʱ��Ż����
					//ִ�еĴ���
				}

				//��2:��⵽��������,Ȼ����ݰ���ʱ��ִ��ĳ�δ���
				if(KeySmartConfig[3] == 1)
				{
					if(KeySmartConfig[5]>=3000)//����ʱ�����3S
					{
						KeySmartConfig[3] = 0;//�����Ժ�,ֻ�а����ɿ��ٰ��µ�ʱ��Ż����
						//ִ�еĴ���
					}
				}
				
				//��3:��⵽�����ɿ�ִ��ĳ�δ���
				if(KeySmartConfig[4] == 1)
				{
					KeySmartConfig[4] = 0;//�����Ժ�,ֻ�а�������Ȼ���ɿ���ʱ��Ż����
					//ִ�еĴ���
				}
				
				//��4:��⵽�����ɿ�,Ȼ������ɿ�ʱ��ִ��ĳ�δ���
				if(KeySmartConfig[4] == 1)
				{
					if(KeySmartConfig[6]>=3000)//�ɿ�ʱ�����3S
					{
						KeySmartConfig[4] = 0;//�����Ժ�,ֻ�а����������ɿ���ʱ��Ż����
						//ִ�еĴ���
					}
				}
			}
  ******************************************************************************
  */

#define __KEY_C_
#include "include.h"

int KeySmartConfig[7]={0};//�������� ���±�� �ɿ���� ���±�ǿ���  �ɿ���ǿ��� ����ʱ��(Ms) �ɿ�ʱ��(Ms)
	
/**
* @brief  ��������
* @param  
* @param  None
* @param  None
* @retval None
* @example 
**/
void SmartConfigKey(void)
{
  if(SmartConfigKeyPinIn == KeySmartConfigDown)
	{
		if(KeySmartConfig[1] == 0)
		{
			KeySmartConfig[0]++;
			if(KeySmartConfig[0]>=500)//�����Ժ����
			{
				KeySmartConfig[0] = 0;//Cnt
				KeySmartConfig[2] = 0;//UP
				KeySmartConfig[1] = 1;//Down
				KeySmartConfig[3] = 1;//DownCopy
				KeySmartConfig[4] = 0;//UpCopy
			}
		}
	}
	else
	{
		KeySmartConfig[0]++;
		if(KeySmartConfig[0]>2000)
		{
			KeySmartConfig[0]=0;
			if(KeySmartConfig[1]==1)//���º��ɿ������
			{
				KeySmartConfig[2] = 1;//UP
				KeySmartConfig[1] = 0;//Down
				KeySmartConfig[3] = 0;//DownCopy
				KeySmartConfig[4] = 1;//UpCopy
			}
		}
	}
}
