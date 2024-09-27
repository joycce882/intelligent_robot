#include <reg52.h>
#include <intrins.h>
//-------KEY-PIN-----------//
sbit KEY1 = P3^0;
sbit KEY2 = P3^1;
sbit KEY3 = P3^2;
sbit KEY4 = P3^3;
//-------舵机-PIN-----------//
sbit SG90=P2^5;

/*函数或者变量声明*/
void Delay100ms();
void Time0Init();
void 	ServoMotorTest(void);


//-------红外避障-----------//
sbit XG1OUT	=	P0^4;
sbit XG2OUT	=	P0^5;
sbit XG3OUT	=	P0^6;
//LED-PIN
sbit LED3 = P1^0;
sbit LED4 = P1^1;
sbit LED5 = P1^2;
void	Lightpatrol_Test	(void);


//-------电机-PIN------------//
//电机1
sbit IN1 = P0^0; 
sbit IN2 = P0^1;
//电机2
sbit IN3 = P0^2;  
sbit IN4 = P0^3;	
void L298N_Test(void);
/*-------------- 主函数--------------*/
void main()
{		
		Time0Init();
		while(1){
		ServoMotorTest();
		Lightpatrol_Test();
		L298N_Test();
		}

}

/*--------------相关函数--------------*/
//延时函数
void Delay100ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 5;
	j = 52;
	k = 195;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Time0Init(){
	TMOD=0x01;
	TL0=0x33;
	TH0=0xFE;//配置定时器0，时长0.5ms
	
	TR0=1;//定时器开启
	
	TF0=0;
	ET0=1;
	EA=1; //中断开启

}

int  cnt=0;
int  angel=0;
void ServoMotorTest(void){
	if(KEY1==0)		angel=3;
	if(KEY2==0)		angel=0;
	if(KEY3==0)		angel=4;
}



void Time0() interrupt 1	  //中断函数
{   
	TL0 = 0x33;	
  TH0 = 0xFE;
	cnt++;
	
	if(cnt<=angel)//当小于等于时，这里变为高电平
	{
	   SG90=1;
	}
	else
	{
	   SG90=0;
	}
	 
	if(cnt==40)
	{
		cnt=0;
		SG90=1;
	}
	
}
/*---Lightpatrol-----------相关函数--------------*/
void Lightpatrol_Test(void)//巡光模块
{

	if(XG1OUT==1) LED3 = 1; else LED3 = 0 ;
	if(XG2OUT==1) LED4 = 1; else LED4 = 0 ;
	if(XG3OUT==1) LED5 = 1; else LED5 = 0 ;
}


/*--L298N------------相关函数--------------*/
void L298N_Test(void){
		IN1=0;IN2=1;//电机1正转
		IN3=0;IN4=1;//电机2正转		
		Delay100ms();Delay100ms();Delay100ms();
	
		IN1=1;IN2=0;//电机1反转
		IN3=1;IN4=0;//电机2反转
		Delay100ms();Delay100ms();Delay100ms();
	
		IN1=0;IN2=0;//电机1制动
		IN3=0;IN4=0;//电机2制动	
		Delay100ms();Delay100ms();Delay100ms();
}



