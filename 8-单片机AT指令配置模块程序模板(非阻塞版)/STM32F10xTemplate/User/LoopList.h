#ifndef LOOPLIST_H_
#define LOOPLIST_H_

#ifndef LOOPLIST_C_//���û�ж���  AnnularArray_C_
#define LOOPLIST_C_ extern
#else
#define LOOPLIST_C_
#endif

#include <stm32f10x.h>

#define size_tt uint16_t 


#define min(a, b) (a)<(b)?(a):(b)                   ///< ��ȡ��Сֵ

/** ���λ��������ݽṹ */
typedef struct {
    size_tt rbCapacity;//�ռ��С
    uint8_t  *rbHead; //ͷ
    uint8_t  *rbTail; //β
    uint8_t  *rbBuff; //������׵�ַ
}rb_t;



LOOPLIST_C_ rb_t Uart1rb;  //����һ�����ζ��й������

LOOPLIST_C_ void rbCreate(rb_t *rb,u8 *Buff,uint32_t BuffLen);//��������˵��ʼ�����λ�����
LOOPLIST_C_  void rbDelete(rb_t* rb);
LOOPLIST_C_  int32_t rbCapacity(rb_t *rb);//�õ����δ�С
LOOPLIST_C_  int32_t rbCanRead(rb_t *rb);//�ܶ������ݵĸ���
LOOPLIST_C_  int32_t rbCanWrite(rb_t *rb);//��ʣ��Ŀռ�
LOOPLIST_C_  int32_t rbRead(rb_t *rb, void *data, size_tt count);//��ȡ����
LOOPLIST_C_  int32_t rbWrite(rb_t *rb, const void *data, size_tt count);
int32_t PutData(rb_t *rb ,USART_TypeDef *USARTx,uint8_t *buf, uint32_t len);


#endif





























