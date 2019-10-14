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

u8 ReadDat[10];//缓存环形队列读出的数据
int len=0;//查看环形队列里面的数据个数
int main(void)
{
  NVIC_Configuration();
	uart_init(115200);	 //串口初始化为115200
	GpioInit();
	DelayInit();
	
	rbCreate(&rb_test,rb_temp,20);//把数组交给环形队列去管理
	
	while(1)
	{
		if(rbCanRead(&rb_test)>=10)//环形队列里面的数据个数大于等于10个数据
		{
			rbRead(&rb_test, &ReadDat, 10);//取出来10个数据
			printf("%d\r\n",ReadDat[0]+ReadDat[1]+ReadDat[2]+ReadDat[3]+ReadDat[4]+ReadDat[5]+ReadDat[6]+ReadDat[7]+ReadDat[8]+ReadDat[9]);
		}
		
    if(Usart1ReadFlage)//串口接收完一条完整的数据
		{
		  Usart1ReadFlage=0;
			
			len = rbCanRead(&rb_test);
			if(len<10)
			{
				memset(ReadDat,0,20);//数组所有数据变为0
				rbRead(&rb_test, &ReadDat, len);//读出来剩余的数据
				printf("%d\r\n",ReadDat[0]+ReadDat[1]+ReadDat[2]+ReadDat[3]+ReadDat[4]+ReadDat[5]+ReadDat[6]+ReadDat[7]+ReadDat[8]+ReadDat[9]);
			}
			
//			UsartOutStr(Usart1ReadBuff,Usart1ReadCntCopy);
			memset(Usart1ReadBuff,NULL, sizeof(Usart1ReadBuff));//清零
		}
	}
}

