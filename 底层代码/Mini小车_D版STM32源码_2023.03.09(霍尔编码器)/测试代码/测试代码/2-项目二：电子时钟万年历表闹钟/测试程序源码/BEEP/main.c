#include <reg52.h>
#include <intrins.h>

//-------BEEP-PIN-----------//
sbit BEEP = P1^5;

/*�������߱�������*/
void Delay100ms();
void	BEEP_Test	(void);
/*-------------- ������--------------*/
void main()
{

		while(1){
		BEEP_Test();
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

//������
void BEEP_Test(void){
		BEEP = 1 ;//����
		Delay100ms();
		BEEP = 0 ;//��
		Delay100ms();
}
/*--------------��غ���--------------*/




