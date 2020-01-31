/**
  ******************************************************************************
  * @author  yang feng wu 
  * @version V1.0.0
  * @date    2019/12/30
  * @brief   
  ******************************************************************************
	源码说明: https://www.cnblogs.com/yangfengwu/p/12246190.html
  ******************************************************************************
  */
#include "include.h"
#include "OS_MEM.h"

INT8U  buff[20][16];//定义内存分区(20个内存块,每个内存块16字节大小)
INT8U  err;
OS_MEM *osmem;//内存指针
INT8U *BlkPtr;//存储内存块指针
INT8U data[16]="1111111111111111";

INT8U *BlkPtr1;//存储内存块指针
INT8U data1[10]="2222222222";

int main(void)
{
  NVIC_Configuration();
	uart_init(115200);	 //串口初始化为115200
	GpioInit();
	DelayInit();
	
	OSMemInit();//初始化
	osmem = OSMemCreate(buff,20,16,&err);//创建
	if(err!=0){printf("OSMemCreate err=%d",err);}
	
	BlkPtr = OSMemGet(osmem,&err);//申请内存块
	memcpy(BlkPtr,data,16);//把data数组里面的数据拷贝到新申请的内存块里面
	
	BlkPtr1 = OSMemGet(osmem,&err);//申请内存块
	memcpy(BlkPtr1,data1,10);//把data1数组里面的数据拷贝到新申请的内存块里面
	
	OSMemPut (osmem, BlkPtr);//释放 BlkPtr 内存块
	while(1)
	{
		
	}
}

