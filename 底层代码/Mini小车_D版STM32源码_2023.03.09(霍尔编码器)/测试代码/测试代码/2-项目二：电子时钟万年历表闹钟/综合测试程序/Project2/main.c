#include <reg52.h>
#include <intrins.h>
//-------BEEP-PIN-----------//
sbit BEEP = P1^5;

//-------KEY-PIN-----------//
sbit KEY1 = P3^0;
sbit KEY2 = P3^1;
sbit KEY3 = P3^2;
sbit KEY4 = P3^3;

//-------数码管-PIN-----------//
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

sbit LSA	=	P2^2; //定义管脚
sbit LSB	=	P2^3;
sbit LSC	=	P2^4;

sbit LE 	= P2^5;  //定义方向

u8 code gsmg_code[16]={	0x3f  , 0x06 , 0x5b , 0x4f , 
												0x66 	, 0x6d , 0x7d , 0x07 , 
												0x7f  , 0x6f , 0x77 , 0x7c ,																//Line   Bleak  Bleak   Spot
												0x39 	, 0x5e , 0x79 , 0x71};//共阴数码管段选数据即显示的数字//0x40   0x00   0xFF   0x80




//-------DS1302-PIN-----------//
sbit DS1302_RST	=	P3^5;
sbit DS1302_CLK	=	P3^6;
sbit DS1302_IO	=	P3^4;

//---DS1302写入和读取时分秒的地址命令---//
//---秒分时日月周年 最低位读写位;-------//
u8 gREAD_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d}; 
u8 gWRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};

//---DS1302时钟初始化2021年5月20日星期四13点51分47秒。---//
//---存储顺序是秒分时日月周年,存储格式是用BCD码---//
u8 gDS1302_TIME[7] = {0x47, 0x51, 0x13, 0x20, 0x04, 0x05, 0x21};


/*函数或者变量声明*/
void	Delay100ms();
void 	delay_10us(u16 ten_us);
void 	Delay100us();
void  BEEP_Test(void);

void ds1302_init(void);
void ds1302_read_time(void);

