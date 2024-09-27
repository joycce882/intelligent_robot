#include <reg52.h>
#include <intrins.h>

//-------LED-----------//
sbit LED3 = P1^0;
sbit LED4 = P1^1;
sbit LED5 = P1^2;
sbit LED6 = P1^3;	
sbit LED7 = P1^4;

//--------���������-PIN---------//
sbit Trig = P2^0;
sbit Echo = P2^1;

/*�������߱�������*/
void Delay10us();
void Rstart();
int gettime();
float Getdis(unsigned int time);
void star();
void end();
void GetOnce();
void	UltrasonicTest(void);
/*-------------- ������--------------*/
void main()
{

		while(1){
		UltrasonicTest();
		}

}

/*--------------��غ���--------------*/
void Delay10us()
{
 TMOD |= 0x1;
 TH0 = 0xFF;
 TL0 = 0xF6;
 TR0 = 1;
 while(!TF0);
 TF0 = 0;
}
void Rstart()  
{
 Trig=0;
 Trig=1;
 Delay10us();
 Trig=0;
}

//��ȡʱ��
int gettime()
{
 unsigned int time = 0;
 time = TH0*256+TL0 ;// TH0<<8 | TL0;
 return time;
}
//��ȡ����
float Getdis(unsigned int time)  
{
 float distance;
 distance = (float)time * 0.0017;
	 TH0=0;
	 TL0=0;
 return distance;
}
void star()
{
 TH0 = 0;
 TL0 = 0;
 TR0 = 1;
}
void end()
{
 TR0 = 0;
}
void GetOnce()  
{
 Rstart();
 while(!Echo);
 star();
 while(Echo);
 end();
}

unsigned int time = -1;
float dis = -1;
void UltrasonicTest(void){  //������ģ�����
  GetOnce();
  time = gettime();
  dis = Getdis(time);
	
//	if(dis!=-1) LED4=0;
//	else LED4=1;
	
		if(dis>5) LED4=0;
	else LED4=1;
	
}
/*--------------��غ���--------------*/




