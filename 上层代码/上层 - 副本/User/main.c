#include <stdint.h>
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "sys.h"
#include "AS608.h"
#include "Usart3.h"
#include "FingerUse.h"
#include "Timer.h"
#include "LED.h"
#include "SYS_INT.h"
#include "Jq8900.h"
//#include "wave.h"


//uint64_t numlen(uint64_t num)//计算数字的长度
//{
//    uint64_t len = 1;        // 初始长度为1
//    for(; num > 9; ++len)    // 判断num是否大于9，否则长度+1
//        num /= 10;	         // 使用除法进行运算，直到num小于1
//    return len;              // 返回长度的值
//}

int main(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	SYS_INT();
	
	OLED_ShowString(1, 2, "HELLO");
	Delay_ms(1000);
	show_number1();
	OLED_ShowString(2,2,"TRUE");
	while(PS_HandShake(&AS608Addr))              //与AS608模块握手
	{
		OLED_Clear();
		Delay_ms(2000);
		OLED_ShowString(1, 2, "AS608_OFF <-_->");
		Delay_ms(2000);	  
	}
	
	Delay_s(2);
	show_number7();

	
	LED1=0;
	GPIO_SetBits(GPIOA, GPIO_Pin_7);
	Delay_ms(5000);
	GPIO_ResetBits(GPIOA, GPIO_Pin_7);
	LED1=1;
	OLED_ShowString(2, 2, "AS608__ON <^_^>");
	OLED_ShowString(3, 2, "Connect_OK");
	show_number2();
	Delay_s(5);
	OLED_Clear();
	press_FR();
	while (1)
	{


		
	}
//void TIM3_IRQHandler(void)			//更新中断函数，用来计时，每10微秒变量time加1
//{
//	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)		//获取TIM3定时器的更新中断标志位
//	{
//		time++;
//		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);			//清除更新中断标志位
//	}
//}
}
