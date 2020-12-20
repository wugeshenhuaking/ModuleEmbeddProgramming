#ifndef BufferRankOrder_cc_
#define BufferRankOrder_cc_

#ifndef BufferRankOrder_cx_//如果没有定义
#define BufferRankOrder_cx_ extern
#else
#define BufferRankOrder_cx_
#endif

#include <stm32f10x.h>

//最多记录10条数据
#define BufferRankOrderRowLen 10
//每条数据的最大长度(字节)
//注,最后一位记录的存储数据的个数,实际最大存储24字节
#define BufferRankOrderListLen 25 

BufferRankOrder_cx_ char BufferRankOrder[BufferRankOrderRowLen][BufferRankOrderListLen];


BufferRankOrder_cx_ char BufferRankOrderInsert(char *data,int datalen,char *HoldBuff,int HoldBuffLen,char *error);

#endif

