#include <reg52.h>
#include <intrins.h>
//-------BEEP-PIN-----------//
sbit BEEP = P1^5;

//-------KEY-PIN-----------//
sbit KEY1 = P3^0;
sbit KEY2 = P3^1;
sbit KEY3 = P3^2;
sbit KEY4 = P3^3;

//-------�����-PIN-----------//
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

sbit LSA	=	P2^2; //����ܽ�
sbit LSB	=	P2^3;
sbit LSC	=	P2^4;

sbit LE 	= P2^5;  //���巽��

u8 code gsmg_code[16]={	0x3f  , 0x06 , 0x5b , 0x4f , 
												0x66 	, 0x6d , 0x7d , 0x07 , 
												0x7f  , 0x6f , 0x77 , 0x7c ,																//Line   Bleak  Bleak   Spot
												0x39 	, 0x5e , 0x79 , 0x71};//��������ܶ�ѡ���ݼ���ʾ������//0x40   0x00   0xFF   0x80




//-------DS1302-PIN-----------//
sbit DS1302_RST	=	P3^5;
sbit DS1302_CLK	=	P3^6;
sbit DS1302_IO	=	P3^4;

//---DS1302д��Ͷ�ȡʱ����ĵ�ַ����---//
//---���ʱ�������� ���λ��дλ;-------//
u8 gREAD_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d}; 
u8 gWRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};

//---DS1302ʱ�ӳ�ʼ��2021��5��20��������13��51��47�롣---//
//---�洢˳�������ʱ��������,�洢��ʽ����BCD��---//
u8 gDS1302_TIME[7] = {0x47, 0x51, 0x13, 0x20, 0x04, 0x05, 0x21};


/*�������߱�������*/
void	Delay100ms();
void 	delay_10us(u16 ten_us);
void 	Delay100us();
void  BEEP_Test(void);

void ds1302_init(void);
void ds1302_read_time(void);

void smg_display(u8 dat[],u8 pos);
/*-------------- ������--------------*/
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


void delay_10us(u16 ten_us)
{
    while(ten_us--);    
}
/************************************************************************************************************/
//�����

void smg_display(u8 dat[],u8 pos)
{
    u8 i=0;
    u8 pos_temp=pos-1;

    for(i=pos_temp;i<8;i++)
    {
           switch(i)//λѡ
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
        P0=dat[i-pos_temp];//���Ͷ�ѡ����
        delay_10us(100);//��ʱһ��ʱ�䣬�ȴ���ʾ�ȶ�
        P0=0x00;//
    }
}

/*--------------��غ���--------------*/
/************************************************************************************************************/
//������
void BEEP_Test(void){
		BEEP = 1 ;//����
		Delay100ms();
		BEEP = 0 ;//��
		Delay100ms();
}
/************************************************************************************************************/
//DS1302s
/*******************************************************************************
* �� �� ��       : ds1302_write_byte
* ��������         : DS1302д���ֽ�
* ��    ��       : addr����ַ/����
                   dat������
* ��    ��         : ��
*******************************************************************************/
void ds1302_write_byte(u8 addr,u8 dat)
{
    u8 i=0;
    
    DS1302_RST=0;
    _nop_();    
    DS1302_CLK=0;//CLK�͵�ƽ
    _nop_();
    DS1302_RST=1;//RST�ɵ͵��߱仯
    _nop_();

    for(i=0;i<8;i++)//ѭ��8�Σ�ÿ��д1λ����д��λ��д��λ
    {
        DS1302_IO=addr&0x01;
        addr>>=1;
        DS1302_CLK=1;
        _nop_();
        DS1302_CLK=0;//CLK�ɵ͵��߲���һ�������أ��Ӷ�д������
        _nop_();        
    }
    for(i=0;i<8;i++)//ѭ��8�Σ�ÿ��д1λ����д��λ��д��λ
    {
        DS1302_IO=dat&0x01;
        dat>>=1;
        DS1302_CLK=1;
        _nop_();
        DS1302_CLK=0;
        _nop_();        
    }
    DS1302_RST=0;//RST����
    _nop_();    
}

/*******************************************************************************
* �� �� ��       : ds1302_read_byte
* ��������         : DS1302�����ֽ�
* ��    ��       : addr����ַ/����
* ��    ��         : ��ȡ������
*******************************************************************************/
u8 ds1302_read_byte(u8 addr)
{
    u8 i=0;
    u8 temp=0;
    u8 value=0;

    DS1302_RST=0;
    _nop_();    
    DS1302_CLK=0;//CLK�͵�ƽ
    _nop_();
    DS1302_RST=1;//RST�ɵ͵��߱仯
    _nop_();
    
    for(i=0;i<8;i++)//ѭ��8�Σ�ÿ��д1λ����д��λ��д��λ
    {
        DS1302_IO=addr&0x01;
        addr>>=1;    
        DS1302_CLK=1;
        _nop_();
        DS1302_CLK=0;//CLK�ɵ͵��߲���һ�������أ��Ӷ�д������
        _nop_();        
    }
    for(i=0;i<8;i++)//ѭ��8�Σ�ÿ�ζ�1λ���ȶ���λ�ٶ���λ
    {
        temp=DS1302_IO;
        value=(temp<<7)|(value>>1);//�Ƚ�value����1λ��Ȼ��temp����7λ����������
        DS1302_CLK=1;
        _nop_();
        DS1302_CLK=0;
        _nop_();        
    }
    DS1302_RST=0;//RST����
    _nop_();    
    DS1302_CLK=1;//����ʵ���У�P3.4��û�������������ģ��˴�������Ҫ��ӣ�ʹ���ݿ���һ�����������塣
    _nop_();
    DS1302_IO = 0;
    _nop_();
    DS1302_IO = 1;
    _nop_();    
    return value;        
}

/*******************************************************************************
* �� �� ��       : ds1302_init
* ��������         : DS1302��ʼ��ʱ��
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
* �� �� ��       : ds1302_read_time
* ��������         : DS1302��ȡʱ��
*******************************************************************************/
void ds1302_read_time(void)
{
    u8 i=0;
    for(i=0;i<7;i++)
    {
        gDS1302_TIME[i]=ds1302_read_byte(gREAD_RTC_ADDR[i]);    
    }    
}













