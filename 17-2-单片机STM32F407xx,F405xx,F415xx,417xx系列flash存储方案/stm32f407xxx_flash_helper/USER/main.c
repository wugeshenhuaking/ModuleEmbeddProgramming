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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	uart_init(115200,115200);
	delay_init();
	
	//初始化使用哪一个扇区存储数据
	flash_helper_init(ADDR_FLASH_SECTOR_11);	
	
	printf("\r\nStart\r\n");
	while(1)
	{
		//延时只是避免打印的太快
		delay_ms(3000);
		
		//把字符串存储到flash
		flash_data_set_1000bytes(temp,1000);
		/*刷新一下让数据存储到flash*/
		flash_helper_update();
		
		//延时只是避免打印的太快
		delay_ms(1000);
		
		//获取存储的字符串
		memset(temp,0,sizeof(temp));
		flash_data_get_1000bytes(temp,1);
		printf("字符串:%s\r\n",temp);
		
	}
}



