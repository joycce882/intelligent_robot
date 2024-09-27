#ifndef __DS3231_H
#define __DS3231_H

#include "config.h"
#include "clock_param.h"

#define DS_SDADIR_IN()	{GPIOB->CRL&=0XFF0FFFFF;GPIOB->CRL|=(u32)8<<20;}
#define DS_SDADIR_OUT() {GPIOB->CRL&=0XFF0FFFFF;GPIOB->CRL|=(u32)8<<20;}

#define DS_SCL		PAout(6)
#define DS_SDA		PAout(5)
#define DS_SDAin	PAin(5)

/***********ÓÃ»§º¯Êý***********/
void ds3231_Init(void);
unsigned char ds3231_Read(unsigned char addr);
void ds3231_Write(unsigned char addr, unsigned short int dat);
void ds3231_writeTime(void);
void ds3231_displayTime(enum clockShowSwitch_e showMode);
void ds3231_serialSetTime(void);
void ds3231_readTime(void);
void ds3231_setAlarm(enum alarm_e alarmx, alarmSetTimeObject *alarmxSet);
float ds3231_readTemper(void);
/***********µ×²ãº¯Êý***********/
unsigned char BCDtoNum(unsigned char val);
unsigned short int NumtoBCD(unsigned char val);
/***********¼Ä´æÆ÷***********/
#define DS3231_ADDR_Write  	0xd0    
#define DS3231_ADDR_Read  	0xd1
#define DS3231_CONTROL   		0x0e    //¿ØÖÆ¼Ä´æÆ÷
#define DS3231_STATUS    		0x0f    //×´Ì¬¼Ä´æÆ÷

#define DS3231_ADDR_Second	0x00
#define DS3231_ADDR_Minute	0x01
#define DS3231_ADDR_Hour		0x02
#define DS3231_ADDR_Day			0x03
#define DS3231_ADDR_Date		0x04
#define DS3231_ADDR_Month		0x05 		/*Month/Century*/
#define DS3231_ADDR_Year		0x06

#define DS3231_AL1SEC				0x07
#define DS3231_AL1MIN				0x08
#define DS3231_AL1HOUR			0x09
#define DS3231_AL1DAY				0x0a

#define DS3231_AL2MIN				0x0b
#define DS3231_AL2HOUR			0x0c
#define DS3231_AL2DAY				0x0d

#define DS3231_AgingOffset	0x10
#define DS3231_TempM				0x11
#define DS3231_TempL				0x12

#endif