void smg_display(u8 dat[],u8 pos);
/*-------------- 主函数--------------*/
void main()
{	  
		u8 clockStatus = 0 ;
		u8 time_buf[8];
		LE = 1 ;
		ds1302_init();

		while(1){
			ds1302_read_time();
			time_buf[0]=gsmg_code[gDS1302_TIME[2]/16];
			time_buf[1]=gsmg_code[gDS1302_TIME[2]&0x0f];
			time_buf[2]=0x40;
			time_buf[3]=gsmg_code[gDS1302_TIME[1]/16];
			time_buf[4]=gsmg_code[gDS1302_TIME[1]&0x0f];
			time_buf[5]=0x40;
			time_buf[6]=gsmg_code[gDS1302_TIME[0]/16];
			time_buf[7]=gsmg_code[gDS1302_TIME[0]&0x0f];
			smg_display(time_buf,1);
			
			
		  BEEP_Test();
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


void delay_10us(u16 ten_us)
{
    while(ten_us--);    
}
/************************************************************************************************************/
//数码管

void smg_display(u8 dat[],u8 pos)
{
    u8 i=0;
    u8 pos_temp=pos-1;

    for(i=pos_temp;i<8;i++)
    {
           switch(i)//位选
        {
            case 0: LSC=1;LSB=1;LSA=1;break;
            case 1: LSC=1;LSB=1;LSA=0;break;
            case 2: LSC=1;LSB=0;LSA=1;break;
            case 3: LSC=1;LSB=0;LSA=0;break;
            case 4: LSC=0;LSB=1;LSA=1;break;
            case 5: LSC=0;LSB=1;LSA=0;break;
            case 6: LSC=0;LSB=0;LSA=1;break;
            case 7: LSC=0;LSB=0;LSA=0;break;
					
        }
        P0=dat[i-pos_temp];//传送段选数据
        delay_10us(100);//延时一段时间，等待显示稳定
        P0=0x00;//
    }
}

/*--------------相关函数--------------*/
/************************************************************************************************************/
//蜂鸣器
void BEEP_Test(void){
		BEEP = 1 ;//不响
		Delay100ms();
		BEEP = 0 ;//响
		Delay100ms();
}
/************************************************************************************************************/
//DS1302s
/*******************************************************************************
* 函 数 名       : ds1302_write_byte
* 函数功能         : DS1302写单字节
* 输    入       : addr：地址/命令
                   dat：数据
* 输    出         : 无
*******************************************************************************/
void ds1302_write_byte(u8 addr,u8 dat)
{
    u8 i=0;
    
    DS1302_RST=0;
    _nop_();    
    DS1302_CLK=0;//CLK低电平
    _nop_();
    DS1302_RST=1;//RST由低到高变化
    _nop_();

    for(i=0;i<8;i++)//循环8次，每次写1位，先写低位再写高位
    {
        DS1302_IO=addr&0x01;
        addr>>=1;
        DS1302_CLK=1;
        _nop_();
        DS1302_CLK=0;//CLK由低到高产生一个上升沿，从而写入数据
        _nop_();        
    }
    for(i=0;i<8;i++)//循环8次，每次写1位，先写低位再写高位
    {
        DS1302_IO=dat&0x01;
        dat>>=1;
        DS1302_CLK=1;
        _nop_();
        DS1302_CLK=0;
        _nop_();        
    }
    DS1302_RST=0;//RST拉低
    _nop_();    
}

/*******************************************************************************
* 函 数 名       : ds1302_read_byte
* 函数功能         : DS1302读单字节
* 输    入       : addr：地址/命令
* 输    出         : 读取的数据
*******************************************************************************/
u8 ds1302_read_byte(u8 addr)
{
    u8 i=0;
    u8 temp=0;
    u8 value=0;

    DS1302_RST=0;
    _nop_();    
    DS1302_CLK=0;//CLK低电平
    _nop_();
    DS1302_RST=1;//RST由低到高变化
    _nop_();
    
    for(i=0;i<8;i++)//循环8次，每次写1位，先写低位再写高位
    {
        DS1302_IO=addr&0x01;
        addr>>=1;    
        DS1302_CLK=1;
        _nop_();
        DS1302_CLK=0;//CLK由低到高产生一个上升沿，从而写入数据
        _nop_();        
    }
    for(i=0;i<8;i++)//循环8次，每次读1位，先读低位再读高位
    {
        temp=DS1302_IO;
        value=(temp<<7)|(value>>1);//先将value右移1位，然后temp左移7位，最后或运算
        DS1302_CLK=1;
        _nop_();
        DS1302_CLK=0;
        _nop_();        
    }
    DS1302_RST=0;//RST拉低
    _nop_();    
    DS1302_CLK=1;//对于实物中，P3.4口没有外接上拉电阻的，此处代码需要添加，使数据口有一个上升沿脉冲。
    _nop_();
    DS1302_IO = 0;
    _nop_();
    DS1302_IO = 1;
    _nop_();    
    return value;        
}

/*******************************************************************************
* 函 数 名       : ds1302_init
* 函数功能         : DS1302初始化时间
*******************************************************************************/
void ds1302_init(void)
{
    u8 i=0;
    ds1302_write_byte(0x8E,0X00);
    for(i=0;i<7;i++)
    {
        ds1302_write_byte(gWRITE_RTC_ADDR[i],gDS1302_TIME[i]);    
    }
    ds1302_write_byte(0x8E,0X80);    
}

/*******************************************************************************
* 函 数 名       : ds1302_read_time
* 函数功能         : DS1302读取时间
*******************************************************************************/
void ds1302_read_time(void)
{
    u8 i=0;
    for(i=0;i<7;i++)
    {
        gDS1302_TIME[i]=ds1302_read_byte(gREAD_RTC_ADDR[i]);    
    }    
}













