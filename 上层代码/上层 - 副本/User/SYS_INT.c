#include "SYS_INT.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "oled.h"
#include "delay.h"
#include "usart3.h"	 
#include "AS608.h"
#include "usart3.h"
#include "SYS_INT.h"
#include "Jq8900.h"
#include "wave.h"

#define usart2_baund  57600//串口3波特率，根据指纹模块波特率更改（注意：指纹模块默认57600）

void SYS_INT(void)//初始化函数
{
	GPIO_InitTypeDef GPIO_InitStruture;	
	//------------初始化----------
	SystemInit();	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级
	usart2_init(usart2_baund);//初始化串口2,用于与指纹模块通讯
	LED_Init();  //LED初始化
//  ds3231_Init();//时钟系统初始化
//	KEY_Init();//初始化KEY
	OLED_Init();//OLED初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	OnUart_GPIO();

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	//RCC_znitStruture.GPIO_Pin = GPIO_Pin_0;//B8
	GPIO_InitStruture.GPIO_Speed =GPIO_Speed_50MHz;	
	GPIO_InitStruture.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStruture);
	GPIO_SetBits(GPIOB,GPIO_Pin_0);	
	PS_StaGPIO_Init();
//	Timer_Init3();		//初始化定时器
//	HC_SR04_Init();		//初始化超声波测距模块
}

