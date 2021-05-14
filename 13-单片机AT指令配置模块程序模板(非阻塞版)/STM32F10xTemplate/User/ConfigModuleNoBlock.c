/**
  ******************************************************************************
  * @file    usart.c
  * @author  fengwu yang
  * @version V1.0.0
  * @date    2019/10/12
  * @brief   https://www.cnblogs.com/yangfengwu/p/11674814.html
  ******************************************************************************
	һ,ʹ��˵��
		1,�����³������1ms��ʱ���ж���
			ConfigModuleNoBlockCnt++;
			
		2,�����³���ŵ�������
		while(1)
		{
			ConfigModuleNoBlock();//����ģ��
			
			if(���ڽ��յ�һ������������)
			{
				if(ConfigConnectDispose != NULL){
					ConfigConnectDispose(���յ����ݵ�ַ,���յ����ݸ���);
				}
			}
		}
			
  ******************************************************************************
  */


#define CONFIGMODULENOBLOCK_C_
#include <stdio.h>
#include <string.h>
#include "ConfigModuleNoBlock.h"
#include "usart.h"
#include "main.h"


u32 ConfigModuleNoBlockCnt =0xFFFFFFFF;   //���ú�����ʱ����,��ʱ���ڲ��ۼ�
int ConfigModuleNoBlockCaseValue = 0; //����ִ����һ��Case ���
char ConfigModuleNoBlockFlage  = 0;   //1-���������� 0-δ����������

u32 CompareValue=5000;                //ÿ�� Ms ����һ������
u32 SendNextDelay =0;                 //����SendConfigFunction�������һ������,���մ��ݸ� ConfigModuleNoBlockCnt ����дһ�����ݷ��͵�ʱ��
int Cnt = 0;                          //��¼����״̬���͵Ĵ���
char DataReturnFlage  = 0;            //�Ƿ񷵻���Ԥ�ڵ�����

char HopeReturnData1[20]="";//�洢ϣ�����ص�����
char HopeReturnData2[20]="";//�洢ϣ�����ص�����

void (*ConfigConnectDispose)(char *data,int len);//����һ������ָ�����,��������ģ�鷵�ص�����
void ConfigModuleRunNext(int delay);
/*********************************************************************************************************/

void FunctionParseSendAT(void){
	UsartOutStr(USART1,"AT\r\n",strlen("AT\r\n"));//���͵�����
}

void FunctionParseGetID(char *data,int len){
	/*data:ģ�鷵�ص�����; len:���ص����ݳ���*/
	if(strstr(data, "OK"))//�������ж�,��������ȡ����,��ֻ�Ǿٸ�����
	{
		//�жϻ�����ȡ����Ժ�д��������仰
		ConfigModuleRunNext(CompareValue);//����ִ����һ�� case���
	}
}

/**
* @brief  ����ָ������ģ��,��������
* @waring 
* @param  None 
* @param  None
* @param  None
* @retval None
* @example 
**/
void ConfigModuleNoBlock(void)
{
	if(ConfigModuleNoBlockCnt>CompareValue && ConfigModuleNoBlockFlage==0)
	{
		ConfigModuleNoBlockCnt=0;
		if(DataReturnFlage == 1)//��һ��ָ����OK��
		{
			Cnt=0;
			DataReturnFlage = 0;
			ConfigModuleNoBlockCaseValue ++;//ִ����һ��
		}
		else
		{
			Cnt ++;
			if(Cnt>=3)//����3������ִ��
			{
				Cnt=0;
				ConfigModuleNoBlockCaseValue = 0;
			}
		}
		switch(ConfigModuleNoBlockCaseValue)
		{
			case 0:
					SendConfigFunction("AT\r\n",NULL,"OK",NULL,FunctionParseCompare,CompareValue);
				break;
			case 2://��Ҫ��ѵ���
				SendConfigFunction(NULL,NULL,NULL,NULL,NULL,CompareValue);//���,��ֹ����
				break;
			default: 
				SendConfigFunction(NULL,NULL,NULL,NULL,NULL,CompareValue);
				DataReturnFlage=0; 
				ConfigModuleNoBlockFlage=1; break;
		}
	}
	
	if(ConfigModuleNoBlockCaseValue == 2)
	{
		if(!DataReturnFlage)
		{
			/*��д�Լ���ִ�к���*/
			if(/*ִ�гɹ�*/1){
				ConfigModuleRunNext(CompareValue);//����ִ����һ�� case���
			}
		}
	}
}


