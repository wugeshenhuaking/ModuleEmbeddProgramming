/**
  ******************************************************************************
  * @author  yang feng wu 
  * @version V1.0.0
  * @date    2020/1/22
  * @brief   
  ******************************************************************************
	ʹ��˵��:https://www.cnblogs.com/yangfengwu/p/12228402.html
  ******************************************************************************
  */
#include "include.h"
#include "BufferManage.h"

//buff_manage_struct buff_manage_struct1;


u8  buff[1024];//�������ݵ�����
u32 Managebuff[10];//��¼ÿ�λ���������ݵ�����

//u8  SendBuff[1024];//��ȡһ������֮��洢������

char temp[17]="111111111111111\r\n";
char temp1[30]="000000000000000000000000000\r\n";

int main(void)
{
  NVIC_Configuration();
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	GpioInit();
	DelayInit();
	BufferManageCreate(&buff_manage_struct1, buff, 1024, Managebuff, 10*4);
	while(1)
	{	
		if(SysTickCntMs>=3000)
		{
			BufferManageWrite(&buff_manage_struct1,temp,17);//��������
			BufferManageWrite(&buff_manage_struct1,temp1,30);//��������
			SysTickCntMs=0;
		}

//		buff_manage_struct1.SendLen = BufferManageRead(&buff_manage_struct1,SendBuff);//��ȡ���ݵ�SendBuff����
//		if(buff_manage_struct1.SendLen>0)//��������Ҫ����
//		{
//			UsartOutStr(SendBuff,buff_manage_struct1.SendLen);
//			delay_ms(1000);
//		}
		
		
//    if(Usart1ReadFlage)//���ڽ�����һ������������
//		{
//		  Usart1ReadFlage=0;
//			memset(Usart1ReadBuff,NULL, sizeof(Usart1ReadBuff));//����
//		}
	}
}


