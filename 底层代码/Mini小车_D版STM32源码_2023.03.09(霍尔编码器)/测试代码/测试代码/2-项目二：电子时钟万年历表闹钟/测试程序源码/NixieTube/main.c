#include <reg52.h>
#include <intrins.h>

//-------�����-PIN-----------//
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

sbit LSA	=	P2^2; //����ܽ�
sbit LSB	=	P2^3;
sbit LSC	=	P2^4;

sbit LE = P2^5;  //���巽��

/*�������߱�������*/
void	Delay100ms();
void	NixieTube_Test(void);
/*-------------- ������--------------*/
void main()
{
		LE = 1 ;
		while(1){
//			LSA=1; LSB=1; LSC=1;
//			P0 = 0x06;
		NixieTube_Test();
		}
}

/*--------------��غ���--------------*/
//��ʱ����
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
//�����
u8 code smg[16]={	0x3f  , 0x06 , 0x5b , 0x4f , 
									0x66 	, 0x6d , 0x7d , 0x07 , 
									0x7f  , 0x6f , 0x77 , 0x7c ,														//Line   Bleak  Bleak   Spot
									0x39 	, 0x5e , 0x79 , 0x71};//��������ܶ�ѡ���ݼ���ʾ������//0x40   0x00   0xFF   0x80

//u8 code smg[16]={	0xC0  , 0xF9 , 0xA4 , 0xB0 , 
//								0x99 	, 0x92 , 0x82 , 0xF8 , 
//								0x80  , 0x90 , 0x88 , 0x83 ,
//								0xC6 	, 0xA1 , 0x86 , 0x8E};//��������ܶ�ѡ���ݼ���ʾ������	//0xBF 0xFF 0x00	0x7F						

void NixieTube_Test(void){
  u8 i = 0;			
	while(1)
	{
				switch(i){
//						case(0):LSA=0;LSB=0;LSC=0;break;//��һ�������LSC LSB LSA  000 ֮��Ϊ0
//						case(1):LSA=1;LSB=0;LSC=0;break;//�ڶ��������LSC LSB LSA  001 ֮��Ϊ1
//						case(2):LSA=0;LSB=1;LSC=0;break;//�����������LSC LSB LSA  010 ֮��Ϊ2
//						case(3):LSA=1;LSB=1;LSC=0;break;//���ĸ������LSC LSB LSA  011 ֮��Ϊ3
//						case(4):LSA=0;LSB=0;LSC=1;break;//����������LSC LSB LSA  100 ֮��Ϊ4
//						case(5):LSA=1;LSB=0;LSC=1;break;//�����������LSC LSB LSA  101 ֮��Ϊ5
//						case(6):LSA=0;LSB=1;LSC=1;break;//���߸������LSC LSB LSA  110 ֮��Ϊ6
//						case(7):LSA=1;LSB=1;LSC=1;break;//�ڰ˸������LSC LSB LSA  111 ֮��Ϊ7
					
						case(7):LSA=0; LSB=0; LSC=0; break;//��һ�������LSC LSB LSA  000 ֮��Ϊ0
						case(6):LSA=1; LSB=0; LSC=0; break;//�ڶ��������LSC LSB LSA  001 ֮��Ϊ1
						case(5):LSA=0; LSB=1; LSC=0; break;//�����������LSC LSB LSA  010 ֮��Ϊ2
						case(4):LSA=1; LSB=1; LSC=0; break;//���ĸ������LSC LSB LSA  011 ֮��Ϊ3
						case(3):LSA=0; LSB=0; LSC=1; break;//����������LSC LSB LSA  100 ֮��Ϊ4
						case(2):LSA=1; LSB=0; LSC=1; break;//�����������LSC LSB LSA  101 ֮��Ϊ5
						case(1):LSA=0; LSB=1; LSC=1; break;//���߸������LSC LSB LSA  110 ֮��Ϊ6
						case(0):LSA=1; LSB=1; LSC=1; break;//�ڰ˸������LSC LSB LSA  111 ֮��Ϊ7	
						default : i = -1; break;
			}
			P0 = smg[i];	//���ն�ѡ����
			i ++;
			Delay100us();	//�����Ӿ�����ЧӦ	
			P0 = 0x00;
	}
}

/*--------------��غ���--------------*/




