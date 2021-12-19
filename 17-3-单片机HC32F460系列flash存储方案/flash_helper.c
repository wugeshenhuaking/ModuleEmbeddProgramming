#define FLASH_HELPER_C_
/***
documents: https://www.cnblogs.com/yangfengwu/p/15708263.html
****/
#include "flash_helper.h"


flash_helper_typedef flash_helper_struct;

/**Flash��������,�����Լ��ĺ����޸ĺ�����**/

//ָ����ַ��ȡһ��������u32������
void FlashHelperReadDataEx(uint32_t addr,uint32_t *data, uint32_t datalen)
{
	mcu_flash_read_words(addr,data,datalen);
}
//ָ����ַд��һ��������u32������
int FlashHelperWriteWordsEx(uint32_t addr,uint32_t *pBuffer, uint32_t NumToWrite)
{
	 return mcu_flash_write_words(addr,pBuffer,NumToWrite);
}
//����ĳһ������
char FlashHelperEraseSectorEx(uint32_t sector_start_addr,uint32_t sector_stop_addr)
{
	return mcu_flash_erase_sector(sector_start_addr,sector_stop_addr);
}


/**
* @brief  flash_helper_init
* @param  sectors_addr  ʹ����һ��������������(������ʼ��ַ)
* @param  None
* @param  None
* @retval 0:�ɹ�
* @example 
* @waing  
**/
int flash_helper_init(uint32_t sectors_addr)
{
	uint32_t i=0;
	
	flash_helper_struct.FlashHelperDataSize = FlashHelperDataLen*4;
	/*�����Ŀ�ʼ��ַ*/
	flash_helper_struct.FlashHelperStartAddr=0;
	/*�����Ľ�����ַ*/
	flash_helper_struct.FlashHelperEndAddr=0;
	/*��¼��ǰ�����ĵ�ַ*/	
	flash_helper_struct.FlashHelperSaveAddr=0;
	
	
	flash_helper_struct.FlashHelperEndAddr = sectors_addr+FLASH_SECTOR_SIZE;//����������ַ

	flash_helper_printf("\r\nsectors_addr_start: 0x%x\r\n",sectors_addr);
	flash_helper_printf("\r\nsectors_addr_stop: 0x%x\r\n",flash_helper_struct.FlashHelperEndAddr);
	
	//������ʼ��ַ
	flash_helper_struct.FlashHelperStartAddr = sectors_addr;
	
	//�ҵ���ǰ���浽���ĸ�λ��
	for(i=flash_helper_struct.FlashHelperStartAddr;i<=flash_helper_struct.FlashHelperEndAddr-flash_helper_struct.FlashHelperDataSize;i+=flash_helper_struct.FlashHelperDataSize){
		//��ȡ���������
		FlashHelperReadDataEx(i,flash_helper_struct.FlashHelperData,FlashHelperDataLen);
		
		//�б�ʶ
		if(flash_helper_struct.FlashHelperData[FlashHelperDataLen-1] == FlashHelperUUID)
		{
			//��ǰ���ݱ���ĵ�ַ
			flash_helper_struct.FlashHelperSaveAddr=i;
			
			flash_helper_printf("\r\ndata:0x55555555 addr: 0x0%x\r\n",flash_helper_struct.FlashHelperSaveAddr);
		}
		else if(flash_helper_struct.FlashHelperData[FlashHelperDataLen-1] == 0xffffffff)
		{
			//û�л�������
			if(i == flash_helper_struct.FlashHelperStartAddr)
			{
				//��ǰ���ݱ���ĵ�ַ
				flash_helper_struct.FlashHelperSaveAddr =  flash_helper_struct.FlashHelperStartAddr;
				//���ý�β��ʶ��
				memset(flash_helper_struct.FlashHelperData,0,sizeof(flash_helper_struct.FlashHelperData));
				flash_helper_struct.FlashHelperData[FlashHelperDataLen-1] = FlashHelperUUID;
				FlashHelperWriteWordsEx(flash_helper_struct.FlashHelperSaveAddr,flash_helper_struct.FlashHelperData,FlashHelperDataLen);
			}
			else
			{
				//��ȡ���������
				FlashHelperReadDataEx(i-flash_helper_struct.FlashHelperDataSize,flash_helper_struct.FlashHelperData,FlashHelperDataLen);
			}
			
			flash_helper_printf("\r\ndata:0xFFFFFFFF addr: 0x0%x\r\n",flash_helper_struct.FlashHelperSaveAddr);
			break;
		}
		else
		{
			//�����������
			FlashHelperEraseSectorEx(sectors_addr,sectors_addr);
			//��ǰ���ݱ���ĵ�ַ
			flash_helper_struct.FlashHelperSaveAddr =  flash_helper_struct.FlashHelperStartAddr;
			
			flash_helper_printf("\r\ndata:err addr: 0x0%x\r\n",flash_helper_struct.FlashHelperSaveAddr);
			break;
		}
	}
	return 0;
}