/**
* @brief  ִ����һ��
* @param  delay ��ʱ����ʱ����ִ����һ��
* @param  
* @retval 
* @example 
��ʱ500ms��ִ����һ�� case ���,(ע��,�����ʱΪ CompareValue)
ConfigModuleRunNext(CompareValue-500);
����ִ����һ�� case���
ConfigModuleRunNext(CompareValue);//����ִ����һ�� case���
**/
void ConfigModuleRunNext(int delay){
	SendNextDelay = delay;
	DataReturnFlage=1;
	ConfigModuleNoBlockCnt = (SendNextDelay == 0 ? ConfigModuleNoBlockCnt:SendNextDelay);
}


/**
* @brief  ��������ָ���
* @param  order          ��������(�ַ���)
* @param  FunctionSend   ��������(���з������ݺ���)
* @param  HopeReturn1    ��������(ϣ�����ص��ַ���1)
* @param  HopeReturn2    ��������(ϣ�����ص��ַ���2)
* @param  FunctionParse  ���ݴ�����
* @param  ConfigFunctionValue  ������һ�����ݵķ���ʱ��,ȡֵΪ CompareValue:��һ����������
* @retval 
* @example 
**/
void SendConfigFunction(char *order,void (*FunctionSend)(),char *HopeReturn1,char *HopeReturn2,void (*FunctionParse)(char *data,int len),u32 ConfigFunctionValue)
{
	memset(HopeReturnData1,NULL,strlen(HopeReturnData1));
	memset(HopeReturnData2,NULL,strlen(HopeReturnData2));
	if(HopeReturn1!=NULL)  sprintf(HopeReturnData1,"%s",HopeReturn1);//�������ݵ����� HopeReturn1,ϣ�����ص�����1
	if(HopeReturn2!=NULL)  sprintf(HopeReturnData2,"%s",HopeReturn2);//�������ݵ����� HopeReturn1,ϣ�����ص�����2
	if(FunctionSend!=NULL) FunctionSend();//����һ����������ָ��
	
	ConfigConnectDispose = FunctionParse;//���ݴ�����ָ��
	SendNextDelay = ConfigFunctionValue;//�����һ�����ݴ���ɹ�,���Ʒ�����һ�����ݵ�ʱ��
	
	if(order!=NULL){
		/*���ݺ�ģ��ͨ�ŵĶ˿��滻����ķ������ݺ���*/
		//order Ҫ���͵�ָ��  strlen(order):���͵�ָ���
		UsartOutStr(USART1,(unsigned char*)order,strlen(order));//���͵�����
	}
}


/**
* @brief  �������÷�������:�ж��Ƿ񷵻���Ҫ������
* @param  data
* @param  
* @retval 
* @example 
**/
void FunctionParseCompare(char *data,int len)
{
	if(strlen(HopeReturnData1) != 0 && strstr(data, HopeReturnData1))
	{
		DataReturnFlage=1;
		ConfigModuleNoBlockCnt = (SendNextDelay == 0 ? ConfigModuleNoBlockCnt:SendNextDelay);
	}
	if(strlen(HopeReturnData2) != 0 && strstr(data, HopeReturnData2))
	{
		DataReturnFlage=1;
		ConfigModuleNoBlockCnt = (SendNextDelay == 0 ? ConfigModuleNoBlockCnt:SendNextDelay);
	}
}



























