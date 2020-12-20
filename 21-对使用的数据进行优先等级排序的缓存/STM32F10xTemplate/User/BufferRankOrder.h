#ifndef BufferRankOrder_cc_
#define BufferRankOrder_cc_

#ifndef BufferRankOrder_cx_//���û�ж���
#define BufferRankOrder_cx_ extern
#else
#define BufferRankOrder_cx_
#endif

#include <stm32f10x.h>

//����¼10������
#define BufferRankOrderRowLen 10
//ÿ�����ݵ���󳤶�(�ֽ�)
//ע,���һλ��¼�Ĵ洢���ݵĸ���,ʵ�����洢24�ֽ�
#define BufferRankOrderListLen 25 

BufferRankOrder_cx_ char BufferRankOrder[BufferRankOrderRowLen][BufferRankOrderListLen];


BufferRankOrder_cx_ char BufferRankOrderInsert(char *data,int datalen,char *HoldBuff,int HoldBuffLen,char *error);

#endif

