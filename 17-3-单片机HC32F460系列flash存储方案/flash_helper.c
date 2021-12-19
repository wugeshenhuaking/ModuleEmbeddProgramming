#define FLASH_HELPER_C_
/***
documents: https://www.cnblogs.com/yangfengwu/p/15708263.html
****/
#include "flash_helper.h"


flash_helper_typedef flash_helper_struct;

/**Flash操作函数,根据自己的函数修改函数体**/

//指定地址读取一定个数的u32型数据
void FlashHelperReadDataEx(uint32_t addr,uint32_t *data, uint32_t datalen)
{
	mcu_flash_read_words(addr,data,datalen);
}
//指定地址写入一定个数的u32型数据
int FlashHelperWriteWordsEx(uint32_t addr,uint32_t *pBuffer, uint32_t NumToWrite)
{
	 return mcu_flash_write_words(addr,pBuffer,NumToWrite);
}
//擦除某一个扇区
char FlashHelperEraseSectorEx(uint32_t sector_start_addr,uint32_t sector_stop_addr)
{
	return mcu_flash_erase_sector(sector_start_addr,sector_stop_addr);
}


/**
* @brief  flash_helper_init
* @param  sectors_addr  使用哪一个扇区保存数据(扇区开始地址)
* @param  None
* @param  None
* @retval 0:成功
* @example 
* @waing  
**/
int flash_helper_init(uint32_t sectors_addr)
{
	uint32_t i=0;
	
	flash_helper_struct.FlashHelperDataSize = FlashHelperDataLen*4;
	/*扇区的开始地址*/
	flash_helper_struct.FlashHelperStartAddr=0;
	/*扇区的结束地址*/
	flash_helper_struct.FlashHelperEndAddr=0;
	/*记录当前操作的地址*/	
	flash_helper_struct.FlashHelperSaveAddr=0;
	
	
	flash_helper_struct.FlashHelperEndAddr = sectors_addr+FLASH_SECTOR_SIZE;//扇区结束地址

	flash_helper_printf("\r\nsectors_addr_start: 0x%x\r\n",sectors_addr);
	flash_helper_printf("\r\nsectors_addr_stop: 0x%x\r\n",flash_helper_struct.FlashHelperEndAddr);
	
	//扇区开始地址
	flash_helper_struct.FlashHelperStartAddr = sectors_addr;
	
	//找到当前缓存到了哪个位置
	for(i=flash_helper_struct.FlashHelperStartAddr;i<=flash_helper_struct.FlashHelperEndAddr-flash_helper_struct.FlashHelperDataSize;i+=flash_helper_struct.FlashHelperDataSize){
		//获取缓存的数据
		FlashHelperReadDataEx(i,flash_helper_struct.FlashHelperData,FlashHelperDataLen);
		
		//有标识
		if(flash_helper_struct.FlashHelperData[FlashHelperDataLen-1] == FlashHelperUUID)
		{
			//当前数据保存的地址
			flash_helper_struct.FlashHelperSaveAddr=i;
			
			flash_helper_printf("\r\ndata:0x55555555 addr: 0x0%x\r\n",flash_helper_struct.FlashHelperSaveAddr);
		}
		else if(flash_helper_struct.FlashHelperData[FlashHelperDataLen-1] == 0xffffffff)
		{
			//没有缓存数据
			if(i == flash_helper_struct.FlashHelperStartAddr)
			{
				//当前数据保存的地址
				flash_helper_struct.FlashHelperSaveAddr =  flash_helper_struct.FlashHelperStartAddr;
				//设置结尾标识符
				memset(flash_helper_struct.FlashHelperData,0,sizeof(flash_helper_struct.FlashHelperData));
				flash_helper_struct.FlashHelperData[FlashHelperDataLen-1] = FlashHelperUUID;
				FlashHelperWriteWordsEx(flash_helper_struct.FlashHelperSaveAddr,flash_helper_struct.FlashHelperData,FlashHelperDataLen);
			}
			else
			{
				//获取缓存的数据
				FlashHelperReadDataEx(i-flash_helper_struct.FlashHelperDataSize,flash_helper_struct.FlashHelperData,FlashHelperDataLen);
			}
			
			flash_helper_printf("\r\ndata:0xFFFFFFFF addr: 0x0%x\r\n",flash_helper_struct.FlashHelperSaveAddr);
			break;
		}
		else
		{
			//擦除这个扇区
			FlashHelperEraseSectorEx(sectors_addr,sectors_addr);
			//当前数据保存的地址
			flash_helper_struct.FlashHelperSaveAddr =  flash_helper_struct.FlashHelperStartAddr;
			
			flash_helper_printf("\r\ndata:err addr: 0x0%x\r\n",flash_helper_struct.FlashHelperSaveAddr);
			break;
		}
	}
	return 0;
}


/**
* @brief  更改完数组里面的值,调用此函数把数组数据写入flash
* @param  None
* @param  None
* @param  None
* @retval 0 sucess
* @example 
* @waing  
**/
int flash_helper_update(void)
{
	int state;
	//先前保存数据的首地址 + 存数据的个数 = 这次保存数据的首地址
	flash_helper_struct.FlashHelperSaveAddr = flash_helper_struct.FlashHelperSaveAddr + flash_helper_struct.FlashHelperDataSize;
	
	flash_helper_printf("flash_helper_update FlashHelperSaveAddr:%x\r\n",flash_helper_struct.FlashHelperSaveAddr);
	
	//这次保存数据的尾地址大于了该扇区尾地址
	//超出范围,清除整个扇区,重新开始存储
	if(flash_helper_struct.FlashHelperSaveAddr + flash_helper_struct.FlashHelperDataSize-1 > flash_helper_struct.FlashHelperEndAddr)
	{
		flash_helper_printf("flash_helper_update EraseSector\r\n");
		//擦除这个扇区
		state = FlashHelperEraseSectorEx(flash_helper_struct.FlashHelperStartAddr,flash_helper_struct.FlashHelperStartAddr);
		if(state!=0)
		{
			flash_helper_printf("flash_helper_update_EraseSector ERR %d\r\n",state);
			return 1;
		}
		//设置当前保存的地址为扇区首地址
		flash_helper_struct.FlashHelperSaveAddr =  flash_helper_struct.FlashHelperStartAddr;
		
		flash_helper_printf("flash_helper_update FlashHelperSaveAddr:%x\r\n",flash_helper_struct.FlashHelperSaveAddr);
	}
	//再次设置一下结尾标识符,防止用户操作不当戳改.
	flash_helper_struct.FlashHelperData[FlashHelperDataLen-1] = FlashHelperUUID;
	//更新flash数据
	state = FlashHelperWriteWordsEx(flash_helper_struct.FlashHelperSaveAddr,flash_helper_struct.FlashHelperData,FlashHelperDataLen);
	if(state!=0)
	{
		flash_helper_printf("flash_helper_update_WriteWords ERR\r\n");
		return 2;
	}
	return 0;
}


/**
* @brief   获取缓存的数据
* @param   index 和数组的下标对应
* @param   data  返回的数据
* @param   datalen 获取的个数
* @retval  0:成功
* @warning 
* @example 
**/
int flash_helper_get(uint32_t index,uint32_t *data, uint32_t datalen)
{
	//最大获取的个数不能超出实际最大能返回的个数
	if(datalen > FlashHelperDataLen - index) datalen = FlashHelperDataLen - index;
	FlashHelperReadDataEx(flash_helper_struct.FlashHelperSaveAddr+(index<<2),data,datalen);
	return 0;
}























