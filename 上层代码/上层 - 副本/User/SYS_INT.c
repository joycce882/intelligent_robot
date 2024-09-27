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

#define usart2_baund  57600//����3�����ʣ�����ָ��ģ�鲨���ʸ��ģ�ע�⣺ָ��ģ��Ĭ��57600��

void SYS_INT(void)//��ʼ������
{
	GPIO_InitTypeDef GPIO_InitStruture;	
	//------------��ʼ��----------
	SystemInit();	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�
	usart2_init(usart2_baund);//��ʼ������2,������ָ��ģ��ͨѶ
	LED_Init();  //LED��ʼ��
//  ds3231_Init();//ʱ��ϵͳ��ʼ��
//	KEY_Init();//��ʼ��KEY
	OLED_Init();//OLED��ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	OnUart_GPIO();

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	//RCC_znitStruture.GPIO_Pin = GPIO_Pin_0;//B8
	GPIO_InitStruture.GPIO_Speed =GPIO_Speed_50MHz;	
	GPIO_InitStruture.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStruture);
	GPIO_SetBits(GPIOB,GPIO_Pin_0);	
	PS_StaGPIO_Init();
//	Timer_Init3();		//��ʼ����ʱ��
//	HC_SR04_Init();		//��ʼ�����������ģ��
}

