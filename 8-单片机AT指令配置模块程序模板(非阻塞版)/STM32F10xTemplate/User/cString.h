#ifndef CSTRING_H_
#define CSTRING_H_
#include <stm32f10x.h>
#ifndef CSTRING_C_//���û�ж���
#define CSTRING_C_ extern
#else
#define CSTRING_C_
#endif

void cStringFree(void);
char *StrBetwString(char *Str,char *StrBegin,char *StrEnd);
void split(char *src,const char *separator,char **dest,int *num);

#endif

