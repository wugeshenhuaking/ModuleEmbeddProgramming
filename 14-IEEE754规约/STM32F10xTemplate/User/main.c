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


Resolve_Typedef Resolve_Typedef1;

int main(void)
{
  NVIC_Configuration();
	uart_init(115200);	 //串口初始化为115200
	GpioInit();
	DelayInit();
	
//	Resolve_Typedef1.long_data = 65536;//要转换的数据
	
//	Resolve_Typedef1.float_data=220.5; //要转换的数据
//	//打印转换为16进制以后的数据
//	UsartOutChar(Resolve_Typedef1.char_table[0]);
//	UsartOutChar(Resolve_Typedef1.char_table[1]);
//	UsartOutChar(Resolve_Typedef1.char_table[2]);
//	UsartOutChar(Resolve_Typedef1.char_table[3]);
	
	
	Resolve_Typedef1.char_table[0] = 0x00;
	Resolve_Typedef1.char_table[1] = 0x80;
	Resolve_Typedef1.char_table[2] = 0x5c;
	Resolve_Typedef1.char_table[3] = 0x43;
	
	printf("Float=%f",Resolve_Typedef1.float_data);
	

	while(1);
	while(1)
	{
		
    if(Usart1ReadFlage)//串口接收到数据
		{
		  Usart1ReadFlage=0;
			UsartOutStr(Usart1ReadBuff,Usart1ReadCntCopy);
			memset(Usart1ReadBuff,NULL, sizeof(Usart1ReadBuff));//清零
		}
	}
}

