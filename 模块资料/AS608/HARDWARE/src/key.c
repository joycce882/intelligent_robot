#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
#include "LED.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////  
								    
//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);//使能PORTA,PORTE时钟

	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15|GPIO_Pin_5|GPIO_Pin_6;//mode KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB1,3,
	//初始化 Key1-->GPIOA.8	  上拉输入
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置上拉输入	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.8

  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键WK_UP所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级3
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure); 
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//使能按键WK_UP所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级3
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure); 


   //GPIOB.15 中断线以及中断初始化配置   下降沿触发
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource15);
	 //GPIOA.8 中断线以及中断初始化配置   下降沿触发
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8);
   //GPIOB.5 中断线以及中断初始化配置   下降沿触发
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource5);
	 //GPIOB.6 中断线以及中断初始化配置   下降沿触发
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource6);

	EXTI_InitStructure.EXTI_Line=EXTI_Line15;	//KEY3
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


	EXTI_InitStructure.EXTI_Line=EXTI_Line8;	//KEY3
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

  EXTI_InitStructure.EXTI_Line=EXTI_Line5;	//KEY3
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

  EXTI_InitStructure.EXTI_Line=EXTI_Line6;	//KEY4
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

}
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，m0de按下
//1，KEY0按下
//2，KEY1按下
//注意此函数有响应优先级,KEY0>KEY1>KEY2
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		
	if(KEY1==0||KEY2==0||KEY3==0||KEY4==0)
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY1==0)return KEY1_PRES;
		else if(KEY2==0)return KEY2_PRES;
		else if(KEY3==0)return KEY3_PRES;
		else if(KEY4==0)return KEY4_PRES;
	}
	else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1)key_up=1;
	return 5;// 无按键按下
}
