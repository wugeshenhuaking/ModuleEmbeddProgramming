#ifndef CONFIGMODULEBLOCK_H_
#define CONFIGMODULEBLOCK_H_

#include <stm32f10x.h>

#ifndef CONFIGMODULEBLOCK_C_//���û�ж���
#define CONFIGMODULEBLOCK_C_ extern
#else
#define CONFIGMODULEBLOCK_C_
#endif

CONFIGMODULEBLOCK_C_ int ConfigModuleBlockDelay;

char ConfigModuleBlock(char *dat,char *returnc,char *returncc);
#endif

