#ifndef __TIMER_H
#define __TIMER_H

#ifndef _TIME_C_//如果没有定义  _TIME_C_
#define _TIME_Ex_ extern
#else
#define _TIME_Ex_
#endif

#include "stm32f10x.h"

_TIME_Ex_ int timer2Value;

_TIME_Ex_ void Timer2Init(void);
#endif

