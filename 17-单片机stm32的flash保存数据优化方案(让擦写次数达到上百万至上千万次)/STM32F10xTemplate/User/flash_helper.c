/**
  ******************************************************************************
  * @author  feng wu yang
  * @version V1.0.0  
	* @version V1.0.1 �޸�  FlashHelperUpdate �л�ȡβ������bug
	* @version V1.1.0 �޸�  FlashHelperUpdate �л�ȡβ������bug
  * @date    2020/09/02
  * @brief   flash ������ѵ�洢(�������flashʹ������)
	* @document https://www.cnblogs.com/yangfengwu/p/13616968.html
  ******************************************************************************
	1.������λFlashHelperData[��һλ] �� FlashHelperData[���һλ] ��Ϊ���ݱ�ʶ,�û�����ʹ��!
  ******************************************************************************
  */


#define FLASH_HELPER_C_
#include <stdio.h>
#include "flash_helper.h"
#include "stmflash.h"

#ifdef FlashHelperDebug
#include "usart.h" //ʹ��printf��ӡ����
#endif

flash_helper_typedef flash_helper_struct;

//��
void FlashHelperReadDataEx(u32 addr,u16 *data, u16 datalen)
{
	STMFLASH_Read(addr,data,datalen);
}
//д
void FlashHelperWriteDataEx(u32 addr,u16 *data, u16 datalen)
{
	 WriteFlashHalfWords(addr,data,datalen);
}
//����
char FlashHelperErasePageEx(u32 EraseAddress,u16 PageCnt)
{
	FlashErasePages(EraseAddress,PageCnt);
}

