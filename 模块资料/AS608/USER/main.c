#include "stm32f10x.h"
#include "SYS_INT.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "oled.h"
#include "delay.h"
#include "usart.h"	 
#include "AS608.h"
#include "USART3.h"
#include "ds3231.h" 
/************************************************
************************************************/
#define Beep PBout(0)




u8 tmp_buf[33];	
u16 ValidN;                                    //模块内有效模板个数
u16 Finger_Num=123;
u16 Set_flag=0;
u16 Add_flag=0;
u16 Del_flag=0;
u16 Ver_flag=0;
u16 Choose_flag=0;
u16 Del_Choose_flag=0;
u16 Del_Move_flag=0;
u16 ID=0;
u16 ID_flag=0;
u16 Del_num=0;
u16 One_flag=0;
//--------函数声明------------指纹相关
void Add_FR(void);  //录指纹
void press_FR(void);//刷指纹
void Del_FR(void);  //删除指纹

int main()
{
//--------初始化---------
	SYS_INT();

//-----------操作层-----------
//------------------------通信检测---------------------
	while(PS_HandShake(&AS608Addr))              //与AS608模块握手
	{
		delay_ms(1000);
		OLED_Show_Str(0, 0, "AS608_OFF <-_->",16);
		delay_ms(1000);	  
	}
	LED1=1;
	Beep=0;
	delay_ms(100);
	Beep=1;
	OLED_Show_Str(0, 0, "AS608__ON <^_^>",16);
	OLED_Show_Str(20, 20, "Connect_OK",16);
	delay_ms(800);
//------------------------开始进入功能区---------------------
	OLED_Clear();
	Beep=1;
 	while(1)
    {
        
   
    }            
	while(1)
	{
							                   //函数功能：清屏
		while(Set_flag==0 && Add_flag==0 && Del_flag==0 && Ver_flag==0)
		{
			//------------------------等待操作---------------------		
		
				//---------------正常模式-------------------	
//			OLED_Show_Str(20, 0, "STM32_AS608",16);
			PS_ValidTempleteNum(&ValidN);              //读库指纹个数
//			OLED_Show_Str(10, 20, "Finger_Num:",16);
//			OLED_Show_IntNum(110, 20, ValidN,2,16);    //函数功能：显示int数字	
//			OLED_Show_Str(20, 35, "Scaning....",16);	
			press_FR();		
		}
		
	//---------------设置模式-------------------
		while(Set_flag==1 && Add_flag==0 && Del_flag==0 && Ver_flag==0)
			{
				OLED_Show_Str(40, 0, "Set_Mode",12);
				OLED_Show_Str(0, 18, "<Add_FR>",16);
				OLED_Show_Str(0, 36,"<Del_FR>",16);
				OLED_Show_Str(0, 48,"<Version>",16);
				
				if(Choose_flag==0)
				{
					delay_ms(200);
					OLED_Show_Str(90, 18, "<<-",16);
					delay_ms(200);
					OLED_Show_Str(90, 18, "   ",16);	
				}
				else if(Choose_flag==1)
				{
					delay_ms(200);
					OLED_Show_Str(90, 36, "<<-",16);
					delay_ms(200);
					OLED_Show_Str(90, 36, "   ",16);
				}
				else if(Choose_flag==2)
				{
					delay_ms(200);
					OLED_Show_Str(90, 48, "<<-",16);
					delay_ms(200);
					OLED_Show_Str(90, 48, "   ",16);
				
				}
			}
	//---------------添加模式-------------------
			while(Set_flag==0 && Add_flag==1 && Del_flag==0 && Ver_flag==0)
			{
				Add_FR();//录指纹	
			}
	//---------------删除模式-------------------
			while(Set_flag==0 && Add_flag==0 && Del_flag==1 && Ver_flag==0)
			{
				Del_FR();
			}
	//---------------版本说明-------------------
			OLED_Clear();
			while(Set_flag==0 && Add_flag==0 && Del_flag==0 && Ver_flag==1)
			{
 				LED0=~LED0;
//				OLED_Show_Str(25, 0, "Version_Note",12);
//				OLED_Show_Str(0, 20, "Designer:",12);
//				OLED_Show_Str(0, 35, "WD162:",12);
//				OLED_Show_Str(0, 50, "TX162",12);
//				OLED_Show_Many_Chinese12X12(40, 35, "李润");
//				OLED_Show_Many_Chinese12X12(70, 35, "陈慧");
//				OLED_Show_Str(0, 50, "Ver3.0",12);
//				OLED_Show_Str(50, 50, "2020/05/10",12);

			}
	}
}

