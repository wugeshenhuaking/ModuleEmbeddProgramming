#ifndef __TEST_H_
#define __TEST_H_          //��ֹ�ظ�����
#include <stm32f10x.h>
#ifndef __TEST_C_          //���û�ж��� __TEST_C_
#define __TEST_Ex_ extern   // __TEST_Ex_ ���� extern
#else                      //���  ������ __TEST_Ex_ 
#define __TEST_Ex_          //__TEST_Ex_  �ǿ�
#endif

__TEST_Ex_ char TestValue;

char add(char a,char b);//�����������ĺ� 
	
#endif






