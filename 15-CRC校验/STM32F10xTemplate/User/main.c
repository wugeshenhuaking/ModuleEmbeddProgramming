/**
  ******************************************************************************
  * @author  yang feng wu 
  * @version V1.0.0
  * @date    2019/12/30
  * @brief   
  ******************************************************************************
	
  ******************************************************************************
  */
#include "include.h"

char SendData[6]={0x01,0x00,0x55,0xaa};
int crc=0;
int main(void)
{
  NVIC_Configuration();
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	GpioInit();
	DelayInit();
	
	crc = crc16_modbus(SendData,4);
	SendData[4] = crc>>8; //CRC  high order
	SendData[5] = crc;//CRC low order
	
	UsartOutChar(SendData[0]);
	UsartOutChar(SendData[1]);
	UsartOutChar(SendData[2]);
	UsartOutChar(SendData[3]);
	UsartOutChar(SendData[4]);
	UsartOutChar(SendData[5]);
	
	while(1)
	{
    if(Usart1ReadFlage)//���ڽ��յ�����
		{
		  Usart1ReadFlage=0;
			
			if(crc16_flage(Usart1ReadBuff,Usart1ReadCntCopy))
			{
				printf("\r\n CRCУ����ȷ \r\n");
			}
			else
			{
				printf("\r\n CRCУ����� \r\n");
			}
			
//			UsartOutStr(Usart1ReadBuff,Usart1ReadCntCopy);
//			memset(Usart1ReadBuff,NULL, sizeof(Usart1ReadBuff));//����
		}
	}
}

