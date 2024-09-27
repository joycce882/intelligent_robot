#include "ds3231.h"
#include "stdlib.h"
#include "delay.h"
#include "usart.h"

static void IIC_Start(void)
{
	DS_SDADIR_OUT();
	DS_SDA = 1;
	delay_us(1);
	DS_SCL = 1;  
	delay_us(5);
	DS_SDA = 0; //START:when CLK is high,DATA change form high to low
	delay_us(5);
	DS_SCL = 0; //钳住I2C总线，准备发送或接收数据 
	delay_us(2);
}

static void IIC_Stop(void)
{
	DS_SDADIR_OUT();
	DS_SCL = 0;
	DS_SDA = 0; //STOP:when CLK is high,DATA change form low to high
	delay_us(4);
	DS_SCL = 1;
	delay_us(5);
	DS_SDA = 1; //发送I2C总线结束信号
	delay_us(4);
}

static unsigned char IIC_WaitAck(void)
{
	unsigned char ucErrtime=0;
	DS_SDADIR_OUT();
	DS_SDA = 1;
	delay_us(1);
	DS_SCL = 1;
	delay_us(1);
	DS_SDADIR_IN();
	while(DS_SDAin)
	{
		ucErrtime++;
		if(ucErrtime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	DS_SCL = 0;
	return 0;
}

static void IIC_SendByte(unsigned char dat)
{
	unsigned char i;
	DS_SCL = 0;
	DS_SDADIR_OUT();
	for(i=0;i<8;i++)
	{
		if((dat&0x80)>>7)	DS_SDA = 1;
		else 							DS_SDA = 0;
		dat<<=1;
		delay_us(2);
		DS_SCL = 1;
		delay_us(2);
		DS_SCL = 0;
		delay_us(2);
	}
}

static unsigned char IIC_ReadByte(void)
{
	unsigned char i,dat=0;
	DS_SDADIR_IN();
	for(i=0;i<8;i++)
	{
		DS_SCL = 0;
		delay_us(2);
		DS_SCL = 1;
		dat<<=1;
		if(DS_SDAin) dat++;
		delay_us(1);
	}
	DS_SDADIR_OUT();
	DS_SCL = 0;
	DS_SDA = 1; delay_us(2);
	DS_SCL = 1; delay_us(2);
	DS_SCL = 0;
	return dat;
}


static void IIC_ACK(unsigned char mode)
{
	DS_SDADIR_OUT();
	if(!mode)	DS_SDA = 0;
	else 			DS_SDA = 1;
	delay_us(3);
	DS_SCL = 1;
	delay_us(5);
	DS_SCL = 0;
	delay_us(2);
}


void ds3231_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB,&GPIO_InitStructure);	  
	
	ds3231_Write(DS3231_CONTROL,0x04);
	delay_ms(2);
	ds3231_Write(DS3231_STATUS,0x0);
	delay_ms(50);
}

//void EXTI9_5_IRQHandler(void)
//{
//	clock.alarmBeepFlag = true;
//	EXTI_ClearITPendingBit(EXTI_Line5);
//}

	
void ds3231_Write(unsigned char addr, unsigned short int dat)
{
	IIC_Start();
	delay_us(5);
	IIC_SendByte(DS3231_ADDR_Write);
	IIC_WaitAck();
	delay_us(5);
	IIC_SendByte(addr);
	IIC_WaitAck();
	delay_us(5);
	IIC_SendByte(dat);
	IIC_WaitAck();
	delay_us(5);
	IIC_Stop();
}

unsigned char ds3231_Read(unsigned char addr)
{
	unsigned char dat;
	IIC_Start();
	IIC_SendByte(DS3231_ADDR_Write);
	IIC_WaitAck();
	delay_us(5);
	IIC_SendByte(addr);
	IIC_WaitAck();
	delay_us(5);
	IIC_Start();
	IIC_SendByte(DS3231_ADDR_Read);
	IIC_WaitAck();
	delay_us(5);
	dat = IIC_ReadByte();
	IIC_ACK(1);
	IIC_Stop();
	return dat;
}

