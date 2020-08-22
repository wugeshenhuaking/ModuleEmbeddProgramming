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

//char jsonValue1[50]="{\"datemcu\":\"updata\",\"cmd\":\"model\"}";
char jsonValue2[100]="{\"datemcu\":\"updata\",\"cmd\":{\"Id\":\"CH010100\",\"code\":\"001\"}}";
cJSON *root,*fmt;
char *jsonString;
int main(void)
{
  NVIC_Configuration();
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	GpioInit();
	DelayInit();
	rbCreate(&Uart1rb,Usart1SendBuff,Usart1SendLen);//�������ζ���--����1
	
	root=cJSON_CreateObject();	
	cJSON_AddItemToObject(root, "name", cJSON_CreateString("Jack (\"Bee\") Nimble"));
	cJSON_AddItemToObject(root, "format", fmt=cJSON_CreateObject());
	cJSON_AddStringToObject(fmt,"type",		"rect");
	cJSON_AddNumberToObject(fmt,"width",		1920);
	cJSON_AddNumberToObject(fmt,"height",		1080);
	cJSON_AddFalseToObject (fmt,"interlace");
	cJSON_AddNumberToObject(fmt,"frame rate",	24);
		
//	jsonString = cJSON_PrintUnformatted(root);//��ͨ��ʽ�ַ���
	jsonString = cJSON_Print(root);//�׶���ʽ���ַ���
	
  printf("%s",jsonString);
	delay_ms(1000);
	cJSON_Delete(root);//�ͷ��ڴ�
	free(jsonString);//�ͷ��ڴ�

	while(1)
	{
    if(Usart1ReadFlage)//���ڽ�����һ������������
		{
		  Usart1ReadFlage=0;
//			PutData(&Uart1rb,USART1,Usart1ReadBuff,Usart1ReadCntCopy);//����д�뻷�ζ���,Ȼ��򿪴���1�����жϷ���
			memset(Usart1ReadBuff,NULL, sizeof(Usart1ReadBuff));//����
		}
	}
}
