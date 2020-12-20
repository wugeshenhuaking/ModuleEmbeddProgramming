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
char MainBuffer[MainBufferLen];//��������,ȫ��ͨ��
u32  MainLen=0;      //ȫ��ͨ�ñ���


/*��������������ݺ���*/
int net_recv(char *data){}
/*����TCP�������ݺ���*/
int net_send(char *data,int len){}


/*���������*/
int mbedtls_hardware_poll( void *data,
                    unsigned char *output, size_t len, size_t *olen )
{
	unsigned long randomValue = ((rand()*20) + 1000);//���������
	((void) data);
	*olen = 0;
	
	if( len < sizeof(unsigned long) ) return( 0 );	

	memcpy( output, &randomValue, sizeof(unsigned long) );
	*olen = sizeof(unsigned long);
  return 0;
}

/**
* @brief  ʱ�亯��(SSL�ײ�����ʱ����֤֤���Ƿ����)
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
* @brief  �Զ�����պ���(���Լ��Ľ��պ����ŵ��˺�����)
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
		net_recv_data_len=net_recv(net_recv_buff);//�����Լ��ĺ�����������
		if(net_recv_data_len>0)//������
		{
			if(len >= net_recv_data_len)//ϣ����ȡ�����ݸ�������ʵ�ʵ����ݸ���
			{
				len = net_recv_data_len;
				memcpy(buf, net_recv_buff, len);
				
				net_recv_data_len = 0;
				net_recv_data_len_count=0;
				return len;
			}
			else//ʵ�ʵ����ݸ�����ϣ����ȡ�Ķ�
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
		if(len >= net_recv_data_len - net_recv_data_len_count)//ϣ����ȡ�����ݸ�������ʵ�ʵ����ݸ���
		{
			len = net_recv_data_len - net_recv_data_len_count;
			memcpy(buf, net_recv_buff+net_recv_data_len_count, len);
			net_recv_data_len = 0;
			net_recv_data_len_count=0;
			return len;
		}
		else//ʵ�ʵ����ݸ�����ϣ����ȡ�Ķ�
		{
			memcpy(buf, net_recv_buff + net_recv_data_len_count, len);
			net_recv_data_len_count = net_recv_data_len_count + len;
			return len;
		}
	}
}


/*���ӷ��ͺ���*/
static int custom_ssl_send( void *ctx, unsigned char *buf, size_t len )
{
	ctx = ctx;
	net_send(buf,len);//�����Լ���TCP���ͺ���
	return (int)len;
}

/*���� debug �������*/
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
	//DRBG---->Deterministic Random Bit Generators α�����������
	if( ( ret = mbedtls_ctr_drbg_seed( &ctr_drbg, mbedtls_entropy_func, &entropy,
														 (const unsigned char *) pers,
														 strlen( pers ) ) ) != 0 )
	{
			printf( " failed\n  ! mbedtls_ctr_drbg_seed returned %d\n", ret );
	}
	
	
	//MBEDTLS_SSL_IS_CLIENT ��ʾ����Ϊ�ͻ���
	//MBEDTLS_SSL_TRANSPORT_STREAM ��ʾ���䷽ʽΪTLS
	//���ð汾�� MBEDTLS_SSL_PRESET_DEFAULT ��ʾ TLS1.0
	if( ( ret = mbedtls_ssl_config_defaults( &conf,
									MBEDTLS_SSL_IS_CLIENT,
									MBEDTLS_SSL_TRANSPORT_STREAM,
									MBEDTLS_SSL_PRESET_DEFAULT ) ) != 0 )
	{
			printf( " failed\n  ! mbedtls_ssl_config_defaults returned %d\r\n", ret );
	}
 
 
	/*��������֤����ģʽ 
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
	// ����������������Ļص�����
	mbedtls_ssl_conf_rng( &conf, mbedtls_ctr_drbg_random, &ctr_drbg );
	// ���õ��Իص�����
	mbedtls_ssl_conf_dbg( &conf, my_debug, stdout );
	
	// ����conf����ssl�ṹ
	if( ( ret = mbedtls_ssl_setup( &ssl, &conf ) ) != 0 )
	{
			mbedtls_printf( " failed\n  ! mbedtls_ssl_setup returned 0x%x\r\n", -ret );
	}

	// ����host name �õ���̬�ڴ����(������֤��������)
//	if( ( ret = mbedtls_ssl_set_hostname( &ssl, "�滻�Լ�֤���CN�ֶε�ֵ" ) ) != 0 )
//	{
//			mbedtls_printf( " failed\n  ! mbedtls_ssl_set_hostname returned %d\r\n", ret );
//	}
	// ���÷��ͺͽ��սӿ�
	mbedtls_ssl_set_bio( &ssl, NULL, custom_ssl_send, custom_ssl_recv, NULL );
}


int main(void)
{
  NVIC_Configuration();
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	GpioInit();
	DelayInit();

	while(1)
	{
		if(1)//��TCP�����˷�����
		{
			ssl_int();
			/*�ȴ�SSL���ֳɹ�*/
			while(( ret = mbedtls_ssl_handshake( &ssl ) ) != 0)
			{
				if( ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE )
				{
//						mbedtls_printf( " failed\n  ! mbedtls_ssl_handshake returned %x\r\n", -ret );
					//�������ӳ�ʱ����.��TCP��������,����ִ��.
				}
			}
			
			while(1)
			{
				char *buff = "1111";
				
				mbedtls_ssl_write( &ssl, buff, sizeof(buff)) ;//���������������
				
				/*��ȡ������������*/
				memset( MainBuffer, 0, sizeof( MainBuffer ) );
				MainLen = mbedtls_ssl_read( &ssl, MainBuffer, MainBufferLen-1 );
				if(MainLen>0){//���յ�����(���ݳ���Ϊ MainLen)
					//��������
					//MainBuffer
				}
				
				if(0)//�������ͨ���д���
				{
					break;//��������TCPȥ
				}
			}
			
		}
		
		
	}
}

































