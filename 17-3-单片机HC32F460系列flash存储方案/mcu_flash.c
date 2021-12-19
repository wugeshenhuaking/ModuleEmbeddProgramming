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
* @brief  ָ����ַ��ȡһ����
* @param  faddr  ��ȡ�ĵ�ַ
* @param  none
* @param  none
* @retval ��ȡ����
* @example 
* @waing  
**/
uint32_t mcu_flash_read_word(uint32_t faddr)
{
	return *(uint32_t*)faddr; 
} 


/**
* @brief  ָ����ַ��ȡָ�����ȵ���
* @param  ReadAddr:��ʼ��ַ
* @param  pBuffer:����ָ��
* @param  NumToRead:��ȡ�ĸ���
* @retval ��ȡ����
* @example 
* @waing  
**/
void mcu_flash_read_words(uint32_t ReadAddr,uint32_t *pBuffer,uint32_t NumToRead)   	
{
	uint32_t i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=mcu_flash_read_word(ReadAddr);//��ȡ4���ֽ�.
		ReadAddr+=4;//ƫ��4���ֽ�.	
	}
}



/**
* @brief  ����һ�����߶������
* @param  sector_start_index  Ҫ������������ʼ��ַ
* @param  sector_stop_index   Ҫ����������������ַ
* @param  None
* @retval 0:�ɹ�
* @example 
1.������3������ mcu_flash_erase_sector(3*FLASH_SECTOR_SIZE, 3*FLASH_SECTOR_SIZE);
2.������3�������͵�4������ mcu_flash_erase_sector(3*FLASH_SECTOR_SIZE, 4*FLASH_SECTOR_SIZE);
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
			FlashStatus = EFM_SectorErase(i+FLASH_MCU_BASE);//�����������
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
* @brief  ָ����ַд��һ����(u32)(��Ҫ���Ȳ����ſ�ʹ�ô˺���)
* @param  WriteAddr  ��ʼд��ĵ�ַ
* @param  data    д�������
* @param  none
* @retval 0:�ɹ�
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
		FlashStatus = EFM_SingleProgram(WriteAddr,data);//д������
	}
	EFM_Lock();/* Lock EFM. */
	mcu_flash_delay_us(5);
	
	if(FlashStatus != 0) {
		mcu_flash_printf("mcu_flash_write_word ERR:%d\r\n",FlashStatus);
	}
	
	return FlashStatus;
}

/**
* @brief  ָ����ַд��ָ�����ȵ���(��Ҫ���Ȳ����ſ�ʹ�ô˺���)
* @param  WriteAddr  ��ʼд��ĵ�ַ
* @param  pBuffer    д�������
* @param  NumToWrite д������ݸ���
* @retval 0:�ɹ�
* @example 
д���ݵ�0x0007C000��ַ
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
			FlashStatus = EFM_SingleProgram(WriteAddr,pBuffer[i]);//д������
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


