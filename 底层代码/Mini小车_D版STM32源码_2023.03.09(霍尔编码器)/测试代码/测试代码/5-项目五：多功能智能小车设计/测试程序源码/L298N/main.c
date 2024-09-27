#include <reg52.h>
#include <intrins.h>


//-------���-PIN------------//
//���1
sbit IN1 = P0^0; 
sbit IN2 = P0^1;
//���2
sbit IN3 = P0^2;  
sbit IN4 = P0^3;	

/*�������߱�������*/
void Delay100ms();
void L298N_Test(void);
/*--------------������--------------*/
void main()
{

		while(1){
		L298N_Test();
		}

}

/*-------------��غ���-------------*/
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
		IN1=0;IN2=1;//���1��ת
		IN3=0;IN4=1;//���2��ת		
		Delay100ms();Delay100ms();Delay100ms();
	
		IN1=1;IN2=0;//���1��ת
		IN3=1;IN4=0;//���2��ת
		Delay100ms();Delay100ms();Delay100ms();
	
		IN1=0;IN2=0;//���1�ƶ�
		IN3=0;IN4=0;//���2�ƶ�	
		Delay100ms();Delay100ms();Delay100ms();
}

/*--------------��غ���--------------*/




