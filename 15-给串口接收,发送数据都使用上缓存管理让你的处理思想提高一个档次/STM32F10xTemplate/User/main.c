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


u8  buff[1024];//�������ݵ�����
u32 Managebuff[10];//��¼ÿ�λ���������ݵ�����

char temp[17]="111111111111111\r\n";
char temp1[30]="000000000000000000000000000\r\n";


u8  read_buff[1024];//���洮�ڽ��յ�ÿһ������
u32 read_manage_buff[10];//��¼ÿ�λ���������ݵ�����
u8  read_buff_copy[1024];//��ȡ�������ݵ�����

int main(void)
{
  NVIC_Configuration();
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	GpioInit();
	DelayInit();
	BufferManageCreate(&buff_manage_struct1, buff, 1024, Managebuff, 10*4);
	
	BufferManageCreate(&buff_manage_struct2, read_buff, 1024, read_manage_buff, 10*4);
	while(1)
	{	
		/*��������*/
		if(SysTickCntMs>=3000)
		{
			BufferManageWrite(&buff_manage_struct1,temp,17);//��������
			BufferManageWrite(&buff_manage_struct1,temp1,30);//��������
			SysTickCntMs=0;
		}

		/*�����������Ҫ������������*/
		if(buff_manage_struct1.SendLen>0)//��������Ҫ����
		{
			UsartOutStrIT(Usart1SendBuff,buff_manage_struct1.SendLen);
			buff_manage_struct1.SendLen=0;
		}
		
		
		//��ȡ���ڽ��յ�����
		buff_manage_struct2.ReadLen = BufferManageRead(&buff_manage_struct2,read_buff_copy);
		if(buff_manage_struct2.ReadLen>0){
			/*��������*/
			BufferManageWrite(&buff_manage_struct1,read_buff_copy,buff_manage_struct2.ReadLen);//��������
		}
		
		
//    if(Usart1ReadFlage)//���ڽ�����һ������������
//		{
//		  Usart1ReadFlage=0;
//			memset(Usart1ReadBuff,NULL, sizeof(Usart1ReadBuff));//����
//		}
	}
}


