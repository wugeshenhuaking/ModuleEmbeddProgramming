#ifndef __TEST_H_
#define __TEST_H_          //��ֹ�ظ�����
#include <stm32f10x.h>
#ifndef __TEST_C_          //���û�ж��� __TEST_C_
#define __TEST_C_ extern   // __TEST_C_ ���� extern
#else                      //���  ������ __TEST_C_ 
#define __TEST_C_          //__TEST_C_  �ǿ�
#endif

__TEST_C_ char TestValue;

char add(char a,char b);//�����������ĺ� 
	
#endif






