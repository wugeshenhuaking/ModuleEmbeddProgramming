/**
  ******************************************************************************
  * @file    key.c
  * @author  fengwu yang
  * @version V1.0.0
  * @date    2019/10/12
  * @brief   按键检测模板
  ******************************************************************************
  一,使用说明:检测引脚(PB5)
		1,把以下程序放在1ms定时器中断中
			if(KeySmartConfig[1])
				KeySmartConfig[5]++;
			else
				KeySmartConfig[5]=0;

			if(KeySmartConfig[2])
				KeySmartConfig[6]++;
			else
				KeySmartConfig[6]=0;
		
		2,主循环调用使用
			while(1)
			{
				SmartConfigKey();
				
				//例1:检测到按键按下执行某段代码
				if(KeySmartConfig[3] == 1)
				{
					KeySmartConfig[3] = 0;//清零以后,只有按键松开再按下的时候才会进入
					//执行的代码
				}

				//例2:检测到按键按下,然后根据按下时间执行某段代码
				if(KeySmartConfig[3] == 1)
				{
					if(KeySmartConfig[5]>=3000)//按下时间大于3S
					{
						KeySmartConfig[3] = 0;//清零以后,只有按键松开再按下的时候才会进入
						//执行的代码
					}
				}
				
				//例3:检测到按键松开执行某段代码
				if(KeySmartConfig[4] == 1)
				{
					KeySmartConfig[4] = 0;//清零以后,只有按键按下然后松开的时候才会进入
					//执行的代码
				}
				
				//例4:检测到按键松开,然后根据松开时间执行某段代码
				if(KeySmartConfig[4] == 1)
				{
					if(KeySmartConfig[6]>=3000)//松开时间大于3S
					{
						KeySmartConfig[4] = 0;//清零以后,只有按键按下再松开的时候才会进入
						//执行的代码
					}
				}
			}
  ******************************************************************************
  */

#define __KEY_C_
#include "include.h"

int KeySmartConfig[7]={0};//消抖变量 按下标记 松开标记 按下标记拷贝  松开标记拷贝 按下时间(Ms) 松开时间(Ms)
	
/**
* @brief  按键处理
* @param  
* @param  None
* @param  None
* @retval None
* @example 
**/
void SmartConfigKey(void)
{
  if(SmartConfigKeyPinIn == KeySmartConfigDown)
	{
		if(KeySmartConfig[1] == 0)
		{
			KeySmartConfig[0]++;
			if(KeySmartConfig[0]>=500)//按下以后进入
			{
				KeySmartConfig[0] = 0;//Cnt
				KeySmartConfig[2] = 0;//UP
				KeySmartConfig[1] = 1;//Down
				KeySmartConfig[3] = 1;//DownCopy
				KeySmartConfig[4] = 0;//UpCopy
			}
		}
	}
	else
	{
		KeySmartConfig[0]++;
		if(KeySmartConfig[0]>2000)
		{
			KeySmartConfig[0]=0;
			if(KeySmartConfig[1]==1)//按下后松开后进入
			{
				KeySmartConfig[2] = 1;//UP
				KeySmartConfig[1] = 0;//Down
				KeySmartConfig[3] = 0;//DownCopy
				KeySmartConfig[4] = 1;//UpCopy
			}
		}
	}
}
