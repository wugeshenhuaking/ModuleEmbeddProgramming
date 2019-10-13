#ifndef __MAIN_H_
#define __MAIN_H_
#include <stm32f10x.h>

#ifndef __MAIN_C_
#define __MAIN_EXT_ extern
#else
#define __MAIN_EXT_
#endif

__MAIN_EXT_ char IP[20];//IP地址
__MAIN_EXT_ char Port[5];//端口号
__MAIN_EXT_ char PathVersionInfo[50];//版本信息路径

__MAIN_EXT_ u32 GetHttpCnt;

__MAIN_EXT_ char UpdataStartFlage;
__MAIN_EXT_ char UpdataReadEndFlage;

void Key(void);

#endif
