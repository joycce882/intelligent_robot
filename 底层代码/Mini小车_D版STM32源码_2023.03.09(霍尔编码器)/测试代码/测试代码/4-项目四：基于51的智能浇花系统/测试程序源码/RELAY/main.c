#include <reg52.h>
#include <intrins.h>

//--------�̵���-PIN----------//
sbit RELAY = P3^7;

/*�������߱�������*/
void 	Delay1000ms();
void	RELAY_Test(void);
/*-------------- ������--------------*/
void main()
{
		while(1){
//			RELAY = 1 ;
		RELAY_Test();
		}

}

/*--------------��غ���--------------*/
//��ʱ����
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

/*--------------��غ���--------------*/




