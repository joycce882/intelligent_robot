#include <reg52.h>
#include <intrins.h>

//-------数码管-PIN-----------//
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

sbit LSA	=	P2^2; //定义管脚
sbit LSB	=	P2^3;
sbit LSC	=	P2^4;

sbit LE = P2^5;  //定义方向

/*函数或者变量声明*/
void	Delay100ms();
void	NixieTube_Test(void);
/*-------------- 主函数--------------*/
void main()
{
		LE = 1 ;
		while(1){
//			LSA=1; LSB=1; LSC=1;
//			P0 = 0x06;
		NixieTube_Test();
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



void Delay100us()		//@11.0592MHz
{
	unsigned char i, j;


	i = 2;
	j = 15;
	do
	{
		while (--j);
	} while (--i);
}

/************************************************************************************************************/
//数码管
u8 code smg[16]={	0x3f  , 0x06 , 0x5b , 0x4f , 
									0x66 	, 0x6d , 0x7d , 0x07 , 
									0x7f  , 0x6f , 0x77 , 0x7c ,														//Line   Bleak  Bleak   Spot
									0x39 	, 0x5e , 0x79 , 0x71};//共阴数码管段选数据即显示的数字//0x40   0x00   0xFF   0x80

//u8 code smg[16]={	0xC0  , 0xF9 , 0xA4 , 0xB0 , 
//								0x99 	, 0x92 , 0x82 , 0xF8 , 
//								0x80  , 0x90 , 0x88 , 0x83 ,
//								0xC6 	, 0xA1 , 0x86 , 0x8E};//共阳数码管段选数据即显示的数字	//0xBF 0xFF 0x00	0x7F						

void NixieTube_Test(void){
  u8 i = 0;			
	while(1)
	{
				switch(i){
//						case(0):LSA=0;LSB=0;LSC=0;break;//第一个数码管LSC LSB LSA  000 之和为0
//						case(1):LSA=1;LSB=0;LSC=0;break;//第二个数码管LSC LSB LSA  001 之和为1
//						case(2):LSA=0;LSB=1;LSC=0;break;//第三个数码管LSC LSB LSA  010 之和为2
//						case(3):LSA=1;LSB=1;LSC=0;break;//第四个数码管LSC LSB LSA  011 之和为3
//						case(4):LSA=0;LSB=0;LSC=1;break;//第五个数码管LSC LSB LSA  100 之和为4
//						case(5):LSA=1;LSB=0;LSC=1;break;//第六个数码管LSC LSB LSA  101 之和为5
//						case(6):LSA=0;LSB=1;LSC=1;break;//第七个数码管LSC LSB LSA  110 之和为6
//						case(7):LSA=1;LSB=1;LSC=1;break;//第八个数码管LSC LSB LSA  111 之和为7
					
						case(7):LSA=0; LSB=0; LSC=0; break;//第一个数码管LSC LSB LSA  000 之和为0
						case(6):LSA=1; LSB=0; LSC=0; break;//第二个数码管LSC LSB LSA  001 之和为1
						case(5):LSA=0; LSB=1; LSC=0; break;//第三个数码管LSC LSB LSA  010 之和为2
						case(4):LSA=1; LSB=1; LSC=0; break;//第四个数码管LSC LSB LSA  011 之和为3
						case(3):LSA=0; LSB=0; LSC=1; break;//第五个数码管LSC LSB LSA  100 之和为4
						case(2):LSA=1; LSB=0; LSC=1; break;//第六个数码管LSC LSB LSA  101 之和为5
						case(1):LSA=0; LSB=1; LSC=1; break;//第七个数码管LSC LSB LSA  110 之和为6
						case(0):LSA=1; LSB=1; LSC=1; break;//第八个数码管LSC LSB LSA  111 之和为7	
						default : i = -1; break;
			}
			P0 = smg[i];	//接收段选数据
			i ++;
			Delay100us();	//利用视觉暂留效应	
			P0 = 0x00;
	}
}

/*--------------相关函数--------------*/




