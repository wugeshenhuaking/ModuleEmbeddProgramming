/**
  ******************************************************************************
  * @author  yang feng wu 
  * @version V1.0.0
  * @date    2019/10/12
  * @brief   
  ******************************************************************************
	
  ******************************************************************************
  */
#include <stm32f10x.h>
#include "System.h"
#include "delay.h"
#include "usart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "gpio.h"

#include "mbedtls/sha1.h"

/*测试 sha1 加密*/
int i=0;
unsigned char encrypt[] = "yang";
unsigned char decrypt[20];
mbedtls_sha1_context sha1_ctx;
/*测试 sha1 加密*/

int main(void)
{
  NVIC_Configuration();
	uart_init(115200);	 //串口初始化为115200
	GpioInit();
	DelayInit();
	
	
	mbedtls_sha1_init(&sha1_ctx);
	mbedtls_sha1_starts(&sha1_ctx);
	mbedtls_sha1_update(&sha1_ctx,encrypt,4);
	mbedtls_sha1_finish(&sha1_ctx,decrypt);
	mbedtls_sha1_free(&sha1_ctx);
	printf("对yang进行sha1加密后的值:\r\n");
	for(i=0;i<20;i++){
		printf("%02x",decrypt[i]);
	}
	
	while(1)
	{
		
	}
}

