/**
  ******************************************************************************
  * @author  yang feng wu 
  * @version V1.0.0
  * @date    2020/1/22
  * @brief   
  ******************************************************************************
	使用说明:https://www.cnblogs.com/yangfengwu/p/12228402.html
  ******************************************************************************
  */
#include "include.h"
#include "BufferManage.h"

//buff_manage_struct buff_manage_struct1;


u8  buff[1024];//缓存数据的数组
u32 Managebuff[10];//记录每次缓存多少数据的数组

//u8  SendBuff[1024];//提取一条数据之后存储的数组

char temp[17]="111111111111111\r\n";
char temp1[30]="000000000000000000000000000\r\n";

int main(void)
{
  NVIC_Configuration();
	uart_init(115200);	 //串口初始化为115200
	GpioInit();
	DelayInit();
	BufferManageCreate(&buff_manage_struct1, buff, 1024, Managebuff, 10*4);
	while(1)
	{	
		if(SysTickCntMs>=3000)
		{
			BufferManageWrite(&buff_manage_struct1,temp,17);//插入数据
			BufferManageWrite(&buff_manage_struct1,temp1,30);//插入数据
			SysTickCntMs=0;
		}

//		buff_manage_struct1.SendLen = BufferManageRead(&buff_manage_struct1,SendBuff);//提取数据到SendBuff数组
//		if(buff_manage_struct1.SendLen>0)//有数据需要发送
//		{
//			UsartOutStr(SendBuff,buff_manage_struct1.SendLen);
//			delay_ms(1000);
//		}
		
		
//    if(Usart1ReadFlage)//串口接收完一条完整的数据
//		{
//		  Usart1ReadFlage=0;
//			memset(Usart1ReadBuff,NULL, sizeof(Usart1ReadBuff));//清零
//		}
	}
}