void ds3231_writeTime(void)
{
	ds3231_Write(DS3231_ADDR_Year,0x20);     //年
	ds3231_Write(DS3231_ADDR_Month,0x03);    //月
	ds3231_Write(DS3231_ADDR_Date,0x19);     //日
	ds3231_Write(DS3231_ADDR_Day,0X04);      //星期
	ds3231_Write(DS3231_ADDR_Hour,	0x15);   //时
	ds3231_Write(DS3231_ADDR_Minute,0x49);   //分
	ds3231_Write(DS3231_ADDR_Second,0x00);   //秒
}

void ds3231_readTime(void)
{
	clock.timeRead.sec 	 = BCDtoNum(ds3231_Read(DS3231_ADDR_Second));
	clock.timeRead.min 	 = BCDtoNum(ds3231_Read(DS3231_ADDR_Minute));
	clock.timeRead.hour  = BCDtoNum(ds3231_Read(DS3231_ADDR_Hour));
	clock.timeRead.day 	 = BCDtoNum(ds3231_Read(DS3231_ADDR_Day));
	clock.timeRead.date  = BCDtoNum(ds3231_Read(DS3231_ADDR_Date));
	clock.timeRead.month = BCDtoNum(ds3231_Read(DS3231_ADDR_Month));
	clock.timeRead.year	 = BCDtoNum(ds3231_Read(DS3231_ADDR_Year));
}


//void ds3231_displayTime(enum clockShowSwitch_e showMode)
//{
//	switch(showMode)
//	{
//		case NormalShow:

//			break;
//		case DateShow:

//			break;
//		case YearShow:

//			break;
//		case TemperShow:

//			break;
//	}
//}



//void ds3231_serialSetTime(void) //使用了公用接收标志位
//{
//	if(UART_RX_STA&0x8000)
//	{
//		UART_RX_STA = 0;
//		if(UART_RX_BUF[2]==':')
//		{
//			ds3231_Write(DS3231_ADDR_Hour,NumtoBCD((UART_RX_BUF[0]-'0')*10+UART_RX_BUF[1]-'0'));
//			ds3231_Write(DS3231_ADDR_Minute,NumtoBCD((UART_RX_BUF[3]-'0')*10+UART_RX_BUF[4]-'0'));
//			ds3231_Write(DS3231_ADDR_Second,NumtoBCD((UART_RX_BUF[6]-'0')*10+UART_RX_BUF[7]-'0'));
//			printf("write ok\r\n");
//		}
//		else
//		{
//			printf("error\r\n");
//		}
//	}
//}


void ds3231_setAlarm(enum alarm_e alarmx, alarmSetTimeObject *alarmxSet)
{
	if(alarmx != alarm1 && alarmx != alarm2)
		return;
	/*
		这里舍弃了sec/date设定
		如若需要可添加设定,注意alarm2无sec设定功能
	*/
	ds3231_Write(DS3231_CONTROL,0x04 + alarmx); //使能Pin_INT输出并开启对应闹钟开关
	if(alarmx == alarm1)
	{
		ds3231_Write(DS3231_AL1SEC, 0x80); /*屏蔽了sec*/
		ds3231_Write(DS3231_AL1MIN,NumtoBCD(alarmxSet->min));
		ds3231_Write(DS3231_AL1HOUR,NumtoBCD(alarmxSet->hour));
		ds3231_Write(DS3231_AL1DAY, 0x80); /*屏蔽了Day/Date*/
	//	ds3231_Write(DS3231_AL2DAY,NumtoBCD(alarmxSet->day)); 
	}
	else if(alarmx == alarm2)
	{
		ds3231_Write(DS3231_AL2MIN,NumtoBCD(alarmxSet->min));
		ds3231_Write(DS3231_AL2HOUR,NumtoBCD(alarmxSet->hour));
		ds3231_Write(DS3231_AL2DAY, 0x80); /*屏蔽了Day/Date*/
	//	ds3231_Write(DS3231_AL2DAY,NumtoBCD(alarmxSet->day)); 
	}
}

/*输出二进制补码,只考虑了正值温度情况*/
float ds3231_readTemper(void) 
{
	float temp;
	temp = ds3231_Read(DS3231_TempM);
	temp += 0.25*(ds3231_Read(DS3231_TempL)>>6);
	return temp;
}



/***********************************************************/
unsigned char BCDtoNum(unsigned char val) //BCD->十进制
{
	return ((val>>4)*10)+(val&0x0f);
}

unsigned short int NumtoBCD(unsigned char val)//十进制->BCD
{
	return (((val%100)/10)<<4)|(val%10);
}
