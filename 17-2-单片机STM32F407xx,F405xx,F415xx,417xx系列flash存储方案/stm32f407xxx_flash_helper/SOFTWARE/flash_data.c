#define FLASH_DATA_C_

#include "flash_data.h"
#include <string.h>
#include "flash_helper.h"
#include "data_parse.h"

/**
记录下哪些位置存储了哪些数据.一个数组就占了4个字节(高字节,中上字节,中下字节,低字节)
**/
/**以下只是举例子.
设置转速: flash_helper_struct.FlashHelperData[0] 全部使用
设置计数值: flash_helper_struct.FlashHelperData[1] 全部使用
flash_helper_struct.FlashHelperData[2] 水位值,湿度值,XXX值,XXX值,各占一个字节

记录一个最长不到1000字节的字符串
从3到252是250个u32 也就是1000字节
flash_helper_struct.FlashHelperData[3] - flash_helper_struct.FlashHelperData[252] 
**/

//设置一个最长不到1000字节的字符串
void flash_data_set_1000bytes(char *data,u32 data_len)
{
	//清空
	memset(&flash_helper_struct.FlashHelperData[3],0,1000);
	//复制
	memcpy(&flash_helper_struct.FlashHelperData[3],data,data_len);
}

//获取一个最长不到1000字节的字符串
//data 的长度是1000字节
void flash_data_get_1000bytes(char *data,char mode)
{
	if(mode) flash_helper_get(3,(u32*)data,250); //从falsh里面获取
	else memcpy(data,&flash_helper_struct.FlashHelperData[3],1000);
}


//设置水位0,湿度1,xxx值2,xxxx值3
void flash_data_set_water_humidity_xxx_xxxx(char type,char data)
{
	/*先把里面的数据全部获取出来*/
	union_resolve_value.u32_data = flash_helper_struct.FlashHelperData[2];
	if(type==0){//设置水位
		union_resolve_value.char_table[0] = data;/*重新修改下水位*/
	}
	else if(type==1){//设置湿度
		union_resolve_value.char_table[1] = data;/*重新修改下湿度*/
	}
	else if(type==2){//设置xxx值
		union_resolve_value.char_table[2] = data;/*重新修改下xxx值*/
	}
	else if(type==3){//设置xxxx值
		union_resolve_value.char_table[3] = data;/*重新修改下xxxx值*/
	}
	/*重新设置下全部数据*/
	flash_helper_struct.FlashHelperData[2] = union_resolve_value.u32_data;
}

//获取水位0,湿度1,xxx值2,xxxx值3
//返回255,说明错误
char flash_data_get_water_humidity_xxx_xxxx(char type,char mode)
{	
	u32 value;
	if(mode) flash_helper_get(2,&value,1); //从falsh里面获取
	else value = flash_helper_struct.FlashHelperData[2];
	
	/*转换*/
	union_resolve_value.u32_data = value;
	
	if(type==0) return union_resolve_value.char_table[0]; //水位
	else if(type==1)return union_resolve_value.char_table[1];//湿度
	else if(type==2)return union_resolve_value.char_table[2];//xxx值
	else if(type==3)return union_resolve_value.char_table[3];//xxxx值
	else return 255;
}


//设置转速
void flash_data_set_speed(u32 data)
{
	flash_helper_struct.FlashHelperData[0] = data;
}

//获取设置的转速
u32 flash_data_get_speed(char mode)
{
	u32 value;
	if(mode){//从falsh里面获取
		flash_helper_get(0,&value,1);
	}
	else{
		value = flash_helper_struct.FlashHelperData[0];
	}
	return value;
}

//设置计数值
void flash_data_set_count(u32 data)
{
	flash_helper_struct.FlashHelperData[1] = data;
}

//获取设置的计数值
u32 flash_data_get_count(char mode)
{
	u32 value;
	if(mode){//从falsh里面获取
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
//	/*获取先前的数据*/
//	temp[0] = flash_helper_struct.FlashHelperData[0]>>24&0x000000ff;
//	temp[1] = flash_helper_struct.FlashHelperData[0]>>16&0x000000ff;
//	temp[2] = flash_helper_struct.FlashHelperData[0]>>8&0x000000ff;
//	temp[3] = flash_helper_struct.FlashHelperData[0]&0x000000ff;
//	
//	/*改变其中的一个值,重新组合*/
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
//	//从flash里面获取
//	if(mode)
//	{
//		flash_helper_get(1,(u32*)temp,1);
//	}
//	else
//	{
//		/*获取先前的数据*/
//		temp[0] = flash_helper_struct.FlashHelperData[0]>>24&0x000000ff;
//		temp[1] = flash_helper_struct.FlashHelperData[0]>>16&0x000000ff;
//		temp[2] = flash_helper_struct.FlashHelperData[0]>>8&0x000000ff;
//		temp[3] = flash_helper_struct.FlashHelperData[0]&0x000000ff;
//	}
//	return temp[0];
//}




