#include <reg52.h>
#include <intrins.h>
//-------LED-PIN-----------//
sbit LED3 = P1^0;
sbit LED4 = P1^1;
sbit LED5 = P1^2;
sbit LED6 = P1^3;	
sbit LED7 = P1^4;

//-------�������-----------//
sbit XG1OUT	=	P0^4;
sbit XG2OUT	=	P0^5;
sbit XG3OUT	=	P0^6;

/*�������߱�������*/
void	Lightpatrol_Test	(void);
/*-------------- ������--------------*/
void main()
{
//		LED3 = 1;
//		LED4 = 1;
//		LED5 = 1;
//		LED6 = 1;
//		LED7 = 1;
		XG1OUT = 0;
		XG2OUT = 0;
		XG3OUT = 0;
		while(1){
		Lightpatrol_Test();
		}

}

/*--------------��غ���--------------*/

void Lightpatrol_Test(void)//Ѳ��ģ��
{

	if(XG1OUT==1) LED3 = 1; else LED3 = 0 ;
	if(XG2OUT==1) LED4 = 1; else LED4 = 0 ;
	if(XG3OUT==1) LED5 = 1; else LED5 = 0 ;
}
/*--------------��غ���--------------*/






