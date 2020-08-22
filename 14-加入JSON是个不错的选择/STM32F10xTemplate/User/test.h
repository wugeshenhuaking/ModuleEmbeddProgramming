#ifndef __TEST_H_
#define __TEST_H_          //防止重复编译
#include <stm32f10x.h>
#ifndef __TEST_C_          //如果没有定义 __TEST_C_
#define __TEST_C_ extern   // __TEST_C_ 代表 extern
#else                      //如果  定义了 __TEST_C_ 
#define __TEST_C_          //__TEST_C_  是空
#endif

__TEST_C_ char TestValue;

char add(char a,char b);//计算两个数的和 
	
#endif






