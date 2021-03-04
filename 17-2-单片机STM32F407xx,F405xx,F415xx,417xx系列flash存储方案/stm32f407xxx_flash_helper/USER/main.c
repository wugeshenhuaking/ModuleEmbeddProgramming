#include <string.h>
#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "sys.h"
#include "stmflash.h"
#include "flash_helper.h"
#include "flash_data.h"

char temp[1000] = "1111111111111111111111111";
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	uart_init(115200,115200);
	delay_init();
	
	//��ʼ��ʹ����һ�������洢����
	flash_helper_init(ADDR_FLASH_SECTOR_11);	
	
	printf("\r\nStart\r\n");
	while(1)
	{
		//��ʱֻ�Ǳ����ӡ��̫��
		delay_ms(3000);
		
		//���ַ����洢��flash
		flash_data_set_1000bytes(temp,1000);
		/*ˢ��һ�������ݴ洢��flash*/
		flash_helper_update();
		
		//��ʱֻ�Ǳ����ӡ��̫��
		delay_ms(1000);
		
		//��ȡ�洢���ַ���
		memset(temp,0,sizeof(temp));
		flash_data_get_1000bytes(temp,1);
		printf("�ַ���:%s\r\n",temp);
		
	}
}



