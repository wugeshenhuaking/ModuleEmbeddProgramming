#define _USART_C_
#include "include.h"

/**
* ����:  ���ں���
* ˵��:  ���ö�ʱ��2�ﵽ 115200 HZ
* ˵��:  �����ô����жϷ�������
* ˵��:  ���ö�ʱ�����˽��տ��м��
* ˵��:  None
* ֧��:  QQ946029359 --Ⱥ 607064330
* �Ա�:  https://shop411638453.taobao.com/
* ����:  С��
**/


bit UsartFlage = 0;
int UsartIdleCnt =0;
unsigned char  UsartReadCnt = 0;
unsigned char  UsartReadCntCopy = 0;
unsigned char  UsartReceive[ReadLength] = {0};

unsigned char *UsartSendData;
unsigned char UsartSendDataCnt;
char UsartSendDataCopy;

/**
* @brief  ���ڳ�ʼ������
* @param  
* @param  None
* @param  None
* @retval None
* @example 
**/
void InitUART(long Baud)
{
	if(Baud == 115200)
	{
    SCON=0x50; //���ڹ�����ʽ1��8λUART�������ʿɱ�  
		TH2=0xFF;           
		TL2=0xFD;    //������:115200 ����=11.0592MHz 
		RCAP2H=0xFF;   
		RCAP2L=0xFD; //16λ�Զ���װ��ֵ

		/*****************/
		TCLK=1;   
		RCLK=1;   
		C_T2=0;   
		EXEN2=0; //�����ʷ�����������ʽ
    
		/*****************/
		TR2=1 ; //��ʱ��2��ʼ
  }
	else
	{
		TMOD |= 0x20;
		SCON = 0x50;
    switch(Baud)
		{
      case 2400  :TH1 = 0xF4;TL1 = TH1;PCON = 0x00;break;
			case 4800  :TH1 = 0xFA;TL1 = TH1;PCON = 0x00;break;
			case 9600  :TH1 = 0xFD;TL1 = TH1;PCON = 0x00;break;
			case 14400 :TH1 = 0xFE;TL1 = TH1;PCON = 0x00;break;
			case 19200 :TH1 = 0xFD;TL1 = TH1;PCON = 0x80;break;
			default    :TH1 = 0xFD;TL1 = TH1;PCON = 0x00;break;
    }
		
	  TR1 = 1;
  }
	EA = 1;//���ж�
	ES = 1;//�����ж�
}

/**
* @brief  ���ڷ��ͺ���
* @param  value--���͵�����
* @param  None
* @param  None
* @retval None
* @example 
**/
void UartSend(unsigned char value) 
{
	ES=0;  //�رմ����ж�--ʹ��Printf ��Ҫ���� 
	TI=0;   //�巢������ж������־λ   
	SBUF=value; //����  
	while(TI==0); //�ȴ��������   
	TI=0;   //�巢������ж������־λ --ʹ��Printf ��Ҫ����   
	ES=1;  //�������ж�  --ʹ��Printf ��Ҫ���� 
}

/**
* @brief  ���ڷ��ͺ����жϷ���
* @param  *value--���ݵĵ�ַ
* @param  DataLen--���ݵĸ���
* @param  None
* @retval None
* @example 
**/
void UartSendTI(unsigned char *value,int DataLen) 
{
	UsartSendData = value;
	UsartSendDataCnt = DataLen;
	TI = 1;
}


/**
* @brief  �����жϺ���
* @param  
* @param  None
* @param  None
* @retval None
* @example 
**/
void UARTInterrupt(void) interrupt 4
{
	if(RI)
	{
		RI=0;
		UsartReceive[UsartReadCnt]=SBUF;//���մ�������
		UsartReadCnt++;
		if(UsartReadCnt>ReadLength-2)//��ֹ���
		{
			UsartReadCnt = 0;
    }
	}
	if(TI)
	{
		TI = 0;
		if(UsartSendDataCnt>0)
		{
      SBUF = *UsartSendData++;
		  UsartSendDataCnt--;
    }
		else
		{
      TI = 0;
    }
  }
}
/**
* @brief  ����˺�����ʹ��printf ��������
* @param  
* @param  None
* @param  None
* @retval None
* @example 
**/
char putchar(char c)  
{  
	UsartSendDataCopy = c;
	UartSendTI(&UsartSendDataCopy,1);
	return c;
}  

/*

//���´������Լ�д��printf���� 
void UartSendByte(unsigned char c)  
{  
    if(c=='\n')//�������\n�ͻ���  
    {  
        //����CR(carriage return)  
        SBUF=0x0D;   
        while(!TI);//�ȴ��������  
        TI=0;  
          
        //���� LF(NL line feed,new line)  
        SBUF=0x0A;   
        while(!TI);//�ȴ��������  
        TI=0;         
    }  
    else  
    {  
        SBUF=c;  
        while(!TI);//�ȴ��������  
        TI=0;  
    }  
}  

void sendstring(unsigned char *string)//�˴�*string�൱������  
{  
    while(*string!='\0')//�ж��Ƿ��ַ���ĩβ  
    {  
        UartSendByte(*string);  
        string++;  
    }  
}  
  
void uart_printf(const char *fmt,...)  
{ 
    va_list ap;  
    char xdata string[100];//�����ڲ���չRAM���Ƿ����ⲿRAM�����ܳ����ڲ���չRAM��С(�˴�Ϊ1024) 
      
    va_start(ap,fmt);  
    vsprintf(string,fmt,ap);//�˴�Ҳ����ʹ��sprintf�������÷���࣬�Լ��޸ļ��ɣ��˴���ȥ  
    sendstring(string);  
    va_end(ap);  
}  

*/