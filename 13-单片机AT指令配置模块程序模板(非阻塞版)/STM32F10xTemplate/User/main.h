#ifndef __MAIN_H_
#define __MAIN_H_
#include <stm32f10x.h>

#ifndef __MAIN_C_
#define __MAIN_EXT_ extern
#else
#define __MAIN_EXT_
#endif

#define main_buff_len 500

__MAIN_EXT_ char main_buff[main_buff_len];
__MAIN_EXT_ int  main_len;

#endif
