#include "OLED.h"
#include "AS608.h"
#include "stm32f10x.h"
#include "FingerUse.h"
#include "sys.h"
#include "SYS_INT.h"
#include "Delay.h"
#include "LED.h"
#include "Jq8900.h"
//void Add_FR(void)
//{
//	u8 i=0,ensure ,processnum=0;
//	while(1)
//	{
//		switch (processnum)
//		{
//			case 0:
//				i++;
//				OLED_Clear();
//				OLED_ShowString(1,1,"Please put Finger");//请按手指
//				ensure=PS_GetImage();
//				if(ensure==0x00) 
//				{
//					OLED_Show_Str(2, 2,"Finger O");//获取到指纹
//					ensure=PS_GenChar(CharBuffer1);//生成特征
//					if(ensure==0x00)
//					{
//						OLED_Show_Str(3,2,"Finger ok I");//指纹正确
//						Beep=0;
//						delay_ms(100);
//						Beep=1;
//						i=0;
//						processnum=1;//跳到第二步						
//					}else OLED_Show_Str(3, 2,"Finger no I");//指纹有误				
//				}else OLED_Show_Str(2, 2,"Finger X");//指纹未获取						
//				break;
//			
//			case 1:
//				i++;
//				OLED_Clear();
//				OLED_Show_Str(1, 2,"Finger Again");//再按一次手指
//				ensure=PS_GetImage();
//				if(ensure==0x00) 
//				{
//					OLED_Show_Str(2,2,"Finger OO");
//					ensure=PS_GenChar(CharBuffer2);//生成特征			
//					if(ensure==0x00)
//					{
//						OLED_Show_Str(3, 2,"Finger II");//指纹正确
//					Beep=0;
//					delay_ms(100);
//					Beep=1;						
//						i=0;
//						processnum=2;//跳到第三步
//					}else OLED_Show_Str(3, 2,"Finger no II");	
//				}else OLED_Show_Str(2, 2,"Finger XX");		
//				break;

//			case 2:
//				OLED_Clear();
//				OLED_Show_Str(20, 0,"Finger Comper",12);//对比两次指纹
//				ensure=PS_Match();
//				if(ensure==0x00) 
//				{
//					OLED_Show_Str(0, 20,"Finger Match OK",12);//两次指纹是一样的
//					Beep=0;
//					delay_ms(100);
//					Beep=1;					
//					processnum=3;//跳到第四步
//				}
//				else 
//				{
//					OLED_Show_Str(0, 20,"Finger Match NO",12);
//					OLED_Show_Str(0, 40,"Back To Step 1",12);
//					Beep=0;
//					delay_ms(100);
//					Beep=1;
//					i=0;
//					processnum=0;//跳回第一步		
//				}
//				delay_ms(1000);
//				break;

//			case 3:
//				OLED_Clear();
//				OLED_Show_Str(10, 0,"Creat Finger Mode",12);//产生一个指纹模板
//				ensure=PS_RegModel();
//				if(ensure==0x00) 
//				{
//					OLED_Show_Str(0, 20,"Creat   Success",12);//生成指纹模板成功
//					Beep=0;
//					delay_ms(100);
//					Beep=1;
//					processnum=4;//跳到第五步
//				}else {processnum=0;OLED_Show_Str(0, 20,"Creat Unsccess",12);}
//				delay_ms(1000);
//				break;
//				
//			case 4:
//				OLED_Clear();				
//				OLED_Show_Str(20, 0,"Creat Mode ID    ",12);//输入ID并按“Enter”保存
//				OLED_Show_Str(0, 20,"    0< ID <299   ",12);//输入范围	
//			OLED_Show_Str(0, 33,"Input ID:",12);
//			while(!ID_flag)
//			{
//				OLED_Show_IntNum(60, 33, ID,3,12);	
//			}
//			OLED_Clear();	
//				ensure=PS_StoreChar(CharBuffer2,ID);//储存模板
//				if(ensure==0x00) 
//				{			
//					OLED_Show_Str(25, 0,"Add Fingger Ok",12);//添加指纹成功
//					OLED_Show_Str(0, 33,"Left ID num:",12);//添加指纹成功
//					PS_ValidTempleteNum(&ValidN);//读库指纹个数
//					OLED_Show_IntNum(80, 33, 300-ValidN,3,12);//显示剩余指纹个数
//					Beep=0;
//					delay_ms(100);
//					Beep=1;	
//					delay_ms(3000);//延时后清除显示
//					ID_flag=0;//ID_flag归0
//					ID++;//指纹增加一个
//					Set_flag=1;
//					Add_flag=0;
//					Del_flag=0;
//					Ver_flag=0;
//					return ;
//				}else {processnum=0;OLED_Show_Str(0, 45,"Add Fingger NO",12);}					
//				break;				
//		}
//		delay_ms(800);				
//	}
//}


//刷指纹
void press_FR(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
	SearchResult seach;
	u8 ensure;
	char *str;
	ensure=PS_GetImage();
	if(ensure==0x00)//获取图像成功 
	{	
		OLED_Clear();
		ensure=PS_GenChar(CharBuffer1);
		if(ensure==0x00) //生成特征成功
		{		
			ensure=PS_HighSpeedSearch(CharBuffer1,0,300,&seach);
			if(ensure==0x00)//搜索成功
			{
				OLED_ShowString(1, 2, "Find Finger");//搜索指纹成功
				GPIO_SetBits(GPIOA, GPIO_Pin_7);
				Delay_ms(100);
				GPIO_ResetBits(GPIOA, GPIO_Pin_7);
				Delay_ms(100);
				GPIO_SetBits(GPIOA, GPIO_Pin_7);
				Delay_ms(100);
				GPIO_ResetBits(GPIOA, GPIO_Pin_7);				
				OLED_ShowString(2, 2, "Finger ID:");//搜索到指纹ID
				OLED_ShowString(3, 2, "Finger Simi rate:");//搜索到指纹相似度
				OLED_ShowString(4, 5, "%");//搜索到指纹相似度					
				OLED_ShowNum(2, 12, seach.pageID,2);    //函数功能：显示int数字
				OLED_ShowNum(4, 2, seach.mathscore/4,2);    //函数功能：显示int数字	
				if(seach.pageID == 1)
				{
					Delay_ms(500);
					
					show_number3();
					Delay_s(1);
					GPIO_ResetBits(GPIOA,GPIO_Pin_1);
					Delay_s(5);
					show_number4();
					Delay_s(2);
					GPIO_SetBits(GPIOA,GPIO_Pin_1);
					OLED_Clear();
					OLED_ShowString(1,2,"Successful");
					show_number5();
					Delay_s(5);
					OLED_Clear();
					OLED_ShowString(1,2,"A--two times one day");
					OLED_ShowString(2,2,"B--one times one day");
					show_number6();
					
				}
			} 
			else
			{	
				show_number9();
				OLED_ShowString(1, 2, "Unknow Finger");//未搜索到指纹
				LED1_FLASH();				
				Delay_ms(250);
				GPIO_SetBits(GPIOA, GPIO_Pin_7);
				LED1_FLASH();
				Delay_ms(250);
				GPIO_ResetBits(GPIOA,GPIO_Pin_7);
				Delay_ms(250);
				GPIO_SetBits(GPIOA, GPIO_Pin_7);
				LED1_FLASH();				
			}				
	  }
		else
		OLED_ShowString(1, 2, "Create Fail");//生成失败
		Delay_ms(1000);//延时后清除显示
		OLED_Clear();
		return ;
	}
	else
		OLED_ShowString(1,2,"FALSE");
	return ;
}




