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


//uint64_t numlen(uint64_t num)//�������ֵĳ���
//{
//    uint64_t len = 1;        // ��ʼ����Ϊ1
//    for(; num > 9; ++len)    // �ж�num�Ƿ����9�����򳤶�+1
//        num /= 10;	         // ʹ�ó����������㣬ֱ��numС��1
//    return len;              // ���س��ȵ�ֵ
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
	while(PS_HandShake(&AS608Addr))              //��AS608ģ������
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
//void TIM3_IRQHandler(void)			//�����жϺ�����������ʱ��ÿ10΢�����time��1
//{
//	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)		//��ȡTIM3��ʱ���ĸ����жϱ�־λ
//	{
//		time++;
//		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);			//��������жϱ�־λ
//	}
//}
}
