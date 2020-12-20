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

#include <time.h>


#include "mbedtls/config.h"
#include "mbedtls/ssl.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/debug.h"
#include "mbedtls/entropy_poll.h"
#include "mbedtls/platform.h"
#include "mbedtls/net_sockets.h"


#define MainBufferLen 2000
char MainBuffer[MainBufferLen];//缓存数据,全局通用
u32  MainLen=0;      //全局通用变量


/*假设接收网络数据函数*/
int net_recv(char *data){}
/*假设TCP发送数据函数*/
int net_send(char *data,int len){}


/*随机数函数*/
int mbedtls_hardware_poll( void *data,
                    unsigned char *output, size_t len, size_t *olen )
{
	unsigned long randomValue = ((rand()*20) + 1000);//生成随机数
	((void) data);
	*olen = 0;
	
	if( len < sizeof(unsigned long) ) return( 0 );	

	memcpy( output, &randomValue, sizeof(unsigned long) );
	*olen = sizeof(unsigned long);
  return 0;
}

/**
* @brief  时间函数(SSL底层会调用时间验证证书是否过期)
**/
//struct tm *lcTime;
//time_t startTime;
//	lcTime = localtime (&startTime);
_ARMABI time_t time(time_t *t)
{
//	time_t it;
	if (t) {
		return *t;
	}
	else
	{
//		startTime = 0;
//		lcTime = localtime (&startTime);
//		it = mktime(lcTime);
//		return it ;
		return 0;
	}
}


/**
* @brief  自定义接收函数(把自己的接收函数放到此函数中)
* @param  None
* @param  None
* @param  None
* @retval None
* @example 
**/
int net_recv_data_len=0; 
int net_recv_data_len_count=0;
char net_recv_buff[2000];
static int custom_ssl_recv( void *ctx, unsigned char *buf, size_t len )
{
	int rbCanReadLen;
	
	if(net_recv_data_len ==0)
	{
		net_recv_data_len=net_recv(net_recv_buff);//调用自己的函数接收数据
		if(net_recv_data_len>0)//有数据
		{
			if(len >= net_recv_data_len)//希望读取的数据个数大于实际的数据个数
			{
				len = net_recv_data_len;
				memcpy(buf, net_recv_buff, len);
				
				net_recv_data_len = 0;
				net_recv_data_len_count=0;
				return len;
			}
			else//实际的数据个数比希望读取的多
			{
				memcpy(buf, net_recv_buff, len);
				net_recv_data_len_count = len;
				return len;
			}
		}
		else
		{
			return MBEDTLS_ERR_NET_RECV_FAILED;
		}
	}
	else
	{
		if(len >= net_recv_data_len - net_recv_data_len_count)//希望读取的数据个数大于实际的数据个数
		{
			len = net_recv_data_len - net_recv_data_len_count;
			memcpy(buf, net_recv_buff+net_recv_data_len_count, len);
			net_recv_data_len = 0;
			net_recv_data_len_count=0;
			return len;
		}
		else//实际的数据个数比希望读取的多
		{
			memcpy(buf, net_recv_buff + net_recv_data_len_count, len);
			net_recv_data_len_count = net_recv_data_len_count + len;
			return len;
		}
	}
}


/*增加发送函数*/
static int custom_ssl_send( void *ctx, unsigned char *buf, size_t len )
{
	ctx = ctx;
	net_send(buf,len);//调用自己的TCP发送函数
	return (int)len;
}

/*设置 debug 输出函数*/
static void my_debug( void *ctx, int level,
                      const char *file, int line, const char *str )
{
	printf("%s:%04d: %s\r\n", file, line, str );
}



int ret;//
const char *pers = "ssl_client1";
mbedtls_entropy_context entropy;
mbedtls_ctr_drbg_context ctr_drbg;
mbedtls_ssl_context ssl;
mbedtls_ssl_config conf;


