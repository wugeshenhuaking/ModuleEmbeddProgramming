#include "sys.h"

/**
* @brief   ��λоƬ
* @param   None
* @param   None
* @param   None
* @retval  None
* @warning None
* @example 
**/
void system_reset(void)
{
  __disable_fault_irq();
	NVIC_SystemReset();
}

