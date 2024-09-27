#include <reg52.h>
#include <intrins.h>

//--------继电器-PIN----------//
sbit RELAY = P3^7;

/*函数或者变量声明*/
void 	Delay1000ms();
void	RELAY_Test(void);
/*-------------- 主函数--------------*/
void main()
{
		while(1){
//			RELAY = 1 ;
		RELAY_Test();
		}

}

/*--------------相关函数--------------*/
//延时函数
void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 57;
	j = 27;
	k = 112;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void RELAY_Test(void){
		RELAY	=	0;
		Delay1000ms();
		RELAY	=	1;
		Delay1000ms();
}

/*--------------相关函数--------------*/