void ssl_int(void)
{
	mbedtls_ssl_close_notify( &ssl );
	mbedtls_ssl_free( &ssl );
	mbedtls_ssl_config_free( &conf );
	mbedtls_ctr_drbg_free( &ctr_drbg );
	mbedtls_entropy_free( &entropy );
	
	mbedtls_debug_set_threshold( 1 );//
	mbedtls_ssl_init( &ssl );
	mbedtls_ssl_config_init( &conf );
	mbedtls_ctr_drbg_init( &ctr_drbg );
	mbedtls_entropy_init( &entropy );

	printf( "\n  . Seeding the random number generator..." );
	//DRBG---->Deterministic Random Bit Generators 伪随机数产生器
	if( ( ret = mbedtls_ctr_drbg_seed( &ctr_drbg, mbedtls_entropy_func, &entropy,
														 (const unsigned char *) pers,
														 strlen( pers ) ) ) != 0 )
	{
			printf( " failed\n  ! mbedtls_ctr_drbg_seed returned %d\n", ret );
	}
	
	
	//MBEDTLS_SSL_IS_CLIENT 表示配置为客户端
	//MBEDTLS_SSL_TRANSPORT_STREAM 表示传输方式为TLS
	//设置版本， MBEDTLS_SSL_PRESET_DEFAULT 表示 TLS1.0
	if( ( ret = mbedtls_ssl_config_defaults( &conf,
									MBEDTLS_SSL_IS_CLIENT,
									MBEDTLS_SSL_TRANSPORT_STREAM,
									MBEDTLS_SSL_PRESET_DEFAULT ) ) != 0 )
	{
			printf( " failed\n  ! mbedtls_ssl_config_defaults returned %d\r\n", ret );
	}
 
 
	/*设置数字证书检查模式 
	*  MBEDTLS_SSL_VERIFY_NONE:      peer certificate is not checked
	*                        (default on server)
	*                        (insecure on client)
	*
	*  MBEDTLS_SSL_VERIFY_OPTIONAL:  peer certificate is checked, however the
	*                        handshake continues even if verification failed;
	*                        mbedtls_ssl_get_verify_result() can be called after the
	*                        handshake is complete.
	*
	*  MBEDTLS_SSL_VERIFY_REQUIRED:  peer *must* present a valid certificate,
	*                        handshake is aborted if verification failed.
	*                        (default on client)
	*/
	mbedtls_ssl_conf_authmode( &conf, MBEDTLS_SSL_VERIFY_NONE );
	// 配置随机数生成器的回调函数
	mbedtls_ssl_conf_rng( &conf, mbedtls_ctr_drbg_random, &ctr_drbg );
	// 配置调试回调函数
	mbedtls_ssl_conf_dbg( &conf, my_debug, stdout );
	
	// 根据conf设置ssl结构
	if( ( ret = mbedtls_ssl_setup( &ssl, &conf ) ) != 0 )
	{
			mbedtls_printf( " failed\n  ! mbedtls_ssl_setup returned 0x%x\r\n", -ret );
	}

	// 设置host name 用到动态内存分配(单向认证可以屏蔽)
//	if( ( ret = mbedtls_ssl_set_hostname( &ssl, "替换自己证书的CN字段的值" ) ) != 0 )
//	{
//			mbedtls_printf( " failed\n  ! mbedtls_ssl_set_hostname returned %d\r\n", ret );
//	}
	// 设置发送和接收接口
	mbedtls_ssl_set_bio( &ssl, NULL, custom_ssl_send, custom_ssl_recv, NULL );
}


int main(void)
{
  NVIC_Configuration();
	uart_init(115200);	 //串口初始化为115200
	GpioInit();
	DelayInit();

	while(1)
	{
		if(1)//以TCP连接了服务器
		{
			ssl_int();
			/*等待SSL握手成功*/
			while(( ret = mbedtls_ssl_handshake( &ssl ) ) != 0)
			{
				if( ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE )
				{
//						mbedtls_printf( " failed\n  ! mbedtls_ssl_handshake returned %x\r\n", -ret );
					//自行增加超时函数.让TCP重新连接,重新执行.
				}
			}
			
			while(1)
			{
				char *buff = "1111";
				
				mbedtls_ssl_write( &ssl, buff, sizeof(buff)) ;//向服务器发送数据
				
				/*获取服务器的数据*/
				memset( MainBuffer, 0, sizeof( MainBuffer ) );
				MainLen = mbedtls_ssl_read( &ssl, MainBuffer, MainBufferLen-1 );
				if(MainLen>0){//接收到数据(数据长度为 MainLen)
					//处理数据
					//MainBuffer
				}
				
				if(0)//如果网络通信有错误
				{
					break;//重新连接TCP去
				}
			}
			
		}
		
		
	}
}

































