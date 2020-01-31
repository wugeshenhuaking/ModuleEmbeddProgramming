#ifndef __CRC_C_
#define __CRC_C_
#include "stm32f10x.h"

#ifndef __CRC_C_
#define __CRC_Cx_  extern
#else 
#define __CRC_Cx_
#endif

int crc16_modbus(u8 *modbusdata, int length);
int crc16_flage(u8 *modbusdata, int length);

#endif
