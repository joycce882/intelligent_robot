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
u16 ValidN;                                    //ģ������Чģ�����
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
//--------��������------------ָ�����
void Add_FR(void);  //¼ָ��
void press_FR(void);//ˢָ��
void Del_FR(void);  //ɾ��ָ��

int main()
{
//--------��ʼ��---------
	SYS_INT();

//-----------������-----------
//------------------------ͨ�ż��---------------------
	while(PS_HandShake(&AS608Addr))              //��AS608ģ������
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
//------------------------��ʼ���빦����---------------------
	OLED_Clear();
	Beep=1;
 	while(1)
    {
        
   
    }            
	while(1)
	{
							                   //�������ܣ�����
		while(Set_flag==0 && Add_flag==0 && Del_flag==0 && Ver_flag==0)
		{
			//------------------------�ȴ�����---------------------		
		
				//---------------����ģʽ-------------------	
//			OLED_Show_Str(20, 0, "STM32_AS608",16);
			PS_ValidTempleteNum(&ValidN);              //����ָ�Ƹ���
//			OLED_Show_Str(10, 20, "Finger_Num:",16);
//			OLED_Show_IntNum(110, 20, ValidN,2,16);    //�������ܣ���ʾint����	
//			OLED_Show_Str(20, 35, "Scaning....",16);	
			press_FR();		
		}
		
	//---------------����ģʽ-------------------
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
	//---------------���ģʽ-------------------
			while(Set_flag==0 && Add_flag==1 && Del_flag==0 && Ver_flag==0)
			{
				Add_FR();//¼ָ��	
			}
	//---------------ɾ��ģʽ-------------------
			while(Set_flag==0 && Add_flag==0 && Del_flag==1 && Ver_flag==0)
			{
				Del_FR();
			}
	//---------------�汾˵��-------------------
			OLED_Clear();
			while(Set_flag==0 && Add_flag==0 && Del_flag==0 && Ver_flag==1)
			{
 				LED0=~LED0;
//				OLED_Show_Str(25, 0, "Version_Note",12);
//				OLED_Show_Str(0, 20, "Designer:",12);
//				OLED_Show_Str(0, 35, "WD162:",12);
//				OLED_Show_Str(0, 50, "TX162",12);
//				OLED_Show_Many_Chinese12X12(40, 35, "����");
//				OLED_Show_Many_Chinese12X12(70, 35, "�»�");
//				OLED_Show_Str(0, 50, "Ver3.0",12);
//				OLED_Show_Str(50, 50, "2020/05/10",12);

			}
	}
}

