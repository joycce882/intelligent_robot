#include "jq8900.h"
#include "Delay.h"
#include "stm32f10x.h"
 
///
//��	  OnUart_GPIO(void)
//��	  �ܣ�����ģ��һ�ߴ���IO��
//�������: void
//�������: void
//˵	  ����
//


//
//������ʾ���벻Ҫ�����޸�ע������ ������Ŷ
//������
//

void OnUart_GPIO(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
		RCC->APB2ENR|=1<<3;   //GPIOB
		
		//GPIOB.11
		GPIOB->CRH&=0xFFFF0FFF;     //���� 
		GPIOB->CRH|=0x00003000;     //�������	50MHZ
		GPIOB->ODR=~(1<<11);        //B.11��	
 
	
}
///
//��	  ����SendData(u8 addr)
//��	  �ܣ�����ģ��һ�ߴ���
//�������: addrҪ���͵�0x��
//�������: void
//˵	  ����
//
void SendData(u8 addr)//���ͺ�����
{
    u8 i;
 
     /*����ʱ�ص��жϣ���ֹ�ж�Ӱ��ʱ��  */
    SDA = 1; /*��ʼ����*/
    Delay_us ( 1000 );
    SDA = 0; /*��ʼ������*/
    Delay_us ( 3200 );/*�˴���ʱ����Ҫ����2ms*/
    for ( i = 0; i < 8; i++ ) /*�ܹ�8λ����  */
    {
        SDA = 1;
        if ( addr & 0x01 ) /*3:1��ʾ����λ1,ÿ��λ�����������ʾ  */
        {
            Delay_us ( 600 );
            SDA = 0;
            Delay_us ( 200 );
        }
        else              /*1��3��ʾ����λ0 ,ÿ��λ�����������ʾ  */
        {
            Delay_us ( 200 );
            SDA = 0;
            Delay_us ( 600 );
        }
        addr >>= 1;
    }
    SDA = 1;
    
		//�ָ��ж�
}
void show_number1()
{
    //��������Ϊ20
    SendData(0x0a);    //�������
    SendData(0x03);    //����20
    SendData(0x00);
    SendData(0x0c);    //��������
    Delay_ms(2000);    //��ʱ
    
    //ѡȡ��Ŀ1����
    SendData(0x0a);//�������
    SendData(0x01);//��Ŀ���֣���Ӧ00001.mp3
    SendData(0x0b);//ѡ������
    Delay_ms(2000);
    
//    //��ʼ����
//    SendData(0x11);//��ʼ����
//    Delay_ms(2000);
}
void show_number2()
{
    //��������Ϊ20
    SendData(0x0a);    //�������
    SendData(0x03);    //����20
    SendData(0x00);
    SendData(0x0c);    //��������
    Delay_ms(2000);    //��ʱ
    
    //ѡȡ��Ŀ1����
    SendData(0x0a);//�������
    SendData(0x02);//��Ŀ���֣���Ӧ00001.mp3
    SendData(0x0b);//ѡ������
    Delay_ms(2000);
    
//    //��ʼ����
//    SendData(0x11);//��ʼ����
//    Delay_ms(2000);
}
void show_number3()
{
    //��������Ϊ20
    SendData(0x0a);    //�������
    SendData(0x03);    //����20
    SendData(0x00);
    SendData(0x0c);    //��������
    Delay_ms(2000);    //��ʱ
    
    //ѡȡ��Ŀ1����
    SendData(0x0a);//�������
    SendData(0x03);//��Ŀ���֣���Ӧ00001.mp3
    SendData(0x0b);//ѡ������
    Delay_ms(2000);
	
//    //��ʼ����
//    SendData(0x11);//��ʼ����
//    Delay_ms(2000);
}
void show_number4()
{
    //��������Ϊ20
    SendData(0x0a);    //�������
    SendData(0x03);    //����20
    SendData(0x00);
    SendData(0x0c);    //��������
    Delay_ms(2000);    //��ʱ
    
    //ѡȡ��Ŀ1����
    SendData(0x0a);//�������
    SendData(0x04);//��Ŀ���֣���Ӧ00001.mp3
    SendData(0x0b);//ѡ������
    Delay_ms(2000);
    
//    //��ʼ����
//    SendData(0x11);//��ʼ����
//    Delay_ms(2000);
}
void show_number5()
{
    //��������Ϊ20
    SendData(0x0a);    //�������
    SendData(0x03);    //����20
    SendData(0x00);
    SendData(0x0c);    //��������
    Delay_ms(2000);    //��ʱ
    
    //ѡȡ��Ŀ1����
    SendData(0x0a);//�������
    SendData(0x05);//��Ŀ���֣���Ӧ00001.mp3
    SendData(0x0b);//ѡ������
    Delay_ms(2000);
    
//    //��ʼ����
//    SendData(0x11);//��ʼ����
//    Delay_ms(2000);
}
void show_number6()
{
    //��������Ϊ20
    SendData(0x0a);    //�������
    SendData(0x03);    //����20
    SendData(0x00);
    SendData(0x0c);    //��������
    Delay_ms(2000);    //��ʱ
    
    //ѡȡ��Ŀ1����
    SendData(0x0a);//�������
    SendData(0x06);//��Ŀ���֣���Ӧ00001.mp3
    SendData(0x0b);//ѡ������
    Delay_ms(2000);
    
//    //��ʼ����
//    SendData(0x11);//��ʼ����
//    Delay_ms(2000);
}
void show_number7()
{
    //��������Ϊ20
    SendData(0x0a);    //�������
    SendData(0x03);    //����20
    SendData(0x00);
    SendData(0x0c);    //��������
    Delay_ms(2000);    //��ʱ
    
    //ѡȡ��Ŀ1����
    SendData(0x0a);//�������
    SendData(0x07);//��Ŀ���֣���Ӧ00001.mp3
    SendData(0x0b);//ѡ������
    Delay_ms(2000);
    
    //��ʼ����
    SendData(0x11);//��ʼ����
    Delay_ms(2000);
}
void show_number8()
{
    //��������Ϊ20
    SendData(0x0a);    //�������
    SendData(0x03);    //����20
    SendData(0x00);
    SendData(0x0c);    //��������
    Delay_ms(2000);    //��ʱ
    
    //ѡȡ��Ŀ1����
    SendData(0x0a);//�������
    SendData(0x08);//��Ŀ���֣���Ӧ00001.mp3
    SendData(0x0b);//ѡ������
    Delay_ms(2000);
    
//    //��ʼ����
//    SendData(0x11);//��ʼ����
//    Delay_ms(2000);
}
void show_number9()
{
    //��������Ϊ20
    SendData(0x0a);    //�������
    SendData(0x03);    //����20
    SendData(0x00);
    SendData(0x0c);    //��������
    Delay_ms(2000);    //��ʱ
    
    //ѡȡ��Ŀ1����
    SendData(0x0a);//�������
    SendData(0x09);//��Ŀ���֣���Ӧ00009.mp3
    SendData(0x0b);//ѡ������
    Delay_ms(2000);
    
//    //��ʼ����
//    SendData(0x11);//��ʼ����
//    Delay_ms(2000);
}
void show_number10()
{
    //��������Ϊ20
    SendData(0x0a);    //�������
    SendData(0x03);    //����20
    SendData(0x00);
    SendData(0x0c);    //��������
    Delay_ms(2000);    //��ʱ
    
    //ѡȡ��Ŀ1����
    SendData(0x0a);//�������
		SendData(0x01);
    SendData(0x00);//��Ŀ���֣���Ӧ00010.mp3
    SendData(0x0b);//ѡ������
    Delay_ms(2000);
    
//    //��ʼ����
//    SendData(0x11);//��ʼ����
//    Delay_ms(2000);
}

