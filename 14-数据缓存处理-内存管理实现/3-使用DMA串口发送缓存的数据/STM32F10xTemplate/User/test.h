#ifndef __TEST_H_
#define __TEST_H_          //防止重复编译
#include <stm32f10x.h>
#ifndef __TEST_C_          //如果没有定义 __TEST_C_
#define __TEST_Ex_ extern   // __TEST_Ex_ 代表 extern
#else                      //如果  定义了 __TEST_Ex_ 
#define __TEST_Ex_          //__TEST_Ex_  是空
#endif

__TEST_Ex_ char TestValue;

char add(char a,char b);//计算两个数的和 
	
#endif






