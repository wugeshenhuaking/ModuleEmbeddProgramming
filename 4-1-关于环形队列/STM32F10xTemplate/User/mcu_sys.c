#include "mcu_sys.h"

void NVIC_Configuration(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
}
/*��λоƬ*/
void mcu_sys_reset(void)
{
  __disable_fault_irq();   
	NVIC_SystemReset();
}

