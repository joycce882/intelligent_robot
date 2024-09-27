#include <reg52.h>
#include <intrins.h>

//-------BEEP-PIN-----------//
sbit BEEP = P1^5;

/*函数或者变量声明*/
void Delay100ms();
void	BEEP_Test	(void);
/*-------------- 主函数--------------*/
void main()
{

		while(1){
		BEEP_Test();
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

//蜂鸣器
void BEEP_Test(void){
		BEEP = 1 ;//不响
		Delay100ms();
		BEEP = 0 ;//响
		Delay100ms();
}
/*--------------相关函数--------------*/