/**
* @brief  ���������������ֵ,���ô˺�������������д��flash
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
	//��ǰ�������ݵ��׵�ַ + �����ݵĸ��� = ��α������ݵ��׵�ַ
	flash_helper_struct.FlashHelperSaveAddr = flash_helper_struct.FlashHelperSaveAddr + flash_helper_struct.FlashHelperDataSize;
	
	flash_helper_printf("flash_helper_update FlashHelperSaveAddr:%x\r\n",flash_helper_struct.FlashHelperSaveAddr);
	
	//��α������ݵ�β��ַ�����˸�����β��ַ
	//������Χ,�����������,���¿�ʼ�洢
	if(flash_helper_struct.FlashHelperSaveAddr + flash_helper_struct.FlashHelperDataSize-1 > flash_helper_struct.FlashHelperEndAddr)
	{
		flash_helper_printf("flash_helper_update EraseSector\r\n");
		//�����������
		state = FlashHelperEraseSectorEx(flash_helper_struct.FlashHelperStartAddr,flash_helper_struct.FlashHelperStartAddr);
		if(state!=0)
		{
			flash_helper_printf("flash_helper_update_EraseSector ERR %d\r\n",state);
			return 1;
		}
		//���õ�ǰ����ĵ�ַΪ�����׵�ַ
		flash_helper_struct.FlashHelperSaveAddr =  flash_helper_struct.FlashHelperStartAddr;
		
		flash_helper_printf("flash_helper_update FlashHelperSaveAddr:%x\r\n",flash_helper_struct.FlashHelperSaveAddr);
	}
	//�ٴ�����һ�½�β��ʶ��,��ֹ�û�������������.
	flash_helper_struct.FlashHelperData[FlashHelperDataLen-1] = FlashHelperUUID;
	//����flash����
	state = FlashHelperWriteWordsEx(flash_helper_struct.FlashHelperSaveAddr,flash_helper_struct.FlashHelperData,FlashHelperDataLen);
	if(state!=0)
	{
		flash_helper_printf("flash_helper_update_WriteWords ERR\r\n");
		return 2;
	}
	return 0;
}


/**
* @brief   ��ȡ���������
* @param   index ��������±��Ӧ
* @param   data  ���ص�����
* @param   datalen ��ȡ�ĸ���
* @retval  0:�ɹ�
* @warning 
* @example 
**/
int flash_helper_get(uint32_t index,uint32_t *data, uint32_t datalen)
{
	//����ȡ�ĸ������ܳ���ʵ������ܷ��صĸ���
	if(datalen > FlashHelperDataLen - index) datalen = FlashHelperDataLen - index;
	FlashHelperReadDataEx(flash_helper_struct.FlashHelperSaveAddr+(index<<2),data,datalen);
	return 0;
}























