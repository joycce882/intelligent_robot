#include <reg52.h>
#include <intrins.h>
#include <stdio.h>
#define uint unsigned int
#define uchar unsigned char
//--------PIN-----------//

/*函数或者变量声明*/

void		UARTInit		(void);
void 		SendData		(unsigned char dat);
void 		SendString	(unsigned char *s );
void	  Delay1000ms	();

uchar num;	//接收到的值

/*-------------- 主函数--------------*/
void main()
{
		UARTInit(); //串口初始化
	
	
	while(1){ 
			
		TI = 1;
		puts("Hello Wolrd!");   // 每次打印都会换行   支持中文打印 
		while(!TI);
		TI = 0;
		Delay1000ms();
		}

}
/*--------------相关函数--------------*/
//延时函数
void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 43;
	j = 6;
	k = 203;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

//重写putchar函数
char putchar(char c)
{
	SendData(c);
	return c;
}

void UARTInit()
{
	EA = 1;	//打开总中断
	ES = 1; //打开串口中断
	SM0 = 0;	
	SM1 = 1;//串口工作方式1,8位UART波特率可变
	REN = 1;//串口允许接收
	TR1 = 1;//启动定时器1
	TMOD |= 0x20;//定时器1，工作模式2 8位自动重装 n  
	TH1 = 0xfd;   // 根据下面的公式计算得到
	TL1 = 0xfd; //设置比特率9600
}

	


// 发送一个字节数据
void SendData(unsigned char dat)
{
	SBUF = dat;				// 把要发送的数据存入写SBUF
	while(TI == 0);  	// 等待发送标志位置1
	TI = 0;
}

// 发送字符串，以'\0'形式结尾
void SendString(unsigned char *s)
{
	while (*s!='\0')		// 检查是否到结尾
	{
		SendData(*s ++);	// 地址递增进行逐个发送
	}
}

//串口中断函数
void IRQ_UART() interrupt 4
{
	if(RI)//判断接收是否完成
	{
		num = SBUF;//读SBUF，读出串口接收到的数据
		RI = 0;//软件清零接收标志位	
	}
	if(TI)//判断是否发送完成
		TI = 0;//清零发送完成标志位	
} 



