#ifndef __JQ8900_H
#define __JQ8900_H
 
#include "sys.h"
#include "SYS_INT.h"
 
#define SDA PBout(11)
 
void SendData ( u8 addr );    //·¢ËÍº¯Êý¡£
void OnUart_GPIO(void);       //GPIO
void delay1_us(u32 nTimer);
void show_number1(void);
void show_number2(void);
void show_number3(void);
void show_number4(void);
void show_number5(void);
void show_number6(void);
void show_number7(void);
void show_number8(void);
void show_number9(void);
void show_number10(void);
#endif
