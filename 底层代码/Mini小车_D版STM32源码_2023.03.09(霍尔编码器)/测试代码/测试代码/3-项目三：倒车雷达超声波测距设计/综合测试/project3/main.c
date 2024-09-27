#include <reg52.h>
#include <intrins.h>
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
unsigned int time = -1;
float dis = -1;
//--------LCD-PIN---------//
#define uchar unsigned char	// �Ժ�unsigned char�Ϳ�����uchar����
#define uint  unsigned int	// �Ժ�unsigned int �Ϳ�����uint ����

sbit LCD_RS   = P3^6;			// 1602Һ����RS�ܽ�       
sbit LCD_RW   = P3^5;			// 1602Һ����RW�ܽ� 
sbit LCD_EN   = P3^4;			// 1602Һ����EN�ܽ�

#define LCD_DataPort P0
void LCD_Init();
void LCD_ShowString(unsigned char Line,unsigned char Column,char *String);
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);

//-------BEEP-PIN-----------//
sbit BEEP = P1^5;

/*�������߱�������*/
void Delay100ms();
void BEEPControl(unsigned int b);
/*********************************************************/
// ���뼶����ʱ������time��Ҫ��ʱ�ĺ�����
/*********************************************************/
void LCD_Delay()
{
	unsigned char i, j;
	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

/**
  * @brief  LCD1602д����
  * @param  Command Ҫд�������
  * @retval ��
  */
void LCD_WriteCommand(unsigned char Command)
{
	LCD_RS=0;
	LCD_RW=0;
	LCD_DataPort=Command;
	LCD_EN=1;
	LCD_Delay();
	LCD_EN=0;
	LCD_Delay();
}

/**
  * @brief  LCD1602д����
  * @param  Data Ҫд�������
  * @retval ��
  */
void LCD_WriteData(unsigned char Data)
{
	LCD_RS=1;
	LCD_RW=0;
	LCD_DataPort=Data;
	LCD_EN=1;
	LCD_Delay();
	LCD_EN=0;
	LCD_Delay();
}

/**
  * @brief  LCD1602���ù��λ��
  * @param  Line ��λ�ã���Χ��1~2
  * @param  Column ��λ�ã���Χ��1~16
  * @retval ��
  */
void LCD_SetCursor(unsigned char Line,unsigned char Column)
{
	if(Line==1)
	{
		LCD_WriteCommand(0x80|(Column-1));
	}
	else if(Line==2)
	{
		LCD_WriteCommand(0x80|(Column-1+0x40));
	}
}

/**
  * @brief  LCD1602��ʼ������
  * @param  ��
  * @retval ��
  */
void LCD_Init()
{
	LCD_WriteCommand(0x38);//��λ���ݽӿڣ�������ʾ��5*7����
	LCD_WriteCommand(0x0c);//��ʾ�������أ���˸��
	LCD_WriteCommand(0x06);//���ݶ�д�����󣬹���Զ���һ�����治��
	LCD_WriteCommand(0x01);//��긴λ������
}

/**
  * @brief  ��LCD1602ָ��λ�ÿ�ʼ��ʾ�����ַ���
  * @param  Line ��ʼ��λ�ã���Χ��1~2
  * @param  Column ��ʼ��λ�ã���Χ��1~16
  * @param  String Ҫ��ʾ���ַ���
  * @retval ��
  */
void LCD_ShowString(unsigned char Line,unsigned char Column,char *String)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=0;String[i]!='\0';i++)
	{
		LCD_WriteData(String[i]);
	}
}

/**
  * @brief  ����ֵ=X��Y�η�
  */
int LCD_Pow(int X,int Y)
{
	unsigned char i;
	int Result=1;
	for(i=0;i<Y;i++)
	{
		Result*=X;
	}
	return Result;
}

/**
 * @brief  ��LCD1602ָ��λ�ÿ�ʼ��ʾ��������
 * @param  Line ��ʼ��λ�ã���Χ��1~2
 * @param  Column ��ʼ��λ�ã���Χ��1~16
 * @param  Number Ҫ��ʾ�����֣���Χ��0~65535
 * @param  Length Ҫ��ʾ���ֵĳ��ȣ���Χ��1~5
 * @retval ��
  */
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(Number/LCD_Pow(10,i-1)%10+'0');
	}
}

/********��������غ���*************************************************//*********************************************************/
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
void BEEPControl(unsigned int b){
	if(b == 0){BEEP = 1 ;}//����
	else BEEP = 0 ;//��
	
}
/*********************************************************//*********************************************************/
// ������
/*********************************************************/
void main()
{
	LCD_Init();								// Һ�����ܳ�ʼ��	
	while(1)
	{
		GetOnce();
		time = gettime();
		dis = Getdis(time);
		LCD_ShowString(1,3,"dis:");
		LCD_ShowNum(2,7,dis,2);
		if(dis <5)BEEPControl(1);
		else BEEPControl(0);
		
	}
}
