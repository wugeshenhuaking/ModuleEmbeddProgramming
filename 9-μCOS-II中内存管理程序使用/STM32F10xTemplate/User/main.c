/**
  ******************************************************************************
  * @author  yang feng wu 
  * @version V1.0.0
  * @date    2019/12/30
  * @brief   
  ******************************************************************************
	Դ��˵��: https://www.cnblogs.com/yangfengwu/p/12246190.html
  ******************************************************************************
  */
#include "include.h"
#include "OS_MEM.h"

INT8U  buff[20][16];//�����ڴ����(20���ڴ��,ÿ���ڴ��16�ֽڴ�С)
INT8U  err;
OS_MEM *osmem;//�ڴ�ָ��
INT8U *BlkPtr;//�洢�ڴ��ָ��
INT8U data[16]="1111111111111111";

INT8U *BlkPtr1;//�洢�ڴ��ָ��
INT8U data1[10]="2222222222";

int main(void)
{
  NVIC_Configuration();
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	GpioInit();
	DelayInit();
	
	OSMemInit();//��ʼ��
	osmem = OSMemCreate(buff,20,16,&err);//����
	if(err!=0){printf("OSMemCreate err=%d",err);}
	
	BlkPtr = OSMemGet(osmem,&err);//�����ڴ��
	memcpy(BlkPtr,data,16);//��data������������ݿ�������������ڴ������
	
	BlkPtr1 = OSMemGet(osmem,&err);//�����ڴ��
	memcpy(BlkPtr1,data1,10);//��data1������������ݿ�������������ڴ������
	
	OSMemPut (osmem, BlkPtr);//�ͷ� BlkPtr �ڴ��
	while(1)
	{
		
	}
}