//---------------指纹添加函数-------------------

void Add_FR(void)
{
	u8 i=0,ensure ,processnum=0;
	while(1)
	{
		switch (processnum)
		{
			case 0:
				i++;
				OLED_Clear();
				OLED_Show_Str(10, 0,"Please put Finger",12);//请按手指
				ensure=PS_GetImage();
				if(ensure==0x00) 
				{
					OLED_Show_Str(0, 20,"Finger O",12);//获取到指纹
					ensure=PS_GenChar(CharBuffer1);//生成特征
					if(ensure==0x00)
					{
						OLED_Show_Str(0, 33,"Finger ok I",12);//指纹正确
						Beep=0;
						delay_ms(100);
						Beep=1;
						i=0;
						processnum=1;//跳到第二步						
					}else OLED_Show_Str(0, 33,"Finger no I",12);//指纹有误				
				}else OLED_Show_Str(0, 20,"Finger X",12);//指纹未获取						
				break;
			
			case 1:
				i++;
				OLED_Clear();
				OLED_Show_Str(10, 0,"Finger Again",12);//再按一次手指
				ensure=PS_GetImage();
				if(ensure==0x00) 
				{
					OLED_Show_Str(10, 20,"Finger OO",12);
					ensure=PS_GenChar(CharBuffer2);//生成特征			
					if(ensure==0x00)
					{
						OLED_Show_Str(10, 20,"Finger II",12);//指纹正确
					Beep=0;
					delay_ms(100);
					Beep=1;						
						i=0;
						processnum=2;//跳到第三步
					}else OLED_Show_Str(0, 33,"Finger no II",12);	
				}else OLED_Show_Str(0, 20,"Finger XX",12);		
				break;

			case 2:
				OLED_Clear();
				OLED_Show_Str(20, 0,"Finger Comper",12);//对比两次指纹
				ensure=PS_Match();
				if(ensure==0x00) 
				{
					OLED_Show_Str(0, 20,"Finger Match OK",12);//两次指纹是一样的
					Beep=0;
					delay_ms(100);
					Beep=1;					
					processnum=3;//跳到第四步
				}
				else 
				{
					OLED_Show_Str(0, 20,"Finger Match NO",12);
					OLED_Show_Str(0, 40,"Back To Step 1",12);
					Beep=0;
					delay_ms(100);
					Beep=1;
					i=0;
					processnum=0;//跳回第一步		
				}
				delay_ms(1000);
				break;

			case 3:
				OLED_Clear();
				OLED_Show_Str(10, 0,"Creat Finger Mode",12);//产生一个指纹模板
				ensure=PS_RegModel();
				if(ensure==0x00) 
				{
					OLED_Show_Str(0, 20,"Creat   Success",12);//生成指纹模板成功
					Beep=0;
					delay_ms(100);
					Beep=1;
					processnum=4;//跳到第五步
				}else {processnum=0;OLED_Show_Str(0, 20,"Creat Unsccess",12);}
				delay_ms(1000);
				break;
				
			case 4:
				OLED_Clear();				
				OLED_Show_Str(20, 0,"Creat Mode ID    ",12);//输入ID并按“Enter”保存
				OLED_Show_Str(0, 20,"    0< ID <299   ",12);//输入范围	
			OLED_Show_Str(0, 33,"Input ID:",12);
			while(!ID_flag)
			{
				OLED_Show_IntNum(60, 33, ID,3,12);	
			}
			OLED_Clear();	
				ensure=PS_StoreChar(CharBuffer2,ID);//储存模板
				if(ensure==0x00) 
				{			
					OLED_Show_Str(25, 0,"Add Fingger Ok",12);//添加指纹成功
					OLED_Show_Str(0, 33,"Left ID num:",12);//添加指纹成功
					PS_ValidTempleteNum(&ValidN);//读库指纹个数
					OLED_Show_IntNum(80, 33, 300-ValidN,3,12);//显示剩余指纹个数
					Beep=0;
					delay_ms(100);
					Beep=1;	
					delay_ms(3000);//延时后清除显示
					ID_flag=0;//ID_flag归0
					ID++;//指纹增加一个
					Set_flag=1;
					Add_flag=0;
					Del_flag=0;
					Ver_flag=0;
					return ;
				}else {processnum=0;OLED_Show_Str(0, 45,"Add Fingger NO",12);}					
				break;				
		}
		delay_ms(800);				
	}
}


