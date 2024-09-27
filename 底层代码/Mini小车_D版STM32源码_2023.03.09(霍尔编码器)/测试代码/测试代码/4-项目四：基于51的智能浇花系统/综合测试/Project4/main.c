#include <reg52.h>
#include <intrins.h>

/*��֪�����������¶���*/
#define uchar unsigned char
#define uint unsigned int


/*���Ŷ���*/
//LCD1602
#define LCD1602_DB P0	//LCD1602��������
sbit LCD1602_RS = P3^6;	 //RS��
sbit LCD1602_RW = P3^5;	 //RW��
sbit LCD1602_EN = P3^4;	 //EN��

//ADC0832
sbit cs  = P2^4;//Ƭѡʹ�ܣ��͵�ƽ��Ч
sbit clk = P2^3;//оƬʱ������
sbit dio = P2^2;//��������DI�����DO

//relay
sbit RELAY = P3^7;
void	RELAY_Control(uint r);

//��ʱ2us
void Delay_2us(void)
{
	_nop_();
	_nop_();
}
/*=================================================
*�������ƣ�Read_Busy
*�������ܣ��ж�1602Һ��æ�����ȴ�
=================================================*/
void Read_Busy()
{
	uchar busy;
	LCD1602_DB = 0xff;//��λ��������
	LCD1602_RS = 0;	  //����RS
	LCD1602_RW = 1;	  //����RW��
	do
	{
		LCD1602_EN = 1;//ʹ��EN
		busy = LCD1602_DB;//��������
		LCD1602_EN = 0;	 //����ʹ���Ա�����һ�β���������
	}while(busy & 0x80); //�ж�״̬��BIT7λ�Ƿ�Ϊ1��Ϊ1���ʾæ������ȴ�
}
/*=================================================
*�������ƣ�LCD1602_Write_Cmd
*�������ܣ�дLCD1602����
*���ã�Read_Busy();
*���룺cmd:Ҫд������
=================================================*/
void LCD1602_Write_Cmd(uchar cmd)
{
	Read_Busy();	 //�ж�æ��æ��ȴ�
	LCD1602_RS = 0;
	LCD1602_RW = 0;	//����RS��RW����ʱ�����1602�μ�������ʹ��˵����������ʱ���½�
	LCD1602_DB = cmd;//д������
	LCD1602_EN = 1;	 //����ʹ�ܶ� ���ݱ����䵽LCD1602��
	LCD1602_EN = 0;	 //����ʹ���Ա�����һ�β���������
}
/*=================================================
*�������ƣ�LCD1602_Write_Dat
*�������ܣ�дLCD1602����
*���ã�Read_Busy();
*���룺dat����Ҫд�������
=================================================*/
void LCD1602_Write_Dat(uchar dat)
{
	Read_Busy();
	LCD1602_RS = 1;
	LCD1602_RW = 0;
	LCD1602_DB = dat;
	LCD1602_EN = 1;
	LCD1602_EN = 0;
}

/*=================================================
*�������ƣ�LCD1602_Dis_Str
*�������ܣ���ָ��λ����ʾ�ַ���
*���ã�LCD1602_Write_Cmd(); LCD1602_Write_Dat();
*���룺x��Ҫ��ʾ�ĺ�����ȡֵ0-40��y��Ҫ��ʾ��������ȡֵ0-1��0Ϊ��һ��,1Ϊ�ڶ��У�
		*str����Ҫ��ʾ���ַ���
=================================================*/
void LCD1602_Dis_Str(uchar x, uchar y, uchar *str)
{
	if(y) x |= 0x40;
	x |= 0x80;
	LCD1602_Write_Cmd(x);
	while(*str != '\0')
	{
		LCD1602_Write_Dat(*str++);
	}
}
/*=================================================
*�������ƣ�Init_LCD1602
*�������ܣ�1602��ʼ��
*���ã�	LCD1602_Write_Cmd();
=================================================*/
void Init_LCD1602()
{
	LCD1602_Write_Cmd(0x38); //	����16*2��ʾ��5*7����8λ���ݽӿ�
	LCD1602_Write_Cmd(0x0c); //����ʾ
	LCD1602_Write_Cmd(0x06); //��дһ�ֽں��ַָ���1
	LCD1602_Write_Cmd(0x01); //�����ʾ
}
/*****************************************
������飺��ȡADC0832����
�������ƣ�ADC_read_data(bit channel)
����˵����chΪ��ڲ�����ch=0ѡ��ͨ��0��ch=1ѡ��ͨ��1
�������أ����ض�ȡ���Ķ�����ADC���ݣ���ʽΪunsigned char
		  ������һֱ0ʱ��ת����������
******************************************/
uchar ADC_read_data(bit channel)
{
	uchar i,dat0=0,dat1=0;
  //------��1���½���֮ǰdi�øߣ������ź�---------

	cs=0;			//Ƭѡ�ź��õͣ�����ADת��оƬ
	clk=0;			//ʱ���õ�ƽ
	
	dio=1;  		//��ʼ�ź�Ϊ�ߵ�ƽ
	Delay_2us();
	clk=1;			//����һ��������,��ʱ�������أ����뿪ʼ�źţ�DI=1��
	Delay_2us();
  	clk=0;			//��1��ʱ���½���
	dio=1;
	Delay_2us();
	
	clk=1;		    // ��2���½�������DI=1����ʾ˫ͨ������������
	Delay_2us();	 
  //------�ڵ�2���½��أ�ģ���ź�����ģʽѡ��1����ģ�źţ�0��˫ģ����źţ�---------		
	clk=0;	
	dio=channel;         // ��3���½���,����DI��ѡ��ͨ��;
	Delay_2us();
	clk=1;
	Delay_2us();

   //------�ڵ�3���½��أ�ģ���ź�����ͨ��ѡ��1��ͨ��CH1��0��ͨ��CH0��------------	
	
	clk=0;
	dio=1;          //���ĸ��½���֮ǰ��DI�øߣ�׼�������� 
	Delay_2us();	
	for(i=0;i<8;i++)                 //��4~11��8���½��ض����ݣ�MSB->LSB��
	{
		clk=1;
		Delay_2us();
		clk=0;
		Delay_2us();
		dat0=dat0<<1|dio;
	}
	for(i=0;i<8;i++)                 //��11~18��8���½��ض����ݣ�LSB->MSB��
	{
		dat1=dat1|((uchar)(dio)<<i);
		clk=1;
		Delay_2us();
		clk=0;
		Delay_2us();
	} 
	cs=1;				  
	return (dat0==dat1)?dat0:0;	    //�ж�dat0��dat1�Ƿ����
}


void RELAY_Control(uint r){
	if(r == 1 ){RELAY = 1 ;}
else RELAY = 0 ;
}

void main()
{
	uchar adc = 0;
	uint humidity = 0;
	uchar LCD_buffer[16] = {"humidity:"};
	Init_LCD1602();//1602��ʼ��
	while(1)
	{
		adc = ADC_read_data(0);//��ȡadcֵ
		humidity = adc * 500.0 / 255;//��adcֵ�����ʪ�ȣ���ʽ���޸�
		if(humidity < 55) RELAY_Control(0);		 //��ʪ�ȣ������Ƽ̵�������
		LCD1602_Dis_Str(0, 0, &LCD_buffer[0]);	//��ʾ�ַ���
		LCD1602_Dis_Str(0, 1, &humidity);				//��ʾ�ַ���
	}
}
