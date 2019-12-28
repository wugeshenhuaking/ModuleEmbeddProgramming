#ifndef __MAIN_H_
#define __MAIN_H_
#include <stm32f10x.h>

#ifndef __MAIN_C_
#define __MAIN_Ex_ extern
#else
#define __MAIN_Ex_
#endif



typedef union Resolve//STM32为小端模式
{
	float float_data;
	long  long_data;
	char  char_table[4];
}Resolve_Typedef;



void Key(void);

#endif
