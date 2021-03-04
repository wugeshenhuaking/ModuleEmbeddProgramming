#ifndef FLASH_DATA_Cc_
#define FLASH_DATA_Cc_

#ifndef FLASH_DATA_Cx_//���û�ж���
#define FLASH_DATA_Cx_ extern
#else
#define FLASH_DATA_Cx_
#endif

#include "stm32f4xx_conf.h"

//����ת��
void flash_data_set_speed(u32 data);
//��ȡ���õ�ת��
u32 flash_data_get_speed(char mode);

//���ü���ֵ
void flash_data_set_count(u32 data);
//��ȡ���õļ���ֵ
u32 flash_data_get_count(char mode);


//����ˮλ0,ʪ��1,xxxֵ2,xxxxֵ3
void flash_data_set_water_humidity_xxx_xxxx(char type,char data);
//��ȡˮλ0,ʪ��1,xxxֵ2,xxxxֵ3
//����255,˵������
char flash_data_get_water_humidity_xxx_xxxx(char type,char mode);


//����һ�������1000�ֽڵ��ַ���
void flash_data_set_1000bytes(char *data,u32 data_len);
//��ȡһ���1000�ֽڵ��ַ���
//data �ĳ�����1000�ֽ�
void flash_data_get_1000bytes(char *data,char mode);


#endif
