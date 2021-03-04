#ifndef DATA_PARSE_Cc_
#define DATA_PARSE_Cc_

#ifndef DATA_PARSE_Cx_//如果没有定义
#define DATA_PARSE_Cx_ extern
#else
#define DATA_PARSE_Cx_
#endif

#include "stm32f4xx_conf.h"

typedef union union_resolve
{
	u32   u32_data;
	char  char_table[4];
}union_resolve;

DATA_PARSE_Cx_ union_resolve union_resolve_value;


#endif
