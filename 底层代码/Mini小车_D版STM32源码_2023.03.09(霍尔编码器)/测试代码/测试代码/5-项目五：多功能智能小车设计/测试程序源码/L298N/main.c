#include <reg52.h>
#include <intrins.h>


//-------电机-PIN------------//
//电机1
sbit IN1 = P0^0; 
sbit IN2 = P0^1;
//电机2
sbit IN3 = P0^2;  
sbit IN4 = P0^3;	

/*函数或者变量声明*/
void Delay100ms();
void L298N_Test(void);
/*--------------主函数--------------*/
void main()
{

		while(1){
		L298N_Test();
		}

}

/*-------------相关函数-------------*/
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

/*--------------相关函数--------------*/




