#define FLASH_DATA_C_

#include "flash_data.h"
#include <string.h>
#include "flash_helper.h"
#include "data_parse.h"

/**
��¼����Щλ�ô洢����Щ����.һ�������ռ��4���ֽ�(���ֽ�,�����ֽ�,�����ֽ�,���ֽ�)
**/
/**����ֻ�Ǿ�����.
����ת��: flash_helper_struct.FlashHelperData[0] ȫ��ʹ��
���ü���ֵ: flash_helper_struct.FlashHelperData[1] ȫ��ʹ��
flash_helper_struct.FlashHelperData[2] ˮλֵ,ʪ��ֵ,XXXֵ,XXXֵ,��ռһ���ֽ�

��¼һ�������1000�ֽڵ��ַ���
��3��252��250��u32 Ҳ����1000�ֽ�
flash_helper_struct.FlashHelperData[3] - flash_helper_struct.FlashHelperData[252] 
**/

//����һ�������1000�ֽڵ��ַ���
void flash_data_set_1000bytes(char *data,u32 data_len)
{
	//���
	memset(&flash_helper_struct.FlashHelperData[3],0,1000);
	//����
	memcpy(&flash_helper_struct.FlashHelperData[3],data,data_len);
}

//��ȡһ�������1000�ֽڵ��ַ���
//data �ĳ�����1000�ֽ�
void flash_data_get_1000bytes(char *data,char mode)
{
	if(mode) flash_helper_get(3,(u32*)data,250); //��falsh�����ȡ
	else memcpy(data,&flash_helper_struct.FlashHelperData[3],1000);
}


//����ˮλ0,ʪ��1,xxxֵ2,xxxxֵ3
void flash_data_set_water_humidity_xxx_xxxx(char type,char data)
{
	/*�Ȱ����������ȫ����ȡ����*/
	union_resolve_value.u32_data = flash_helper_struct.FlashHelperData[2];
	if(type==0){//����ˮλ
		union_resolve_value.char_table[0] = data;/*�����޸���ˮλ*/
	}
	else if(type==1){//����ʪ��
		union_resolve_value.char_table[1] = data;/*�����޸���ʪ��*/
	}
	else if(type==2){//����xxxֵ
		union_resolve_value.char_table[2] = data;/*�����޸���xxxֵ*/
	}
	else if(type==3){//����xxxxֵ
		union_resolve_value.char_table[3] = data;/*�����޸���xxxxֵ*/
	}
	/*����������ȫ������*/
	flash_helper_struct.FlashHelperData[2] = union_resolve_value.u32_data;
}

//��ȡˮλ0,ʪ��1,xxxֵ2,xxxxֵ3
//����255,˵������
char flash_data_get_water_humidity_xxx_xxxx(char type,char mode)
{	
	u32 value;
	if(mode) flash_helper_get(2,&value,1); //��falsh�����ȡ
	else value = flash_helper_struct.FlashHelperData[2];
	
	/*ת��*/
	union_resolve_value.u32_data = value;
	
	if(type==0) return union_resolve_value.char_table[0]; //ˮλ
	else if(type==1)return union_resolve_value.char_table[1];//ʪ��
	else if(type==2)return union_resolve_value.char_table[2];//xxxֵ
	else if(type==3)return union_resolve_value.char_table[3];//xxxxֵ
	else return 255;
}


//����ת��
void flash_data_set_speed(u32 data)
{
	flash_helper_struct.FlashHelperData[0] = data;
}

//��ȡ���õ�ת��
u32 flash_data_get_speed(char mode)
{
	u32 value;
	if(mode){//��falsh�����ȡ
		flash_helper_get(0,&value,1);
	}
	else{
		value = flash_helper_struct.FlashHelperData[0];
	}
	return value;
}

//���ü���ֵ
void flash_data_set_count(u32 data)
{
	flash_helper_struct.FlashHelperData[1] = data;
}

//��ȡ���õļ���ֵ
u32 flash_data_get_count(char mode)
{
	u32 value;
	if(mode){//��falsh�����ȡ
		flash_helper_get(1,&value,1);
	}
	else{
		value = flash_helper_struct.FlashHelperData[1];
	}
	return value;
}






//void flash_data_set_bytes(char data)
//{
//	char temp[4];
//	/*��ȡ��ǰ������*/
//	temp[0] = flash_helper_struct.FlashHelperData[0]>>24&0x000000ff;
//	temp[1] = flash_helper_struct.FlashHelperData[0]>>16&0x000000ff;
//	temp[2] = flash_helper_struct.FlashHelperData[0]>>8&0x000000ff;
//	temp[3] = flash_helper_struct.FlashHelperData[0]&0x000000ff;
//	
//	/*�ı����е�һ��ֵ,�������*/
//	temp[0] = data;
//	
//	flash_helper_struct.FlashHelperData[0] = temp[0];
//	flash_helper_struct.FlashHelperData[0] = flash_helper_struct.FlashHelperData[0] <<8;
//	
//	flash_helper_struct.FlashHelperData[0] = flash_helper_struct.FlashHelperData[0] + temp[1];
//	flash_helper_struct.FlashHelperData[0] = flash_helper_struct.FlashHelperData[0] <<8;
//	
//	flash_helper_struct.FlashHelperData[0] = flash_helper_struct.FlashHelperData[0] + temp[2];
//	flash_helper_struct.FlashHelperData[0] = flash_helper_struct.FlashHelperData[0] <<8;
//	
//	flash_helper_struct.FlashHelperData[0] = flash_helper_struct.FlashHelperData[0] + temp[3];
//	flash_helper_struct.FlashHelperData[0] = flash_helper_struct.FlashHelperData[0] <<8;
//}

//char flash_data_get_bytes(char mode)
//{
//	char temp[4];
//	u32 value;
//	//��flash�����ȡ
//	if(mode)
//	{
//		flash_helper_get(1,(u32*)temp,1);
//	}
//	else
//	{
//		/*��ȡ��ǰ������*/
//		temp[0] = flash_helper_struct.FlashHelperData[0]>>24&0x000000ff;
//		temp[1] = flash_helper_struct.FlashHelperData[0]>>16&0x000000ff;
//		temp[2] = flash_helper_struct.FlashHelperData[0]>>8&0x000000ff;
//		temp[3] = flash_helper_struct.FlashHelperData[0]&0x000000ff;
//	}
//	return temp[0];
//}