//刷指纹
void press_FR(void)
{
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
					
				OLED_Show_Str(10, 0, "Find   Finger",16);//搜索指纹成功
				Beep=0;
				delay_ms(100);
				Beep=1;
				delay_ms(100);
				Beep=0;
				delay_ms(100);
				Beep=1;				
				OLED_Show_Str(0, 20, "Finger ID:",16);//搜索到指纹ID
				OLED_Show_Str(0, 40, "Finger Simi rate:",12);//搜索到指纹相似度
				OLED_Show_Str(115, 40, "%",12);//搜索到指纹相似度					
				OLED_Show_IntNum(80, 20, seach.pageID,3,16);    //函数功能：显示int数字
				OLED_Show_IntNum(100, 40, seach.mathscore/4,2,12);    //函数功能：显示int数字	
			} 
			else
			{				
				OLED_Show_Str(10, 0, "Unknow Finger",16);//未搜索到指纹
				LED1_FLASH();				
				Beep=0;
				delay_ms(250);
				Beep=1;
				LED1_FLASH();
				delay_ms(250);
				Beep=0;
				delay_ms(250);
				Beep=1;	
				LED1_FLASH();				
			}				
	  }
		else
			OLED_Show_Str(10, 0, "Create Fail",16);//生成失败
	 delay_ms(1000);//延时后清除显示
		OLED_Clear();
		return ;
	}
}




//删除指纹
void Del_FR(void)
{
	u8  ensure;
	
	OLED_Show_Str(20, 0, "Del Finger",16);//显示删除指纹
	OLED_Show_Str(0,20,"Single_ID:",16);//显示输入ID并按下“Enter”
	OLED_Show_Str(0,40,"Hole___ID:",16);//显示输入ID并按下“Enter”
	delay_ms(50);
	
	if(!Del_Move_flag)
	{
		OLED_Show_Str(80,20,"<<-",16);//显示输入ID并按下“Enter”
		OLED_Show_Str(80,40,"   ",16);//
	}
	else
	{
		OLED_Show_Str(80,20,"   ",16);//
		OLED_Show_Str(80,40,"<<-",16);//
	}
	if(Del_Choose_flag==1)
		{
			ensure=PS_DeletChar(Del_num,1);//删除单个指纹
			Del_flag=0;
			}
		else if(Del_Choose_flag==2)
		{
					ensure=PS_Empty();//清空指纹库
					Del_flag=0;
		}
		
		
	if(ensure==0)
	{	
		OLED_Clear();
		OLED_Show_Str(20, 0, "Del Finger",16);//显示删除指纹
		OLED_Show_Str(10, 40, "Del Finger OK",16);//删除指纹成功	
		delay_ms(500);
		ensure=201;
		Del_num++;
		Set_flag=1;
		Add_flag=0;
		Del_flag=0;
		Ver_flag=0;
		return;
	}
//  else
//		OLED_Show_Str(10, 40, "Del Finger NO",16);	
	delay_ms(1500);//延时后清除显示
	PS_ValidTempleteNum(&ValidN);//读库指纹个数
}


//---------------按键中断处理区-------------------

void EXTI15_10_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line15);  //清除LINE15上的中断标志位
	delay_ms(10);//消抖
//------------------KEY1--------------------	
	if(KEY1==0)	  //按键KEY1
	{
			Set_flag=1;
			LED0=~LED0;
			OLED_Clear();
			delay_ms(100);
	}		   
}


