#define __TEST_C_     //__文件名字大写_C_      前后加__ _C_ 防止有重名
#include "include.h"

char TestValue = 0;

/**
* @brief   计算两个数的和 
* @param   a:第一个数
* @param   b:第二个数
* @param   None
* @retval  两个数的和
* @warning
* @example 
**/
char add(char a,char b)//计算两个数的和 
{
  return a+b;
}
