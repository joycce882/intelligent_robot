#include <reg52.h>
#include <intrins.h>

/*-----LED-PIN----*/
sbit LED3 = P1^0;
sbit LED4 = P1^1;
sbit LED5 = P1^2;
sbit LED6 = P1^3;	
sbit LED7 = P1^4;
/*-----LED-PIN----*/
/*函数或者变量声明*/
void Delay100ms();
void	LED_Test	(void);
/*-------------- 主函数--------------*/
void main()
{

while(1){
	LED_Test();
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
//LED灯测试
//void LED_Test(void){
//		LED3 = 0;
//		LED4 = 0;
//		LED5 = 0;
//		LED6 = 0;
//		LED7 = 0;
//		Delay100ms();
//		LED3 = 1;
//		LED4 = 1;
//		LED5 = 1;
//		LED6 = 1;
//		LED7 = 1;
//		Delay100ms();
//}
//流水灯
void LED_Test(void){
		P1 = 0x1e; 					//11110
		Delay100ms();
		P1 = 0x1d; 			 		//11101
		Delay100ms();
		P1 = 0x1b ; 				//11011
		Delay100ms();
		P1 = 0x17 ; 				//10111
		Delay100ms();
		P1 = 0x0f ; 				//01111
		Delay100ms();
}

/*--------------相关函数--------------*/




