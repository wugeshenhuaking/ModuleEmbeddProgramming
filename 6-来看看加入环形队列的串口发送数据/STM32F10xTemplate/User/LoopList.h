#ifndef LOOPLIST_H_
#define LOOPLIST_H_

#ifndef LOOPLIST_C_//如果没有定义  AnnularArray_C_
#define LOOPLIST_C_ extern
#else
#define LOOPLIST_C_
#endif

#include <stm32f10x.h>

#define size_tt uint16_t 


#define min(a, b) (a)<(b)?(a):(b)                   ///< 获取最小值

/** 环形缓冲区数据结构 */
typedef struct {
    size_tt rbCapacity;//空间大小
    uint8_t  *rbHead; //头
    uint8_t  *rbTail; //尾
    uint8_t  *rbBuff; //数组的首地址
}rb_t;



LOOPLIST_C_ rb_t Uart1rb;  //创建一个环形队列管理变量

LOOPLIST_C_ void rbCreate(rb_t *rb,u8 *Buff,uint32_t BuffLen);//创建或者说初始化环形缓冲区
LOOPLIST_C_  void rbDelete(rb_t* rb);
LOOPLIST_C_  int32_t rbCapacity(rb_t *rb);//得到环形大小
LOOPLIST_C_  int32_t rbCanRead(rb_t *rb);//能读出数据的个数
LOOPLIST_C_  int32_t rbCanWrite(rb_t *rb);//还剩余的空间
LOOPLIST_C_  int32_t rbRead(rb_t *rb, void *data, size_tt count);//读取数据
LOOPLIST_C_  int32_t rbWrite(rb_t *rb, const void *data, size_tt count);
int32_t PutData(rb_t *rb ,USART_TypeDef *USARTx,uint8_t *buf, uint32_t len);


#endif





























