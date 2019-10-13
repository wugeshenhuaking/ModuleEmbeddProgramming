#ifndef __TIME_H_
#define __TIME_H_

#ifndef _TIME_C_
#define _TIME_C_ extern
#else
#define _TIME_C_
#endif

void Delay10uS(void);
void InitTimer0(void);
void DelayMs(int s);
void delay1ms(void);

#endif

