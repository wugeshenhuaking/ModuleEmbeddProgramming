#define mcu_flash_c_

#include "mcu_flash.h"


void mcu_flash_delay_us(int value)
{
	Ddl_Delay1us(value);
}
void mcu_flash_delay_ms(int value)
{
	Ddl_Delay1ms(value);
}


/**
* @brief  指定地址读取一个字
* @param  faddr  读取的地址
* @param  none
* @param  none
* @retval 读取的字
* @example 
* @waing  
**/
uint32_t mcu_flash_read_word(uint32_t faddr)
{
	return *(uint32_t*)faddr; 
} 


/**
* @brief  指定地址读取指定长度的字
* @param  ReadAddr:起始地址
* @param  pBuffer:数据指针
* @param  NumToRead:读取的个数
* @retval 读取的字
* @example 
* @waing  
**/
void mcu_flash_read_words(uint32_t ReadAddr,uint32_t *pBuffer,uint32_t NumToRead)   	
{
	uint32_t i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=mcu_flash_read_word(ReadAddr);//读取4个字节.
		ReadAddr+=4;//偏移4个字节.	
	}
}



/**
* @brief  擦除一个或者多个扇区
* @param  sector_start_index  要擦除的扇区起始地址
* @param  sector_stop_index   要擦除的扇区结束地址
* @param  None
* @retval 0:成功
* @example 
1.擦除第3个扇区 mcu_flash_erase_sector(3*FLASH_SECTOR_SIZE, 3*FLASH_SECTOR_SIZE);
2.擦除第3个扇区和第4个扇区 mcu_flash_erase_sector(3*FLASH_SECTOR_SIZE, 4*FLASH_SECTOR_SIZE);
* @waing  
**/
int mcu_flash_erase_sector(uint32_t sector_start_addr,uint32_t sector_stop_addr)
{
	int i=0;
	char FlashStatus=0;
	
	EFM_Unlock();/* Unlock EFM. */
	EFM_FlashCmd(Enable);/* Enable flash. */
	/* Wait flash ready. */
	while((Set != EFM_GetFlagStatus(EFM_FLAG_RDY)) && i<10){
		mcu_flash_delay_ms(1);
		i++;
	}
	FlashStatus=255;
	
	if(i<10)
	{		
		for(i=sector_start_addr;i<sector_stop_addr+1;i+=FLASH_SECTOR_SIZE)
		{
			mcu_flash_delay_ms(1);
			FlashStatus = EFM_SectorErase(i+FLASH_MCU_BASE);//擦除这个扇区
			if(FlashStatus != 0) break;
		}
	}
	EFM_Lock();/* Lock EFM. */
	mcu_flash_delay_ms(10);
	if(FlashStatus != 0) 
	{
		mcu_flash_printf("mcu_flash_erase_sector ERR:%d\r\n",FlashStatus);
	}
	
	return FlashStatus;
}




/**
* @brief  指定地址写入一个字(u32)(需要事先擦除才可使用此函数)
* @param  WriteAddr  开始写入的地址
* @param  data    写入的数据
* @param  none
* @retval 0:成功
* @example 
* @waing  
**/
int mcu_flash_write_word(uint32_t WriteAddr,uint32_t data)
{
	int i=0;
	char FlashStatus = 0;
	mcu_flash_delay_us(5);
	EFM_Unlock();/* Unlock EFM. */
	EFM_FlashCmd(Enable);/* Enable flash. */
	i=0;
	while((Set != EFM_GetFlagStatus(EFM_FLAG_RDY)) && i<5000){
		mcu_flash_delay_us(1);
		i++;
	}
	FlashStatus=255;
	
	if(i<5000)
	{
		FlashStatus = EFM_SingleProgram(WriteAddr,data);//写入数据
	}
	EFM_Lock();/* Lock EFM. */
	mcu_flash_delay_us(5);
	
	if(FlashStatus != 0) {
		mcu_flash_printf("mcu_flash_write_word ERR:%d\r\n",FlashStatus);
	}
	
	return FlashStatus;
}

/**
* @brief  指定地址写入指定长度的字(需要事先擦除才可使用此函数)
* @param  WriteAddr  开始写入的地址
* @param  pBuffer    写入的数据
* @param  NumToWrite 写入的数据个数
* @retval 0:成功
* @example 
写数据到0x0007C000地址
uint32_t data[255];
mcu_flash_write_words(0x0007C000,data,255);
* @waing  
**/
int mcu_flash_write_words(uint32_t WriteAddr,uint32_t *pBuffer,uint32_t NumToWrite)
{
	int i=0;
	char FlashStatus = 0;
	mcu_flash_delay_us(5);
	EFM_Unlock();/* Unlock EFM. */
	EFM_FlashCmd(Enable);/* Enable flash. */
	i=0;
	while((Set != EFM_GetFlagStatus(EFM_FLAG_RDY)) && i<5000){
		mcu_flash_delay_us(1);
		i++;
	}
	FlashStatus=255;
	if(i<5000)
	{
		for(i=0;i<NumToWrite;i++)
		{
			FlashStatus = EFM_SingleProgram(WriteAddr,pBuffer[i]);//写入数据
			if(FlashStatus != 0) break;
			WriteAddr = WriteAddr + 4;
		}
	}
	
	EFM_Lock();/* Lock EFM. */
	mcu_flash_delay_us(5);
	if(FlashStatus != 0) {
		mcu_flash_printf("mcu_flash_write_words ERR:%d\r\n",FlashStatus);
	}
	return FlashStatus;
}


