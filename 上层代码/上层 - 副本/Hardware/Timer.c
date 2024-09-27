#include "stm32f10x.h"
#include "timer.h" 
 
extern vu16 USART2_RX_STA;

//��ʱ��4�жϷ������		    
void TIM4_IRQHandler(void)
{ 	
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)//�Ǹ����ж�
	{	 			   
		USART2_RX_STA|=1<<15;	//��ǽ������
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //���TIM4�����жϱ�־    
		TIM_Cmd(TIM4, DISABLE);  //�ر�TIM4 
	}	    
}
 
//ͨ�ö�ʱ��4�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ42M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz 
//ͨ�ö�ʱ���жϳ�ʼ��
//����ʼ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��		 
void TIM4_Int_Init(u16 arr,u16 psc)
{	
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//TIM4ʱ��ʹ��    
	
	//��ʱ��TIM4��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM4�ж�,��������ж�
	
	TIM_Cmd(TIM4,ENABLE);//������ʱ��4
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
}


/***********************************************��������*************************************/
//blog.zeruns.tech
void Timer_Init3(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);		//����TIM3ʱ��

	TIM_InternalClockConfig(TIM3);								//����TIM3ʹ���ڲ�ʱ��
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;			//����ṹ�壬���ö�ʱ��
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;	//����1��Ƶ������Ƶ��
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//���ü���ģʽΪ���ϼ���
	TIM_TimeBaseInitStructure.TIM_Period = 10 - 1;			//����������ֵ���ﵽ���ֵ���������¼�����Ϊ��0��ʼ���������Լ���10����10-1,ÿ10΢�봥��һ��
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;			//����ʱ��Ԥ��Ƶ��72-1����ÿ ʱ��Ƶ��(72Mhz)/72=1000000 ��ʱ�����ڼ�������1,ÿ1΢��+1
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;		//�ظ����������߼���ʱ�����У���������0��
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);			//��ʼ��TIM3��ʱ��
	
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);			//��������жϱ�־λ
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);		//���������ж�
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//�����ж����ȼ�����
	
	NVIC_InitTypeDef NVIC_InitStructure;						//����ṹ�壬�����ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;				//ָ���ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//�ж�ʹ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//������ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;			//������Ӧ���ȼ�
	NVIC_Init(&NVIC_InitStructure);								// https://blog.zeruns.tech
	
	TIM_Cmd(TIM3, ENABLE);							//������ʱ��
}

/*
void TIM3_IRQHandler(void)			//�����жϺ���
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)		//��ȡTIM3��ʱ���ĸ����жϱ�־λ
	{
		
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);			//��������жϱ�־λ
	}
}*/