//外部中断9-5服务程序
void EXTI9_5_IRQHandler(void)
{


	delay_ms(10);//消抖
	
	
//------------------KEY2--------------------
//------------------设置模式KEY2--------------------	
	if(Set_flag==1 && Add_flag==0 && Del_flag==0 && Ver_flag==0)
	{	
		if(KEY2==0)	  //按键KEY2
			{
				while(!KEY2);
				Choose_flag++;
				if(Choose_flag==3)
				Choose_flag=0;
				LED0=~LED0;
			}
			EXTI_ClearITPendingBit(EXTI_Line8);  //清除LINE8上的中断标志位		
			}
//------------------添加模式KEY2--------------------		
			else if(Set_flag==0 && Add_flag==1 && Del_flag==0 && Ver_flag==0)
				{
					if(KEY2==0)	  //按键KEY2
						{
							while(!KEY2);
							ID++;
						}
						EXTI_ClearITPendingBit(EXTI_Line8);  //清除LINE8上的中断标志位
						}
				else if(Set_flag==0 && Add_flag==0 && Del_flag==1 && Ver_flag==0)
				{
					if(KEY2==0)	  //按键KEY2
						{
							while(!KEY2);
							Del_Move_flag=~Del_Move_flag;
						}
						EXTI_ClearITPendingBit(EXTI_Line8);  //清除LINE8上的中断标志位
				}
	


//------------------KEY3--------------------		
//------------------设置模式KEY3--------------------	
if(Set_flag==1 && Add_flag==0 && Del_flag==0 && Ver_flag==0)
	{
		EXTI_ClearITPendingBit(EXTI_Line5);  //清除LINE5上的中断标志位
	if(KEY3==0)	  //按键KEY3
		{
			while(!KEY3);
			LED0=~LED0;
				if(Choose_flag==0)
				{
					Add_flag=1;
					Set_flag=0;
					Del_flag=0;
					Ver_flag=0;
					OLED_Clear();
				}
				else if(Choose_flag==1)
					{
						Del_flag=1;
						Set_flag=0;
						Add_flag=0;
						Ver_flag=0;
						OLED_Clear();
					}
					else if(Choose_flag==2)
					{
						Ver_flag=1;
						Set_flag=0;
						Add_flag=0;
						Del_flag=0;

						OLED_Clear();
					}
		}		  
	}
//------------------添加模式KEY3--------------------	
	else if(Set_flag==0 && Add_flag==1 && Del_flag==0 && Ver_flag==0)
		{
			EXTI_ClearITPendingBit(EXTI_Line5);  //清除LINE5上的中断标志位
			if(KEY3==0)	  //按键KEY3
				{
					while(!KEY3);
					LED0=~LED0;
					ID_flag=1;
					Set_flag=1;
					Add_flag=0;
					Del_flag=0;
					Ver_flag=0;
				} 
		}
		else if(Set_flag==0 && Add_flag==0 && Del_flag==1 && Ver_flag==0)
			{
				EXTI_ClearITPendingBit(EXTI_Line5);  //清除LINE5上的中断标志位
				if(KEY3==0)	  //按键KEY3
					{
						while(!KEY3);
						if(!Del_Move_flag)
						{
							Del_Choose_flag=1;
							OLED_Clear();
						}
						else
						{
							Del_Choose_flag=2;
							OLED_Clear();
						}
						LED0=~LED0;
					} 
		}


		
		
		
		
//------------------KEY4--------------------		
		if(Set_flag==1 && Add_flag==0 && Del_flag==0 && Ver_flag==0)
			{		
				if(KEY4==0)	  //按键KEY4
					{
						while(!KEY4);
						LED0=~LED0;
						Set_flag=0;
						Add_flag=0;
						Del_flag=0;
						Ver_flag=0;
						OLED_Clear();
						delay_ms(100);
					}
					EXTI_ClearITPendingBit(EXTI_Line6);  //清除LINE6上的中断标志位	
					}
			else if(Set_flag==0 && Add_flag==1 && Del_flag==0 && Ver_flag==0)
				{		
					if(KEY4==0)	  //按键KEY4
						{
							while(!KEY4);
							LED0=~LED0;
							Set_flag=1;
							Add_flag=0;
							Del_flag=0;
							Ver_flag=0;
							OLED_Clear();
							delay_ms(100);
						}
						EXTI_ClearITPendingBit(EXTI_Line6);  //清除LINE6上的中断标志位	
						}
				else if(Set_flag==0 && Add_flag==0 && Del_flag==1 && Ver_flag==0)
				{		
					if(KEY4==0)	  //按键KEY4
						{
							while(!KEY4);
							LED0=~LED0;
							Set_flag=1;
							Add_flag=0;
							Del_flag=0;
							Ver_flag=0;							
							OLED_Clear();
							delay_ms(100);
						}
						EXTI_ClearITPendingBit(EXTI_Line6);  //清除LINE6上的中断标志位	
						}
				else if(Set_flag==0 && Add_flag==0 && Del_flag==0 && Ver_flag==1)
				{		
					if(KEY4==0)	  //按键KEY4
						{
							while(!KEY4);
							LED0=~LED0;
							Set_flag=1;
							Add_flag=0;
							Del_flag=0;
							Ver_flag=0;
							OLED_Clear();
							delay_ms(100);
						}
						EXTI_ClearITPendingBit(EXTI_Line6);  //清除LINE6上的中断标志位	
						}
}




