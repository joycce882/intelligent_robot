#include "SYS_INT.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "oled.h"
#include "delay.h"
#include "usart.h"	 
#include "AS608.h"
#include "ds3231.h"
#include "usart3.h"

#define usart3_baund  57600//串口3波特率，根据指纹模块波特率更改（注意：指纹模块默认57600）

void SYS_INT(void)//初始化函数
{
	GPIO_InitTypeDef GPIO_InitStruture;	
	//------------初始化----------
	SystemInit();	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级
	usart3_init(usart3_baund);//初始化串口2,用于与指纹模块通讯
	LED_Init();  //LED初始化
	delay_init();//延时函数初始化
//  ds3231_Init();//时钟系统初始化
//	KEY_Init();//初始化KEY
	OLED_Init();//OLED初始化
	OLED_On();


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIO的时钟
	
	GPIO_InitStruture.GPIO_Pin = GPIO_Pin_0;//B8
	GPIO_InitStruture.GPIO_Speed =GPIO_Speed_2MHz;	
	GPIO_InitStruture.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStruture);
	GPIO_SetBits(GPIOB,GPIO_Pin_0);	
}