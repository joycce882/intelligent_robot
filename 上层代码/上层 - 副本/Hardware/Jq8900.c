#include "jq8900.h"
#include "Delay.h"
#include "stm32f10x.h"
 
///
//函	  OnUart_GPIO(void)
//功	  能：语音模块一线串口IO口
//输入参数: void
//输出参数: void
//说	  明：
//


//
//阿摆提示：请不要随意修改注释内容 您会后悔哦
//啦啦啦
//

void OnUart_GPIO(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
		RCC->APB2ENR|=1<<3;   //GPIOB
		
		//GPIOB.11
		GPIOB->CRH&=0xFFFF0FFF;     //清零 
		GPIOB->CRH|=0x00003000;     //推挽输出	50MHZ
		GPIOB->ODR=~(1<<11);        //B.11低	
 
	
}
///
//函	  数：SendData(u8 addr)
//功	  能：语音模块一线串口
//输入参数: addr要发送的0x数
//输出参数: void
//说	  明：
//
void SendData(u8 addr)//发送函数。
{
    u8 i;
 
     /*发送时关掉中断，防止中断影响时序  */
    SDA = 1; /*开始拉高*/
    Delay_us ( 1000 );
    SDA = 0; /*开始引导码*/
    Delay_us ( 3200 );/*此处延时最少要大于2ms*/
    for ( i = 0; i < 8; i++ ) /*总共8位数据  */
    {
        SDA = 1;
        if ( addr & 0x01 ) /*3:1表示数据位1,每个位用两个脉冲表示  */
        {
            Delay_us ( 600 );
            SDA = 0;
            Delay_us ( 200 );
        }
        else              /*1：3表示数据位0 ,每个位用两个脉冲表示  */
        {
            Delay_us ( 200 );
            SDA = 0;
            Delay_us ( 600 );
        }
        addr >>= 1;
    }
    SDA = 1;
    
		//恢复中断
}
void show_number1()
{
    //设置音量为20
    SendData(0x0a);    //清空数字
    SendData(0x03);    //音量20
    SendData(0x00);
    SendData(0x0c);    //设置音量
    Delay_ms(2000);    //延时
    
    //选取曲目1播放
    SendData(0x0a);//清空数字
    SendData(0x01);//曲目数字，对应00001.mp3
    SendData(0x0b);//选曲播放
    Delay_ms(2000);
    
//    //开始播放
//    SendData(0x11);//开始播放
//    Delay_ms(2000);
}
void show_number2()
{
    //设置音量为20
    SendData(0x0a);    //清空数字
    SendData(0x03);    //音量20
    SendData(0x00);
    SendData(0x0c);    //设置音量
    Delay_ms(2000);    //延时
    
    //选取曲目1播放
    SendData(0x0a);//清空数字
    SendData(0x02);//曲目数字，对应00001.mp3
    SendData(0x0b);//选曲播放
    Delay_ms(2000);
    
//    //开始播放
//    SendData(0x11);//开始播放
//    Delay_ms(2000);
}
void show_number3()
{
    //设置音量为20
    SendData(0x0a);    //清空数字
    SendData(0x03);    //音量20
    SendData(0x00);
    SendData(0x0c);    //设置音量
    Delay_ms(2000);    //延时
    
    //选取曲目1播放
    SendData(0x0a);//清空数字
    SendData(0x03);//曲目数字，对应00001.mp3
    SendData(0x0b);//选曲播放
    Delay_ms(2000);
	
//    //开始播放
//    SendData(0x11);//开始播放
//    Delay_ms(2000);
}
void show_number4()
{
    //设置音量为20
    SendData(0x0a);    //清空数字
    SendData(0x03);    //音量20
    SendData(0x00);
    SendData(0x0c);    //设置音量
    Delay_ms(2000);    //延时
    
    //选取曲目1播放
    SendData(0x0a);//清空数字
    SendData(0x04);//曲目数字，对应00001.mp3
    SendData(0x0b);//选曲播放
    Delay_ms(2000);
    
//    //开始播放
//    SendData(0x11);//开始播放
//    Delay_ms(2000);
}
void show_number5()
{
    //设置音量为20
    SendData(0x0a);    //清空数字
    SendData(0x03);    //音量20
    SendData(0x00);
    SendData(0x0c);    //设置音量
    Delay_ms(2000);    //延时
    
    //选取曲目1播放
    SendData(0x0a);//清空数字
    SendData(0x05);//曲目数字，对应00001.mp3
    SendData(0x0b);//选曲播放
    Delay_ms(2000);
    
//    //开始播放
//    SendData(0x11);//开始播放
//    Delay_ms(2000);
}
void show_number6()
{
    //设置音量为20
    SendData(0x0a);    //清空数字
    SendData(0x03);    //音量20
    SendData(0x00);
    SendData(0x0c);    //设置音量
    Delay_ms(2000);    //延时
    
    //选取曲目1播放
    SendData(0x0a);//清空数字
    SendData(0x06);//曲目数字，对应00001.mp3
    SendData(0x0b);//选曲播放
    Delay_ms(2000);
    
//    //开始播放
//    SendData(0x11);//开始播放
//    Delay_ms(2000);
}
void show_number7()
{
    //设置音量为20
    SendData(0x0a);    //清空数字
    SendData(0x03);    //音量20
    SendData(0x00);
    SendData(0x0c);    //设置音量
    Delay_ms(2000);    //延时
    
    //选取曲目1播放
    SendData(0x0a);//清空数字
    SendData(0x07);//曲目数字，对应00001.mp3
    SendData(0x0b);//选曲播放
    Delay_ms(2000);
    
    //开始播放
    SendData(0x11);//开始播放
    Delay_ms(2000);
}
void show_number8()
{
    //设置音量为20
    SendData(0x0a);    //清空数字
    SendData(0x03);    //音量20
    SendData(0x00);
    SendData(0x0c);    //设置音量
    Delay_ms(2000);    //延时
    
    //选取曲目1播放
    SendData(0x0a);//清空数字
    SendData(0x08);//曲目数字，对应00001.mp3
    SendData(0x0b);//选曲播放
    Delay_ms(2000);
    
//    //开始播放
//    SendData(0x11);//开始播放
//    Delay_ms(2000);
}
void show_number9()
{
    //设置音量为20
    SendData(0x0a);    //清空数字
    SendData(0x03);    //音量20
    SendData(0x00);
    SendData(0x0c);    //设置音量
    Delay_ms(2000);    //延时
    
    //选取曲目1播放
    SendData(0x0a);//清空数字
    SendData(0x09);//曲目数字，对应00009.mp3
    SendData(0x0b);//选曲播放
    Delay_ms(2000);
    
//    //开始播放
//    SendData(0x11);//开始播放
//    Delay_ms(2000);
}
void show_number10()
{
    //设置音量为20
    SendData(0x0a);    //清空数字
    SendData(0x03);    //音量20
    SendData(0x00);
    SendData(0x0c);    //设置音量
    Delay_ms(2000);    //延时
    
    //选取曲目1播放
    SendData(0x0a);//清空数字
		SendData(0x01);
    SendData(0x00);//曲目数字，对应00010.mp3
    SendData(0x0b);//选曲播放
    Delay_ms(2000);
    
//    //开始播放
//    SendData(0x11);//开始播放
//    Delay_ms(2000);
}

