#define _TIME_C_
#include "include.h"

int TimeCnt = 0;

void Delay10uS()
{
  nop_();
	nop_();
	nop_();
	nop_();
	nop_();
	nop_();
}

void DelayMs(int s)
{
	while(s--)
  {
    delay1ms();
  }
}

void delay1ms(void)   //��� -0.651041666667us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=142;b>0;b--)
            for(a=2;a>0;a--);
}

//��ʱ����ʼ��
void InitTimer0(void)
{
    TMOD |= 0x01;//��|=��ֹ���ó�ͻ
    TH0 = (65536 - 5000)/256;
    TL0 = (65536 - 5000)%256;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}

void Timer0Interrupt(void) interrupt 1
{
	TH0 = (65536 - 5000)/256;
	TL0 = (65536 - 5000)%256;
	
	TimeCnt ++;
	
	if (UsartReadCnt != 0)//������յ�������
	{
			if (UsartIdleCnt == UsartReadCnt)//���ݸ���һ��ʱ��û�˱仯
			{
				UsartReadCntCopy = UsartReadCnt;
				UsartReadCnt = 0;//�������ݸ���
				UsartIdleCnt = 0;//����
				UsartFlage = 1;
			}
			else
			{
				UsartIdleCnt = UsartReadCnt;
			}
	}
}
