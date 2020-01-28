#define __CRC_C_
#include "include.h"
#include "crc.h"


/**
* @brief  calculate CRC
* @param  *modbusdata: Source data address
* @param  length: data length
* @param  
* @retval CRC16 Value
* @example 
**/
int crc16_modbus(u8 *modbusdata, int length)
{
	int i, j;
	int crc = 0xffff;//0xffff or 0
	for (i = 0; i < length; i++)
	{
		crc ^= modbusdata[i]&0xff;
		for (j = 0; j < 8; j++)
		{
			if ((crc & 0x01) == 1)
			{
				crc = (crc >> 1) ^ 0xa001;
			}
			else
			{
				crc >>= 1;
			}
		}
	}
	
	return crc;
}


/**
* @brief  check CRC for data
* @param  *modbusdata:  Read data address
* @param  length: Read data length
* @param  
* @retval 1:CRC16 OK
* @example 
**/
int crc16_flage(u8 *modbusdata, int length)
{
	int Receive_CRC=0,calculation=0;
	if(length<=2)
	{
		return 0;
	}
	Receive_CRC = crc16_modbus(modbusdata, length-2);
	calculation = modbusdata[length-2];
	calculation <<= 8;
	calculation += modbusdata[length-1];
	if(calculation != Receive_CRC)
	{
		return 0;
	}
	return 1;
}



