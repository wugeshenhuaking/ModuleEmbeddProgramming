/**
  ******************************************************************************
  * @file    usart.c
  * @author  fengwu yang
  * @version V1.0.0
  * @date    2019/10/12
  * @brief   
  ******************************************************************************
	һ,ʹ��˵��
		1,�����³������1ms��ʱ���ж���
			ConfigModuleBlockDelay++;
		2,ʹ��
		//ʹ��printf����AT\r\n,ϣ�����ڷ��ص������� OK,
		ConfigModuleBlock("AT\r\n","OK",NULL) //�жϷ�����OK,���߸�ָ�����3��,ִ����һ��
		
		//ʹ��printf����AT+RST\r\n,ϣ�����ڷ��ص������� OK,
		ConfigModuleBlock("AT+RST\r\n","ready","OK") //�жϷ�����OK,���߷�����"ready",���߸�ָ�����3��,ִ����һ��
		
		//���շ��ص�����״̬
		flage = ConfigModuleBlock("AT\r\n","OK",NULL);//flage:1  ����OK  
  ******************************************************************************
  */

#define CONFIGMODULEBLOCK_C_
#include "include.h"

int  ConfigModuleBlockCnt = 0;
int	 ConfigModuleBlockFlage = 1;
int  ConfigModuleBlockDelay=0;

/**
* @brief  ����ָ������ģ��,������
* @param  dat:      ���͵�����
* @param  returnc:  Ԥ�ڷ��ص�����1
* @param  returncc: Ԥ�ڷ��ص�����2
* @retval 1:���õ�ǰָ��OK
* @example 
**/
char ConfigModuleBlock(char *dat,char *returnc,char *returncc)
{
	ConfigModuleBlockCnt = 0;
	ConfigModuleBlockFlage = 1;
	while(1)
	{
		if(ConfigModuleBlockFlage == 1)//����ָ��
		{
			ConfigModuleBlockDelay = 0;
			memset(Usart1ReadBuff,NULL, sizeof(Usart1ReadBuff));//����,���Լ��Ĵ��ڽ������������������
			ConfigModuleBlockFlage = 0;
      printf("%s",dat);//����ָ��
    }
		if(Usart1ReadFlage == 1)//���ڽ��յ�һ������������
		{
      Usart1ReadFlage = 0;
			
			if(returnc!=NULL && strstr(Usart1ReadBuff,returnc))//�Ƚ�����
			{
				return 1;
			}
			if(returncc!=NULL && strstr(Usart1ReadBuff,returncc))//�Ƚ�����
			{
				return 1;
			}
    }
		if(ConfigModuleBlockDelay>=3000)//����3S
		{
			ConfigModuleBlockDelay = 0;
			ConfigModuleBlockFlage = 1;//����������
			ConfigModuleBlockCnt++;
		}
		if(ConfigModuleBlockCnt>=3)//�������μ���������һ��
		{
			ConfigModuleBlockCnt = 0;
			return 0;
		}
  }
}

