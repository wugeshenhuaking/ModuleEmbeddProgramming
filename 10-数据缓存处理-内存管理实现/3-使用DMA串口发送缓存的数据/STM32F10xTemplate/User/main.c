/**
  ******************************************************************************
  * @author  yang feng wu 
  * @version V1.0.0
  * @date    2019/12/30
  * @brief   
  ******************************************************************************
	源码说明: https://www.cnblogs.com/yangfengwu/p/12238511.html
  ******************************************************************************
  */
#include "include.h"
#include "MemManage.h"


data_type_t CommTxPart[BlocksNumber][BlocksSize];

INT8U err;
char temp[17]="111111111111111\r\n";
char temp1[30]="0000000000000000000000000000\r\n";

int main(void)
{
  NVIC_Configuration();
	uart_init(115200);	 //串口初始化为115200
	GpioInit();
	DelayInit();
	MemManageCreate(&mem_manage_struct1,CommTxPart,BlocksNumber,BlocksSize,&err);
	if(err!=0){printf("MemManageCreate err=%d\r\n",err);}
	while(1)
	{
		if(SysTickCntMs>=3000)
		{
			MemManageWrite(&mem_manage_struct1,temp,17,&err);
			MemManageWrite(&mem_manage_struct1,temp1,30,&err);
			SysTickCntMs=0;
		}
		
		
//		Data = MemManageRead(&mem_manage_struct1,&DataLen);
//		if(DataLen>0)
//		{
//			UsartOutStr(Data,DataLen);
//			MemManageFree(&mem_manage_struct1);
//			delay_ms(500);
//		}
		
		
//    if(Usart1ReadFlage)//串口接收到数据
//		{
//		  Usart1ReadFlage=0;
//		}
	}
}

