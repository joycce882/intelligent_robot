#include <reg52.h>
#include <intrins.h>
//--------超声波测距-PIN---------//
sbit Trig = P2^0;
sbit Echo = P2^1;
/*函数或者变量声明*/
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
#define uchar unsigned char	// 以后unsigned char就可以用uchar代替
#define uint  unsigned int	// 以后unsigned int 就可以用uint 代替

sbit LCD_RS   = P3^6;			// 1602液晶的RS管脚       
sbit LCD_RW   = P3^5;			// 1602液晶的RW管脚 
sbit LCD_EN   = P3^4;			// 1602液晶的EN管脚

#define LCD_DataPort P0
void LCD_Init();
void LCD_ShowString(unsigned char Line,unsigned char Column,char *String);
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);

//-------BEEP-PIN-----------//
sbit BEEP = P1^5;

/*函数或者变量声明*/
void Delay100ms();
void BEEPControl(unsigned int b);
/*********************************************************/
// 毫秒级的延时函数，time是要延时的毫秒数
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
  * @brief  LCD1602写命令
  * @param  Command 要写入的命令
  * @retval 无
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
  * @brief  LCD1602写数据
  * @param  Data 要写入的数据
  * @retval 无
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
  * @brief  LCD1602设置光标位置
  * @param  Line 行位置，范围：1~2
  * @param  Column 列位置，范围：1~16
  * @retval 无
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
  * @brief  LCD1602初始化函数
  * @param  无
  * @retval 无
  */
void LCD_Init()
{
	LCD_WriteCommand(0x38);//八位数据接口，两行显示，5*7点阵
	LCD_WriteCommand(0x0c);//显示开，光标关，闪烁关
	LCD_WriteCommand(0x06);//数据读写操作后，光标自动加一，画面不动
	LCD_WriteCommand(0x01);//光标复位，清屏
}

/**
  * @brief  在LCD1602指定位置开始显示所给字符串
  * @param  Line 起始行位置，范围：1~2
  * @param  Column 起始列位置，范围：1~16
  * @param  String 要显示的字符串
  * @retval 无
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
  * @brief  返回值=X的Y次方
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
 * @brief  在LCD1602指定位置开始显示所给数字
 * @param  Line 起始行位置，范围：1~2
 * @param  Column 起始列位置，范围：1~16
 * @param  Number 要显示的数字，范围：0~65535
 * @param  Length 要显示数字的长度，范围：1~5
 * @retval 无
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

/********超声波相关函数*************************************************//*********************************************************/
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

//获取时间
int gettime()
{
 unsigned int time = 0;
 time = TH0*256+TL0 ;// TH0<<8 | TL0;
 return time;
}
//获取距离
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
void BEEPControl(unsigned int b){
	if(b == 0){BEEP = 1 ;}//不响
	else BEEP = 0 ;//响
	
}
/*********************************************************//*********************************************************/
// 主函数
/*********************************************************/
void main()
{
	LCD_Init();								// 液晶功能初始化	
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
