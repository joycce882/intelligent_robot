#include <reg52.h>
#include <intrins.h>
//-------LED-----------//
sbit LED3 = P1^0;
sbit LED4 = P1^1;
sbit LED5 = P1^2;
sbit LED6 = P1^3;	
sbit LED7 = P1^4;
//--------按键矩阵----------//
sbit L_KEY8	=	P2^0;
sbit L_KEY7	=	P2^1;
sbit L_KEY6	=	P2^2; 
sbit L_KEY5	=	P2^3;//代表列的四个引脚

sbit H_KEY4	=	P2^4;
sbit H_KEY3	=	P2^5;
sbit H_KEY2	=	P1^5;
sbit H_KEY1	=	P1^6;//代表行的四个引脚	

/*函数或者变量声明*/
char key_scan();
void KeyMatrixTest(void);
/*-------------- 主函数--------------*/
void main()
{

		while(1){
		KeyMatrixTest();
		}

}

/*--------------相关函数--------------*/
char key_scan() {//按键矩阵扫描
    char num =0;
//第一行
    H_KEY1 = 0;
    if(L_KEY8==0)
        num = 1;
    if(L_KEY7==0)
        num = 2;
    if(L_KEY6==0)
        num = 3;
    if(L_KEY5==0)
        num = 4;
    H_KEY1 = 1;
//第二行
    H_KEY2 = 0;
    if(L_KEY8==0)
        num = 5;
    if(L_KEY7==0)
        num = 6;
    if(L_KEY6==0)
        num = 7;
    if(L_KEY5==0)
        num = 8;
    H_KEY2 = 1;
//第三行
    H_KEY3 = 0;
    if(L_KEY8==0)
        num = 9;
    if(L_KEY7==0)
        num = 10;
    if(L_KEY6==0)
        num = 11;
    if(L_KEY5==0)
        num = 12;
    H_KEY3 = 1;
//第四行
    H_KEY4 = 0;
    if(L_KEY8==0)
        num = 13;
    if(L_KEY7==0)
        num = 14;
    if(L_KEY6==0)
        num = 15;
    if(L_KEY5==0)
        num = 16;
    H_KEY4 = 1;
		
	return num;
}
char num = 0;
void KeyMatrixTest(void){									//按键矩阵测试
	
    P2=0xff;    //清空P2口，防止原有数据影响
    P1=0xff;    //清空P1口，防止原有数据影响	
    num = key_scan();
		switch(num){
								case (1) : 			LED4=0;			break;
								case (2) : 			LED5=0;			break;	
								case (3) : 			LED6=0;			break;
								case (4) : 			LED7=0;			break;
								case (5) : 			LED4=0;			break;
								case (6) : 			LED5=0;			break;	
								case (7) : 			LED6=0;			break;
								case (8) : 			LED7=0;			break;
								case (9) : 			LED4=0;			break;
								case (10) : 		LED5=0;			break;	
								case (11) : 		LED6=0;			break;
								case (12) : 		LED7=0;			break;
								case (13) : 		LED4=0;			break;
								case (14) : 		LED5=0;			break;	
								case (15) : 		LED6=0;			break;
								case (16) : 		LED7=0;			break;
								}
	
}