/**
* @brief   ��ʼ��
* @param   ADDR ������
* @param   None
* @param   None
* @retval  None
* @warning None
* @example 
**/
void FlashHelperInit(u32 ADDR1,u32 ADDR2,u32 ADDR3,u32 ADDR4)
{
	u16 i,j;
	u16 data[FlashHelperDataLen];
	u16 a1,a2,a3,a4;
	u16 b1,b2,b3,b4;
	
	
	flash_helper_struct.FlashHelperPageAddr[0] = ADDR1 + FlashHelperAddressOffset;
	flash_helper_struct.FlashHelperPageAddr[1] = ADDR2 + FlashHelperAddressOffset;
	flash_helper_struct.FlashHelperPageAddr[2] = ADDR3 + FlashHelperAddressOffset;
	flash_helper_struct.FlashHelperPageAddr[3] = ADDR4 + FlashHelperAddressOffset;
	
	#ifdef FlashHelperDebug
	printf("\r\n page0: 0x%x",flash_helper_struct.FlashHelperPageAddr[0]);
	printf("\r\n page1: 0x%x",flash_helper_struct.FlashHelperPageAddr[1]);
	printf("\r\n page2: 0x%x",flash_helper_struct.FlashHelperPageAddr[2]);
	printf("\r\n page3: 0x%x",flash_helper_struct.FlashHelperPageAddr[3]);
	#endif
	
	
	flash_helper_struct.FlashHelperData[0] = 0xAA;
	flash_helper_struct.FlashHelperData[FlashHelperDataLen-1] = 0x55;
	
	flash_helper_struct.FlashHelperTail = FlashHelperMaxLen/FlashHelperDataLen;
	flash_helper_struct.FlashHelperTail = flash_helper_struct.FlashHelperTail*FlashHelperDataLen;
	
	/*��0ҳ*/
	FlashHelperReadDataEx(flash_helper_struct.FlashHelperPageAddr[0],&a1,1);//�׵�ַ����
	FlashHelperReadDataEx(flash_helper_struct.FlashHelperPageAddr[0]+(flash_helper_struct.FlashHelperTail<<1)-2,&b1,1);//β��ַ����
	/*��1ҳ*/
	FlashHelperReadDataEx(flash_helper_struct.FlashHelperPageAddr[1],&a2,1);//�׵�ַ����
	FlashHelperReadDataEx(flash_helper_struct.FlashHelperPageAddr[1]+(flash_helper_struct.FlashHelperTail<<1)-2,&b2,1);//β��ַ����	
	/*��2ҳ*/
	FlashHelperReadDataEx(flash_helper_struct.FlashHelperPageAddr[2],&a3,1);//�׵�ַ����
	FlashHelperReadDataEx(flash_helper_struct.FlashHelperPageAddr[2]+(flash_helper_struct.FlashHelperTail<<1)-2,&b3,1);//β��ַ����
	/*��3ҳ*/
	FlashHelperReadDataEx(flash_helper_struct.FlashHelperPageAddr[3],&a4,1);//�׵�ַ����
	FlashHelperReadDataEx(flash_helper_struct.FlashHelperPageAddr[3]+(flash_helper_struct.FlashHelperTail<<1)-2,&b4,1);//β��ַ����
	
	
	if(a1==0xFFFF && b1==0xFFFF && a2==0xFFFF && b2==0xFFFF && a3==0xFFFF && b3==0xFFFF && a4==0xFFFF && b4==0xFFFF)
	{
		flash_helper_struct.FlashHelperFlashAddr = flash_helper_struct.FlashHelperPageAddr[1];
		#ifdef FlashHelperDebug
		printf("\r\n no save data");
		#endif
	}
	else if(a1==0xAA && b1 == 0xFFFF)//data save page0
	{
		#ifdef FlashHelperDebug
		printf("\r\n data save page0\r\n");
		#endif
		for(i=0;i<FlashHelperMaxLen/FlashHelperDataLen;i++)
		{
			flash_helper_struct.FlashHelperFlashAddr = flash_helper_struct.FlashHelperPageAddr[0]+i*FlashHelperDataLen*2;
			
			FlashHelperReadDataEx(flash_helper_struct.FlashHelperFlashAddr,data,FlashHelperDataLen);
			
			if(data[0]==0xFFFF && data[FlashHelperDataLen-1]==0xFFFF)
			{
				#ifdef FlashHelperDebug
				for(j=0;j<FlashHelperDataLen;j++){printf("%x ",flash_helper_struct.FlashHelperData[j]);}		
				#endif
				
				break;
			}
			for(j=0;j<FlashHelperDataLen;j++){flash_helper_struct.FlashHelperData[j] = data[j];}				
		}
	}
	else if(a2==0xAA && b2 == 0xFFFF)//data save page1
	{
		#ifdef FlashHelperDebug
		printf("\r\n data save page1\r\n");
		#endif
		for(i=0;i<FlashHelperMaxLen/FlashHelperDataLen;i++)
		{
			flash_helper_struct.FlashHelperFlashAddr = flash_helper_struct.FlashHelperPageAddr[1]+i*FlashHelperDataLen*2;
			
			FlashHelperReadDataEx(flash_helper_struct.FlashHelperFlashAddr,data,FlashHelperDataLen);
			
			if(data[0]==0xFFFF && data[FlashHelperDataLen-1]==0xFFFF)
			{
				#ifdef FlashHelperDebug
				for(j=0;j<FlashHelperDataLen;j++){printf("%x ",flash_helper_struct.FlashHelperData[j]);}		
				#endif
				break;
			}
			for(j=0;j<FlashHelperDataLen;j++){flash_helper_struct.FlashHelperData[j] = data[j];}	
		}
	}
	else if(a3==0xAA && b3 == 0xFFFF)//data save page2
	{
		#ifdef FlashHelperDebug
		printf("\r\n data save page2\r\n");
		#endif
		for(i=0;i<FlashHelperMaxLen/FlashHelperDataLen;i++)
		{
			flash_helper_struct.FlashHelperFlashAddr = flash_helper_struct.FlashHelperPageAddr[2]+i*FlashHelperDataLen*2;
			
			FlashHelperReadDataEx(flash_helper_struct.FlashHelperFlashAddr,data,FlashHelperDataLen);
			
			if(data[0]==0xFFFF && data[FlashHelperDataLen-1]==0xFFFF)
			{
				#ifdef FlashHelperDebug
				for(j=0;j<FlashHelperDataLen;j++){printf("%x ",flash_helper_struct.FlashHelperData[j]);}		
				#endif
				break;
			}
			for(j=0;j<FlashHelperDataLen;j++){flash_helper_struct.FlashHelperData[j] = data[j];}	
		}
	}
	else if(a4==0xAA && b4 == 0xFFFF)//data save page3
	{
		#ifdef FlashHelperDebug
		printf("\r\n data save page3\r\n");
		#endif
		for(i=0;i<FlashHelperMaxLen/FlashHelperDataLen;i++)
		{
			flash_helper_struct.FlashHelperFlashAddr = flash_helper_struct.FlashHelperPageAddr[3]+i*FlashHelperDataLen*2;
			
			FlashHelperReadDataEx(flash_helper_struct.FlashHelperFlashAddr,data,FlashHelperDataLen);
			
			if(data[0]==0xFFFF && data[FlashHelperDataLen-1]==0xFFFF)
			{
				#ifdef FlashHelperDebug
				for(j=0;j<FlashHelperDataLen;j++){printf("%x ",flash_helper_struct.FlashHelperData[j]);}		
				#endif
				break;
			}
			for(j=0;j<FlashHelperDataLen;j++){flash_helper_struct.FlashHelperData[j] = data[j];}	
		}
	}
	else if(a1==0xAA && b1 == 0x55)//data save page0 ?
	{
		#ifdef FlashHelperDebug
		printf("\r\n data save page0 ?\r\n");
		#endif
		
		if(a2==0xAA && b2 == 0xFFFF)//data save page1
		{
			#ifdef FlashHelperDebug
			printf("\r\n data save page1\r\n");
			#endif
			for(i=0;i<FlashHelperMaxLen/FlashHelperDataLen;i++)
			{
				flash_helper_struct.FlashHelperFlashAddr = flash_helper_struct.FlashHelperPageAddr[1]+i*FlashHelperDataLen*2;
				
				FlashHelperReadDataEx(flash_helper_struct.FlashHelperFlashAddr,data,FlashHelperDataLen);

				if(data[0]==0xFFFF && data[FlashHelperDataLen-1]==0xFFFF)
				{
					#ifdef FlashHelperDebug
					for(j=0;j<FlashHelperDataLen;j++){printf("%x ",flash_helper_struct.FlashHelperData[j]);}		
					#endif
					break;
				}
				for(j=0;j<FlashHelperDataLen;j++){flash_helper_struct.FlashHelperData[j] = data[j];}
			}
		}
		else //data save page0 but page0 is full
		{
			#ifdef FlashHelperDebug
			printf("\r\n ata save page0 but page0 is full\r\n");
			#endif
			FlashHelperReadDataEx(flash_helper_struct.FlashHelperPageAddr[0]+(FlashHelperMaxLen/FlashHelperDataLen-1)*FlashHelperDataLen*2,data,FlashHelperDataLen);
			for(j=0;j<FlashHelperDataLen;j++){
				flash_helper_struct.FlashHelperData[j] = data[j];
				#ifdef FlashHelperDebug
				printf("%x ",flash_helper_struct.FlashHelperData[j]);
				#endif
			}
			flash_helper_struct.FlashHelperFlashAddr = flash_helper_struct.FlashHelperPageAddr[1];
		}
	}
	else if(a2==0xAA && b2 == 0x55)//data save page1 ?
	{
		#ifdef FlashHelperDebug
		printf("\r\n data save page1 ?\r\n");
		#endif
		
		if(a3==0xAA && b3 == 0xFFFF)//data save page2
		{
			#ifdef FlashHelperDebug
			printf("\r\n data save page2\r\n");
			#endif
			for(i=0;i<FlashHelperMaxLen/FlashHelperDataLen;i++)
			{
				flash_helper_struct.FlashHelperFlashAddr = flash_helper_struct.FlashHelperPageAddr[2]+i*FlashHelperDataLen*2;
				
				FlashHelperReadDataEx(flash_helper_struct.FlashHelperFlashAddr,data,FlashHelperDataLen);

				if(data[0]==0xFFFF && data[FlashHelperDataLen-1]==0xFFFF)
				{
					#ifdef FlashHelperDebug
					for(j=0;j<FlashHelperDataLen;j++){printf("%x ",flash_helper_struct.FlashHelperData[j]);}		
					#endif
					break;
				}
				for(j=0;j<FlashHelperDataLen;j++){flash_helper_struct.FlashHelperData[j] = data[j];}
			}
		}
		else //data save page1 but page1 is full
		{
			#ifdef FlashHelperDebug
			printf("\r\n data save page1 but page1 is full\r\n");
			#endif
			FlashHelperReadDataEx(flash_helper_struct.FlashHelperPageAddr[1]+(FlashHelperMaxLen/FlashHelperDataLen-1)*FlashHelperDataLen*2,data,FlashHelperDataLen);
			for(j=0;j<FlashHelperDataLen;j++){
				flash_helper_struct.FlashHelperData[j] = data[j];
				#ifdef FlashHelperDebug
				printf("%x ",flash_helper_struct.FlashHelperData[j]);
				#endif
			}
			flash_helper_struct.FlashHelperFlashAddr = flash_helper_struct.FlashHelperPageAddr[2];
		}
	}
	else if(a3==0xAA && b3 == 0x55)//data save page2 ?
	{
		#ifdef FlashHelperDebug
		printf("\r\n data save page2 ?\r\n");
		#endif
		
		if(a4==0xAA && b4 == 0xFFFF)//data save page3
		{
			#ifdef FlashHelperDebug
			printf("\r\n data save page3\r\n");
			#endif
			for(i=0;i<FlashHelperMaxLen/FlashHelperDataLen;i++)
			{
				flash_helper_struct.FlashHelperFlashAddr = flash_helper_struct.FlashHelperPageAddr[3]+i*FlashHelperDataLen*2;
				
				FlashHelperReadDataEx(flash_helper_struct.FlashHelperFlashAddr,data,FlashHelperDataLen);

				if(data[0]==0xFFFF && data[FlashHelperDataLen-1]==0xFFFF)
				{
					#ifdef FlashHelperDebug
					for(j=0;j<FlashHelperDataLen;j++){printf("%x ",flash_helper_struct.FlashHelperData[j]);}		
					#endif
					break;
				}
				for(j=0;j<FlashHelperDataLen;j++){flash_helper_struct.FlashHelperData[j] = data[j];}
			}
		}
		else //data save page2 but page2 is full
		{
			#ifdef FlashHelperDebug
			printf("\r\n data save page2 but page2 is full\r\n");
			#endif
			FlashHelperReadDataEx(flash_helper_struct.FlashHelperPageAddr[2]+(FlashHelperMaxLen/FlashHelperDataLen-1)*FlashHelperDataLen*2,data,FlashHelperDataLen);
			for(j=0;j<FlashHelperDataLen;j++){
				flash_helper_struct.FlashHelperData[j] = data[j];
				#ifdef FlashHelperDebug
				printf("%x ",flash_helper_struct.FlashHelperData[j]);
				#endif
			}
			flash_helper_struct.FlashHelperFlashAddr = flash_helper_struct.FlashHelperPageAddr[3];
		}
	}
	else if(a4==0xAA && b4 == 0x55)//data save page3 ?
	{
		#ifdef FlashHelperDebug
		printf("\r\n data save page3 ?\r\n");
		#endif
		
		if(a1==0xAA && b1 == 0xFFFF)//data save page0
		{
			#ifdef FlashHelperDebug
			printf("\r\n data save page0\r\n");
			#endif
			for(i=0;i<FlashHelperMaxLen/FlashHelperDataLen;i++)
			{
				flash_helper_struct.FlashHelperFlashAddr = flash_helper_struct.FlashHelperPageAddr[0]+i*FlashHelperDataLen*2;
				
				FlashHelperReadDataEx(flash_helper_struct.FlashHelperFlashAddr,data,FlashHelperDataLen);

				if(data[0]==0xFFFF && data[FlashHelperDataLen-1]==0xFFFF)
				{
					#ifdef FlashHelperDebug
					for(j=0;j<FlashHelperDataLen;j++){printf("%x ",flash_helper_struct.FlashHelperData[j]);}		
					#endif
					break;
				}
				for(j=0;j<FlashHelperDataLen;j++){flash_helper_struct.FlashHelperData[j] = data[j];}
			}
		}
		else //data save page3 but page3 is full
		{
			#ifdef FlashHelperDebug
			printf("\r\n data save page3 but page3 is full\r\n");
			#endif
			FlashHelperReadDataEx(flash_helper_struct.FlashHelperPageAddr[3]+(FlashHelperMaxLen/FlashHelperDataLen-1)*FlashHelperDataLen*2,data,FlashHelperDataLen);
			for(j=0;j<FlashHelperDataLen;j++){
				flash_helper_struct.FlashHelperData[j] = data[j];
				#ifdef FlashHelperDebug
				printf("%x ",flash_helper_struct.FlashHelperData[j]);
				#endif
			}
			flash_helper_struct.FlashHelperFlashAddr = flash_helper_struct.FlashHelperPageAddr[0];
		}
	}
}


