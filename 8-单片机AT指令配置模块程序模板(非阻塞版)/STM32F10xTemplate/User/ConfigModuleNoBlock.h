#ifndef CONFIGMODULENOBLOCK_H_
#define CONFIGMODULENOBLOCK_H_
#include "stm32f10x.h"
#ifndef CONFIGMODULENOBLOCK_C_
#define CONFIGMODULENOBLOCK_C_  extern
#else 
#define CONFIGMODULENOBLOCK_C_
#endif

CONFIGMODULENOBLOCK_C_ u32 ConfigModuleNoBlockCnt;        //���ú�����ʱ����
CONFIGMODULENOBLOCK_C_ char ConfigModuleNoBlockFlage;     //1-������ 0-δ������
CONFIGMODULENOBLOCK_C_ int  ConfigModuleNoBlockCaseValue; //����ִ����һ��Case ���

CONFIGMODULENOBLOCK_C_ void (*ConfigConnectDispose)(char *data);//����һ������ָ�����,��������ģ�鷵�ص�����

void ConfigModuleNoBlock(void);

void FunctionParseCompare(char *data);//�Ա��ж��Ƿ񷵻���Ҫ������
void SendConfigFunction(char *order,void (*FunctionSend)(),char *HopeReturn1,char *HopeReturn2,void (*FunctionParse)(char *data),u32 ConfigFunctionValue);


#endif

