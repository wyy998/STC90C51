#include <reg51.h>
#include "delay.h"
#include "driver.h"
#include "gui.h"
#include "lcd_drive.h"

unsigned char ucBluetoothData;
unsigned char rcv_ack=0;
//unsigned char count=0;
//unsigned char speed=0;
//unsigned char timer_ack=0;
void initial_peripheral();
void initial_myself();

void main()
{
	TFT_Init();
	TFT_ClearScreen(BLACK);
	GUI_WriteASCII(75, 105, "Hello World", RED, BLACK);
	//test
	delay(1000);
	forward();
	delay(3000);
	//init
	initial_myself();
	delay(100);
	initial_peripheral();
	stop();
	while(1)
	{
		while(rcv_ack)
			rcv_ack=0;
		switch (ucBluetoothData)
		{
			case 0x01:
				stop();
				break;
			case 0x02:
				forward();
				break;
			case 0x03:
				turn_left();
				break;
			case 0x04:
				turn_right();
				break;
			case 0x05:
				back();
				break;
			case 0x06:
				lock();
				break;
			case 0x07:
				TFT_ClearScreen(BLACK);
				GUI_WriteASCII(75, 105, "Smart-Car", GREEN, BLACK);
				break;
			default://forward();
				break;
		}
	}
}

void usart_receive(void) interrupt 4
{
	if (RI == 1)
	{
		RI = 0;
		ucBluetoothData = SBUF;
		rcv_ack=1;
	}
	else
	{
		TI = 0;
	}
}

void initial_myself()
{
	TMOD = 0x01;//设置定时器0为工作方式1
	TH0 = 0xff;
	TL0 = 0x28;

	//配置串口
	SCON = 0x50;
	TMOD = 0x21;
	TH1 = TL1 = -(11095200L / 12 / 32 / 9600);
	IP = 0x10;
}

void initial_peripheral()
{
	EA = 1;//开总中断
	ES = 1;//允许串口中断
	ET0 = 1;//允许定时器中断
	TR0 = 1;//启动定时器
	TR1 = 1;//
}