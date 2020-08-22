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
			ConfigModuleNoBlockCnt++;
			
		2,�����³���ŵ�������
		while(1)
		{
			ConfigModuleNoBlock();//����ģ��
			if(���ڽ��յ�һ�����������ݱ�־)
			{
			  ���� ���ڽ��յ�һ�����������ݱ�־
				if(ConfigConnectDispose != NULL)
				{
					ConfigConnectDispose(Usart1ReadBuff);//����ģ�鷵�ص�����
				}
			}
		}
			
  ******************************************************************************
  */


#define CONFIGMODULENOBLOCK_C_
#include "include.h"

u32 ConfigModuleNoBlockCnt =0;        //���ú�����ʱ����,��ʱ���ڲ��ۼ�
int ConfigModuleNoBlockCaseValue = 0; //����ִ����һ��Case ���
char ConfigModuleNoBlockFlage  = 0;   //1-���������� 0-δ����������

u32 CompareValue=3000;                //ÿ�� Ms ����һ������
u32 SendNextDelay =0;                 //����SendConfigFunction�������һ������,���մ��ݸ� ConfigModuleNoBlockCnt ����дһ�����ݷ��͵�ʱ��
int Cnt = 0;                          //��¼����״̬���͵Ĵ���
char DataReturnFlage  = 0;            //�Ƿ񷵻���Ԥ�ڵ�����

char HopeReturnData1[20]="";//�洢ϣ�����ص�����
char HopeReturnData2[20]="";//�洢ϣ�����ص�����

void (*ConfigConnectDispose)(char *data);//����һ������ָ�����,��������ģ�鷵�ص�����

char MAC[20];            //�洢MAC��ַ
char SSID[10]="qqqqq";   //·��������
char PWD[10]="11223344"; //·��������
//����·����
void ConnectRouter(void)
{
char temp[100];
sprintf(temp,"AT+CWJAP_DEF=\"%s\",\"%s\"\r\n",SSID,PWD);
printf("%s",temp);
}


/**
* @brief  ��ȡ�豸MAC
* @param  data
* @param  
* @retval 
* @example 
**/
void FunctionParseGetMac(char *data)
{
	char *Str;
	int Len;
	memset(MAC,0,strlen(MAC));
	
	//��ȡMAC_CUR:"  �� " ֮����ַ���
	Str = StrBetwString(data,"MAC_CUR:\"","\"");//+CIPSTAMAC_CUR:"dc:4f:22:10:b8:fc"
	cStringFree();//�ͷ�cString���������ڴ�
	if((Str!=NULL) && strlen(Str) == 17)//��ȡ������
	{
		sprintf(MAC,"%s",Str);//��������
		split(Str,":",NULL,&Len);//�ָ�dc:4f:22:10:b8:fc
		if(Len == 6)//�ָ�����ִ�Ϊ6
		{
			//����ȷ�����ݿ��Է�����һ������(���³���̶�)
			DataReturnFlage=1;
			ConfigModuleNoBlockCnt = (SendNextDelay == 0 ? ConfigModuleNoBlockCnt:SendNextDelay);
		}
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
			case 0://��Ƭ������AT+RST\r\n  �����Ƭ�����ڽ��յ�OK ����ready ִ����һ��
				SendConfigFunction("AT+RST\r\n",NULL,"OK","ready",FunctionParseCompare,CompareValue);break;
			case 1://�˳�͸��
				SendConfigFunction("+++",NULL,"+++",NULL,FunctionParseCompare,CompareValue);break;
			case 2://�ָ���������
				SendConfigFunction("AT+RESTORE\r\n",NULL,NULL,"ready",FunctionParseCompare,CompareValue);break;
			case 3://ģʽ1
				SendConfigFunction("AT+CWMODE_DEF=1\r\n",NULL,"OK",NULL,FunctionParseCompare,CompareValue);break;
			case 4://�Զ�����·����
				SendConfigFunction("AT+CWAUTOCONN=1\r\n",NULL,"OK",NULL,FunctionParseCompare,CompareValue);break;
			case 5://����·����         ִ�к���                                                       0:��һ������������
				SendConfigFunction(NULL,ConnectRouter,"WIFI CONNECTED","WIFI GOT IP",FunctionParseCompare,0);break;
			case 6://��λ
				ConfigModuleNoBlockCaseValue++;//�����������ָ���Ҫ�˿���������
//				SendConfigFunction("AT+RST\r\n",NULL,"OK","ready",FunctionParseCompare,CompareValue);break;
			case 7://��ȡMAC                                              ִ��MAC��������
				SendConfigFunction("AT+CIPSTAMAC_CUR?\r\n",NULL,NULL,NULL,FunctionParseGetMac,CompareValue);break;
			case 8://����TCP������                                            
				SendConfigFunction("AT+CIPSTART=\"TCP\",\"mnif.cn\",1883\r\n",NULL,"CONNECT","ALREADY CONNECTED",FunctionParseCompare,CompareValue);break;
			default: 
				SendConfigFunction(NULL,NULL,NULL,NULL,NULL,CompareValue);//�������,������е�ִ�к���
				printf("�������!\r\n");
				printf("MAC��ַ:%s\r\n",MAC);
				DataReturnFlage=0; 
				ConfigModuleNoBlockFlage=1; break;
		}
	}
}


/**
* @brief  ��������ָ���
* @param  order          ��������(�ַ���)
* @param  FunctionSend   ��������(���з������ݺ���)
* @param  HopeReturn1    ��������(ϣ�����ص��ַ���1)
* @param  HopeReturn2    ��������(ϣ�����ص��ַ���2)
* @param  FunctionParse  ���ݴ�����
* @param  ConfigFunctionValue  ������һ�����ݵķ���ʱ��,ȡֵΪ ConfigFunctionCntCom:��һ����������
* @retval 
* @example 
**/
void SendConfigFunction(char *order,void (*FunctionSend)(),char *HopeReturn1,char *HopeReturn2,void (*FunctionParse)(char *data),u32 ConfigFunctionValue)
{
	memset(HopeReturnData1,NULL,strlen(HopeReturnData1));
	memset(HopeReturnData2,NULL,strlen(HopeReturnData2));
	if(HopeReturn1!=NULL)  sprintf(HopeReturnData1,"%s",HopeReturn1);//�������ݵ����� HopeReturn1,ϣ�����ص�����1
	if(HopeReturn2!=NULL)  sprintf(HopeReturnData2,"%s",HopeReturn2);//�������ݵ����� HopeReturn1,ϣ�����ص�����2
	if(FunctionSend!=NULL) FunctionSend();//����һ����������ָ��
	
	ConfigConnectDispose = FunctionParse;//���ݴ�����ָ��
	SendNextDelay = ConfigFunctionValue;//�����һ�����ݴ���ɹ�,���Ʒ�����һ�����ݵ�ʱ��
	
	if(order!=NULL)printf("%s",order);//ֱ�ӷ�������
}


/**
* @brief  �������÷�������:�ж��Ƿ񷵻���Ҫ������
* @param  data
* @param  
* @retval 
* @example 
**/
void FunctionParseCompare(char *data)
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