void FlashHelperUpdate(void)
{
	u16 a,b;//�ж���һҳ�Ƿ����
	
	/*���ڵ�0ҳ*/
	if( flash_helper_struct.FlashHelperFlashAddr >= flash_helper_struct.FlashHelperPageAddr[0] &&
			flash_helper_struct.FlashHelperFlashAddr < flash_helper_struct.FlashHelperPageAddr[1]
		)
	{
		//��ҳ�����洢
		if((flash_helper_struct.FlashHelperFlashAddr + (FlashHelperDataLen<<1)) > (flash_helper_struct.FlashHelperPageAddr[0]+(FlashHelperMaxLen<<1)))
		{
			flash_helper_struct.FlashHelperFlashAddr = flash_helper_struct.FlashHelperPageAddr[1];//�洢����1ҳ
			flash_helper_struct.FlashHelperFlashAddrCopy = flash_helper_struct.FlashHelperFlashAddr;
		}
		else
		{
			flash_helper_struct.FlashHelperFlashAddrCopy = flash_helper_struct.FlashHelperFlashAddr;//�洢����ҳ
		}
		flash_helper_struct.FlashHelperFlashAddr = flash_helper_struct.FlashHelperFlashAddr + (FlashHelperDataLen<<1);
		FlashHelperWriteDataEx(flash_helper_struct.FlashHelperFlashAddrCopy,flash_helper_struct.FlashHelperData,FlashHelperDataLen);
		#ifdef FlashHelperDebug
		printf("\r\n FlashHelperFlashAddr: 0x%x",flash_helper_struct.FlashHelperFlashAddr);
		#endif
		/*������һҳ*/
		FlashHelperReadDataEx(flash_helper_struct.FlashHelperPageAddr[3],&a,1);//�׵�ַ����
		FlashHelperReadDataEx(flash_helper_struct.FlashHelperPageAddr[3]+(flash_helper_struct.FlashHelperTail<<1)-2,&b,1);//β��ַ����
		if(a != 0xFFFF || b != 0xFFFF)
		{
			#ifdef FlashHelperDebug
			printf("\r\n ErasePag3\r\n");
			#endif
			FlashHelperErasePageEx(flash_helper_struct.FlashHelperPageAddr[3],1);
		}
	}
	/*���ڵ�1ҳ*/
	else if(flash_helper_struct.FlashHelperFlashAddr >= flash_helper_struct.FlashHelperPageAddr[1] &&
			flash_helper_struct.FlashHelperFlashAddr < flash_helper_struct.FlashHelperPageAddr[2]
		)
	{
		//��ҳ�����洢
		if((flash_helper_struct.FlashHelperFlashAddr + (FlashHelperDataLen<<1)) > (flash_helper_struct.FlashHelperPageAddr[1]+(FlashHelperMaxLen<<1)))
		{
			#ifdef FlashHelperDebug
			printf("\r\n FlashHelperMaxLen=%d\r\n",FlashHelperMaxLen);
			#endif
			flash_helper_struct.FlashHelperFlashAddr = flash_helper_struct.FlashHelperPageAddr[2];//�洢����2ҳ
			flash_helper_struct.FlashHelperFlashAddrCopy = flash_helper_struct.FlashHelperFlashAddr;
		}
		else
		{
			flash_helper_struct.FlashHelperFlashAddrCopy = flash_helper_struct.FlashHelperFlashAddr;//�洢����ҳ
		}
		flash_helper_struct.FlashHelperFlashAddr = flash_helper_struct.FlashHelperFlashAddr + (FlashHelperDataLen<<1);
		FlashHelperWriteDataEx(flash_helper_struct.FlashHelperFlashAddrCopy,flash_helper_struct.FlashHelperData,FlashHelperDataLen);
		
		#ifdef FlashHelperDebug
		printf("\r\n FlashHelperFlashAddr: 0x%x",flash_helper_struct.FlashHelperFlashAddr);
		#endif
		
		/*������һҳ*/
		FlashHelperReadDataEx(flash_helper_struct.FlashHelperPageAddr[0],&a,1);//�׵�ַ����
		FlashHelperReadDataEx(flash_helper_struct.FlashHelperPageAddr[0]+(flash_helper_struct.FlashHelperTail<<1)-2,&b,1);//β��ַ����
		if(a != 0xFFFF || b != 0xFFFF)
		{
			#ifdef FlashHelperDebug
			printf("\r\n TailAddr: 0x%x",flash_helper_struct.FlashHelperPageAddr[0]+(flash_helper_struct.FlashHelperTail<<1)-2);
			#endif
			
			
			#ifdef FlashHelperDebug
			printf("\r\n ErasePag0\r\n");
			#endif
			FlashHelperErasePageEx(flash_helper_struct.FlashHelperPageAddr[0],1);
		}
	}
	/*���ڵ�2ҳ*/
	else if(flash_helper_struct.FlashHelperFlashAddr >= flash_helper_struct.FlashHelperPageAddr[2] &&
		flash_helper_struct.FlashHelperFlashAddr < flash_helper_struct.FlashHelperPageAddr[3]
	)
	{
		//��ҳ�����洢
		if((flash_helper_struct.FlashHelperFlashAddr + (FlashHelperDataLen<<1)) > (flash_helper_struct.FlashHelperPageAddr[2]+(FlashHelperMaxLen<<1)))
		{
			flash_helper_struct.FlashHelperFlashAddr = flash_helper_struct.FlashHelperPageAddr[3];//�洢����3ҳ
			flash_helper_struct.FlashHelperFlashAddrCopy = flash_helper_struct.FlashHelperFlashAddr;
		}
		else
		{
			flash_helper_struct.FlashHelperFlashAddrCopy = flash_helper_struct.FlashHelperFlashAddr;//�洢����ҳ
		}
		flash_helper_struct.FlashHelperFlashAddr = flash_helper_struct.FlashHelperFlashAddr + (FlashHelperDataLen<<1);
		FlashHelperWriteDataEx(flash_helper_struct.FlashHelperFlashAddrCopy,flash_helper_struct.FlashHelperData,FlashHelperDataLen);
		
		#ifdef FlashHelperDebug
		printf("\r\n FlashHelperFlashAddr: 0x%x",flash_helper_struct.FlashHelperFlashAddr);
		#endif
		
		/*������һҳ*/
		FlashHelperReadDataEx(flash_helper_struct.FlashHelperPageAddr[1],&a,1);//�׵�ַ����
		FlashHelperReadDataEx(flash_helper_struct.FlashHelperPageAddr[1]+(flash_helper_struct.FlashHelperTail<<1)-2,&b,1);//β��ַ����
		if(a != 0xFFFF || b != 0xFFFF)
		{
			#ifdef FlashHelperDebug
			printf("\r\n TailAddr: 0x%x",flash_helper_struct.FlashHelperPageAddr[1]+(flash_helper_struct.FlashHelperTail<<1)-2);
			#endif
			
			#ifdef FlashHelperDebug
			printf("\r\n ErasePag1\r\n");
			#endif
			FlashHelperErasePageEx(flash_helper_struct.FlashHelperPageAddr[1],1);
		}
	}
	else //���ڵ���ҳ
	{	
		//��ҳ�����洢
		if((flash_helper_struct.FlashHelperFlashAddr + (FlashHelperDataLen<<1)) > (flash_helper_struct.FlashHelperPageAddr[3]+(FlashHelperMaxLen<<1)))
		{
			flash_helper_struct.FlashHelperFlashAddr = flash_helper_struct.FlashHelperPageAddr[0];//�洢����0ҳ
			flash_helper_struct.FlashHelperFlashAddrCopy = flash_helper_struct.FlashHelperFlashAddr;
		}
		else
		{
			flash_helper_struct.FlashHelperFlashAddrCopy = flash_helper_struct.FlashHelperFlashAddr;//�洢����ҳ
		}
		flash_helper_struct.FlashHelperFlashAddr = flash_helper_struct.FlashHelperFlashAddr + (FlashHelperDataLen<<1);
		FlashHelperWriteDataEx(flash_helper_struct.FlashHelperFlashAddrCopy,flash_helper_struct.FlashHelperData,FlashHelperDataLen);
		
		#ifdef FlashHelperDebug
		printf("\r\n FlashHelperFlashAddr: 0x%x",flash_helper_struct.FlashHelperFlashAddr);
		#endif
		
		/*������һҳ*/
		FlashHelperReadDataEx(flash_helper_struct.FlashHelperPageAddr[2],&a,1);//�׵�ַ����
		FlashHelperReadDataEx(flash_helper_struct.FlashHelperPageAddr[2]+(flash_helper_struct.FlashHelperTail<<1)-2,&b,1);//β��ַ����
		if(a != 0xFFFF || b != 0xFFFF)
		{
			#ifdef FlashHelperDebug
			printf("\r\n ErasePag2\r\n");
			#endif
			FlashHelperErasePageEx(flash_helper_struct.FlashHelperPageAddr[2],1);
		}
	}
}



/**
* @brief   ��ȡ������������
* @param   index ����ֵ
* @param   None
* @param   None
* @retval  None
* @warning ������ˢ�º����Ժ���Ҫ�������ô˺���,���Ƕ����ĸոմ������ʵ����
* @example 
**/
u16 FlashHelperGetIndex(u16 index)
{
	u16 data;
	FlashHelperReadDataEx(flash_helper_struct.FlashHelperFlashAddrCopy+(index<<1),&data,1);
	return data;
}
