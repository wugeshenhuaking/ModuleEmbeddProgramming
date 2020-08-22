/**
  ******************************************************************************
  * @file    key.c
  * @author  yang feng wu 
  * @version V1.0.0
  * @date    2019/10/13
  * @brief   �ַ���������
  ******************************************************************************

  ******************************************************************************
  */
#define CSTRING_C_
#include "include.h"

char *Str = NULL;
void cStringFree(void){
	free(Str);
}

/**
* @brief  ��ȡ�����ַ���֮����ַ���
* @param  Str  Դ�ַ���
* @param  StrBegin  ��ʼ���ַ���
* @param  StrEnd    �������ַ���
* @retval �ַ����׵�ַ
* @example  printf("%s",StrBetwString("wqe5w4ew46e5w","5w","6e"));cStringFree(Str);  ���:4ew4   
**/
char *StrBetwString(char *Str,char *StrBegin,char *StrEnd)
{
	char *StrStart=0,*StrStop=0,len=0;
	len = strlen(StrBegin);//�ַ�������
	
  StrStart=strstr(Str, StrBegin);//��һ���ַ�����ʼ�ĵ�ַ
	if(StrStart)
	{
	  StrStop = strstr(StrStart+len+1, StrEnd);//�ڶ����ַ�����ʼ�ĵ�ַ
		if(StrStop)
		{
			Str = (char *)malloc(((StrStop - (StrStart+len))+1) *sizeof(char));//�����һ���ռ�,��ֹ�������ݸ���
			
			memset(Str,NULL,(StrStop - (StrStart+len))+1);
			memcpy(Str, StrStart+len, (StrStop - (StrStart+len)));
		
			return Str;
		}
		else
		{
			return NULL;
		}
	}
	else
	{
	  return NULL;
	}
}



/**
* @brief  �ָ��ַ���
* @param  src        Դ�ַ���
* @param  separator  �ָ�
* @param  dest       �����Ӵ�������
* @param  num        ���ַ����ĸ���
* @retval None
* @example split("42,uioj,dk4,56",",",temp,&cnt);  temp[0]=42,...temp[3]=56  cnt=4
**/
void split(char *src,const char *separator,char **dest,int *num) 
{
	char *pNext;
	int count = 0;
	if (src == NULL || strlen(src) == 0)
		return;
	if (separator == NULL || strlen(separator) == 0)
		return;
	pNext = (char *)strtok(src,separator);
	while(pNext != NULL) 
	{
		if(dest != NULL)
		*dest++ = pNext;
		++count;
		pNext = (char *)strtok(NULL,separator);
	}  
	*num = count;
}
