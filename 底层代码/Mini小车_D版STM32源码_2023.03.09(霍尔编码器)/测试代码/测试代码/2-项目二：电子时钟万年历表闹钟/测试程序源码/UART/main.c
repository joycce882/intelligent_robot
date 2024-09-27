#include <reg52.h>
#include <intrins.h>
#include <stdio.h>
#define uint unsigned int
#define uchar unsigned char
//--------PIN-----------//

/*�������߱�������*/

void		UARTInit		(void);
void 		SendData		(unsigned char dat);
void 		SendString	(unsigned char *s );
void	  Delay1000ms	();

uchar num;	//���յ���ֵ

/*-------------- ������--------------*/
void main()
{
		UARTInit(); //���ڳ�ʼ��
	
	
	while(1){ 
			
		TI = 1;
		puts("Hello Wolrd!");   // ÿ�δ�ӡ���ỻ��   ֧�����Ĵ�ӡ 
		while(!TI);
		TI = 0;
		Delay1000ms();
		}

}
/*--------------��غ���--------------*/
//��ʱ����
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

//��дputchar����
char putchar(char c)
{
	SendData(c);
	return c;
}

void UARTInit()
{
	EA = 1;	//�����ж�
	ES = 1; //�򿪴����ж�
	SM0 = 0;	
	SM1 = 1;//���ڹ�����ʽ1,8λUART�����ʿɱ�
	REN = 1;//�����������
	TR1 = 1;//������ʱ��1
	TMOD |= 0x20;//��ʱ��1������ģʽ2 8λ�Զ���װ n  
	TH1 = 0xfd;   // ��������Ĺ�ʽ����õ�
	TL1 = 0xfd; //���ñ�����9600
}

	


// ����һ���ֽ�����
void SendData(unsigned char dat)
{
	SBUF = dat;				// ��Ҫ���͵����ݴ���дSBUF
	while(TI == 0);  	// �ȴ����ͱ�־λ��1
	TI = 0;
}

// �����ַ�������'\0'��ʽ��β
void SendString(unsigned char *s)
{
	while (*s!='\0')		// ����Ƿ񵽽�β
	{
		SendData(*s ++);	// ��ַ���������������
	}
}

//�����жϺ���
void IRQ_UART() interrupt 4
{
	if(RI)//�жϽ����Ƿ����
	{
		num = SBUF;//��SBUF���������ڽ��յ�������
		RI = 0;//���������ձ�־λ	
	}
	if(TI)//�ж��Ƿ������
		TI = 0;//���㷢����ɱ�־λ	
} 



