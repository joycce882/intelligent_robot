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
/*-------------- 主函数--------------*/
void main()
{		
		Time0Init();
		while(1){
		ServoMotorTest();
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

/*--------------相关函数--------------*/




