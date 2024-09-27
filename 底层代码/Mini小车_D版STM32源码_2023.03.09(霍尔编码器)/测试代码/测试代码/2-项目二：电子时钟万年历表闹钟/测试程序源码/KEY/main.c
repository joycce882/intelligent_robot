#include <reg52.h>
#include <intrins.h>
//-------LED-PIN-----------//
sbit LED3 = P1^0;
sbit LED4 = P1^1;
sbit LED5 = P1^2;
sbit LED6 = P1^3;	
sbit LED7 = P1^4;
//-------KEY-PIN-----------//
sbit KEY1 = P3^0;
sbit KEY2 = P3^1;
sbit KEY3 = P3^2;
sbit KEY4 = P3^3;

/*函数或者变量声明*/
void	KEY_Test	(void);
/*-------------- 主函数--------------*/
void main()
{

		while(1){
		KEY_Test();
		}

}

/*--------------相关函数--------------*/
//按键
void KEY_Test(void){
		LED3=KEY4;
		LED4=KEY3;
		LED5=KEY2;
		LED6=KEY1;
		LED7=KEY1;
}



/*--------------相关函数--------------*/