//---------------ָ����Ӻ���-------------------

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
				OLED_Show_Str(10, 0,"Please put Finger",12);//�밴��ָ
				ensure=PS_GetImage();
				if(ensure==0x00) 
				{
					OLED_Show_Str(0, 20,"Finger O",12);//��ȡ��ָ��
					ensure=PS_GenChar(CharBuffer1);//��������
					if(ensure==0x00)
					{
						OLED_Show_Str(0, 33,"Finger ok I",12);//ָ����ȷ
						Beep=0;
						delay_ms(100);
						Beep=1;
						i=0;
						processnum=1;//�����ڶ���						
					}else OLED_Show_Str(0, 33,"Finger no I",12);//ָ������				
				}else OLED_Show_Str(0, 20,"Finger X",12);//ָ��δ��ȡ						
				break;
			
			case 1:
				i++;
				OLED_Clear();
				OLED_Show_Str(10, 0,"Finger Again",12);//�ٰ�һ����ָ
				ensure=PS_GetImage();
				if(ensure==0x00) 
				{
					OLED_Show_Str(10, 20,"Finger OO",12);
					ensure=PS_GenChar(CharBuffer2);//��������			
					if(ensure==0x00)
					{
						OLED_Show_Str(10, 20,"Finger II",12);//ָ����ȷ
					Beep=0;
					delay_ms(100);
					Beep=1;						
						i=0;
						processnum=2;//����������
					}else OLED_Show_Str(0, 33,"Finger no II",12);	
				}else OLED_Show_Str(0, 20,"Finger XX",12);		
				break;

			case 2:
				OLED_Clear();
				OLED_Show_Str(20, 0,"Finger Comper",12);//�Ա�����ָ��
				ensure=PS_Match();
				if(ensure==0x00) 
				{
					OLED_Show_Str(0, 20,"Finger Match OK",12);//����ָ����һ����
					Beep=0;
					delay_ms(100);
					Beep=1;					
					processnum=3;//�������Ĳ�
				}
				else 
				{
					OLED_Show_Str(0, 20,"Finger Match NO",12);
					OLED_Show_Str(0, 40,"Back To Step 1",12);
					Beep=0;
					delay_ms(100);
					Beep=1;
					i=0;
					processnum=0;//���ص�һ��		
				}
				delay_ms(1000);
				break;

			case 3:
				OLED_Clear();
				OLED_Show_Str(10, 0,"Creat Finger Mode",12);//����һ��ָ��ģ��
				ensure=PS_RegModel();
				if(ensure==0x00) 
				{
					OLED_Show_Str(0, 20,"Creat   Success",12);//����ָ��ģ��ɹ�
					Beep=0;
					delay_ms(100);
					Beep=1;
					processnum=4;//�������岽
				}else {processnum=0;OLED_Show_Str(0, 20,"Creat Unsccess",12);}
				delay_ms(1000);
				break;
				
			case 4:
				OLED_Clear();				
				OLED_Show_Str(20, 0,"Creat Mode ID    ",12);//����ID������Enter������
				OLED_Show_Str(0, 20,"    0< ID <299   ",12);//���뷶Χ	
			OLED_Show_Str(0, 33,"Input ID:",12);
			while(!ID_flag)
			{
				OLED_Show_IntNum(60, 33, ID,3,12);	
			}
			OLED_Clear();	
				ensure=PS_StoreChar(CharBuffer2,ID);//����ģ��
				if(ensure==0x00) 
				{			
					OLED_Show_Str(25, 0,"Add Fingger Ok",12);//���ָ�Ƴɹ�
					OLED_Show_Str(0, 33,"Left ID num:",12);//���ָ�Ƴɹ�
					PS_ValidTempleteNum(&ValidN);//����ָ�Ƹ���
					OLED_Show_IntNum(80, 33, 300-ValidN,3,12);//��ʾʣ��ָ�Ƹ���
					Beep=0;
					delay_ms(100);
					Beep=1;	
					delay_ms(3000);//��ʱ�������ʾ
					ID_flag=0;//ID_flag��0
					ID++;//ָ������һ��
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


//ˢָ��
void press_FR(void)
{
	SearchResult seach;
	u8 ensure;
	char *str;
	ensure=PS_GetImage();
	if(ensure==0x00)//��ȡͼ��ɹ� 
	{	
		OLED_Clear();
		ensure=PS_GenChar(CharBuffer1);
		if(ensure==0x00) //���������ɹ�
		{		
			ensure=PS_HighSpeedSearch(CharBuffer1,0,300,&seach);
			if(ensure==0x00)//�����ɹ�
			{
					
				OLED_Show_Str(10, 0, "Find   Finger",16);//����ָ�Ƴɹ�
				Beep=0;
				delay_ms(100);
				Beep=1;
				delay_ms(100);
				Beep=0;
				delay_ms(100);
				Beep=1;				
				OLED_Show_Str(0, 20, "Finger ID:",16);//������ָ��ID
				OLED_Show_Str(0, 40, "Finger Simi rate:",12);//������ָ�����ƶ�
				OLED_Show_Str(115, 40, "%",12);//������ָ�����ƶ�					
				OLED_Show_IntNum(80, 20, seach.pageID,3,16);    //�������ܣ���ʾint����
				OLED_Show_IntNum(100, 40, seach.mathscore/4,2,12);    //�������ܣ���ʾint����	
			} 
			else
			{				
				OLED_Show_Str(10, 0, "Unknow Finger",16);//δ������ָ��
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
			OLED_Show_Str(10, 0, "Create Fail",16);//����ʧ��
	 delay_ms(1000);//��ʱ�������ʾ
		OLED_Clear();
		return ;
	}
}




//ɾ��ָ��
void Del_FR(void)
{
	u8  ensure;
	
	OLED_Show_Str(20, 0, "Del Finger",16);//��ʾɾ��ָ��
	OLED_Show_Str(0,20,"Single_ID:",16);//��ʾ����ID�����¡�Enter��
	OLED_Show_Str(0,40,"Hole___ID:",16);//��ʾ����ID�����¡�Enter��
	delay_ms(50);
	
	if(!Del_Move_flag)
	{
		OLED_Show_Str(80,20,"<<-",16);//��ʾ����ID�����¡�Enter��
		OLED_Show_Str(80,40,"   ",16);//
	}
	else
	{
		OLED_Show_Str(80,20,"   ",16);//
		OLED_Show_Str(80,40,"<<-",16);//
	}
	if(Del_Choose_flag==1)
		{
			ensure=PS_DeletChar(Del_num,1);//ɾ������ָ��
			Del_flag=0;
			}
		else if(Del_Choose_flag==2)
		{
					ensure=PS_Empty();//���ָ�ƿ�
					Del_flag=0;
		}
		
		
	if(ensure==0)
	{	
		OLED_Clear();
		OLED_Show_Str(20, 0, "Del Finger",16);//��ʾɾ��ָ��
		OLED_Show_Str(10, 40, "Del Finger OK",16);//ɾ��ָ�Ƴɹ�	
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
	delay_ms(1500);//��ʱ�������ʾ
	PS_ValidTempleteNum(&ValidN);//����ָ�Ƹ���
}


//---------------�����жϴ�����-------------------

void EXTI15_10_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line15);  //���LINE15�ϵ��жϱ�־λ
	delay_ms(10);//����
//------------------KEY1--------------------	
	if(KEY1==0)	  //����KEY1
	{
			Set_flag=1;
			LED0=~LED0;
			OLED_Clear();
			delay_ms(100);
	}		   
}


//�ⲿ�ж�9-5�������
void EXTI9_5_IRQHandler(void)
{


	delay_ms(10);//����
	
	
//------------------KEY2--------------------
//------------------����ģʽKEY2--------------------	
	if(Set_flag==1 && Add_flag==0 && Del_flag==0 && Ver_flag==0)
	{	
		if(KEY2==0)	  //����KEY2
			{
				while(!KEY2);
				Choose_flag++;
				if(Choose_flag==3)
				Choose_flag=0;
				LED0=~LED0;
			}
			EXTI_ClearITPendingBit(EXTI_Line8);  //���LINE8�ϵ��жϱ�־λ		
			}
//------------------���ģʽKEY2--------------------		
			else if(Set_flag==0 && Add_flag==1 && Del_flag==0 && Ver_flag==0)
				{
					if(KEY2==0)	  //����KEY2
						{
							while(!KEY2);
							ID++;
						}
						EXTI_ClearITPendingBit(EXTI_Line8);  //���LINE8�ϵ��жϱ�־λ
						}
				else if(Set_flag==0 && Add_flag==0 && Del_flag==1 && Ver_flag==0)
				{
					if(KEY2==0)	  //����KEY2
						{
							while(!KEY2);
							Del_Move_flag=~Del_Move_flag;
						}
						EXTI_ClearITPendingBit(EXTI_Line8);  //���LINE8�ϵ��жϱ�־λ
				}
	


//------------------KEY3--------------------		
//------------------����ģʽKEY3--------------------	
if(Set_flag==1 && Add_flag==0 && Del_flag==0 && Ver_flag==0)
	{
		EXTI_ClearITPendingBit(EXTI_Line5);  //���LINE5�ϵ��жϱ�־λ
	if(KEY3==0)	  //����KEY3
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
//------------------���ģʽKEY3--------------------	
	else if(Set_flag==0 && Add_flag==1 && Del_flag==0 && Ver_flag==0)
		{
			EXTI_ClearITPendingBit(EXTI_Line5);  //���LINE5�ϵ��жϱ�־λ
			if(KEY3==0)	  //����KEY3
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
				EXTI_ClearITPendingBit(EXTI_Line5);  //���LINE5�ϵ��жϱ�־λ
				if(KEY3==0)	  //����KEY3
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
				if(KEY4==0)	  //����KEY4
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
					EXTI_ClearITPendingBit(EXTI_Line6);  //���LINE6�ϵ��жϱ�־λ	
					}
			else if(Set_flag==0 && Add_flag==1 && Del_flag==0 && Ver_flag==0)
				{		
					if(KEY4==0)	  //����KEY4
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
						EXTI_ClearITPendingBit(EXTI_Line6);  //���LINE6�ϵ��жϱ�־λ	
						}
				else if(Set_flag==0 && Add_flag==0 && Del_flag==1 && Ver_flag==0)
				{		
					if(KEY4==0)	  //����KEY4
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
						EXTI_ClearITPendingBit(EXTI_Line6);  //���LINE6�ϵ��жϱ�־λ	
						}
				else if(Set_flag==0 && Add_flag==0 && Del_flag==0 && Ver_flag==1)
				{		
					if(KEY4==0)	  //����KEY4
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
						EXTI_ClearITPendingBit(EXTI_Line6);  //���LINE6�ϵ��жϱ�־λ	
						}
}




