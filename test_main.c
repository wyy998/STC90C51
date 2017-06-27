#include <reg51.h>
#include "delay.h"
#include "driver.h"
#include "gui.h"
#include "lcd_drive.h"

unsigned char ucBluetoothData;
unsigned char rcv_ack=0;
unsigned char rcv_data[20];
void initial_peripheral();
void initial_myself();
//void dispASCII(int xpos,int ypos,unsigned char t);

void main()
{
	//test driver
	forward();
	delay(3000);
	initial_myself();
	delay(100);
	initial_peripheral();
	stop();
	
	//display init
	TFT_Init();
	TFT_ClearScreen(BLACK);
	GUI_ShowPicture(30,120,240,51);
	GUI_WriteASCII(70,220,"Hello World!",GREEN,BLACK);
	//GUI_ShowPicture(30,150,240,51);

	while(1)
	{
		while(rcv_ack)
			rcv_ack=0;
		switch (ucBluetoothData)		//由接收数据判断下一步操作
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
				//display
				//count=0;
				//while(ucBluetoothData!='\n' && rcv_ack)
				//{
					//rcv_ack=0;
					//rcv_data[count++]=ucBluetoothData;
				//}
				TFT_ClearScreen(BLACK);
				GUI_WriteASCII(100,75,"This is a",GREEN,BLACK);
				GUI_WriteASCII(100,105,"Smart Car",GREEN,BLACK);
				break;
			default://forward();
				break;
		}
	}
}

void usart_receive(void) interrupt 4 //串口中断
{
	//int i;
	if (RI == 1)
	{
		RI = 0;
		ucBluetoothData = SBUF;
		rcv_ack=1;
		/*
		if(ucBluetoothData>0x07)
		{	
			if(ucBluetoothData!='\n')
				rcv_data[count++]=ucBluetoothData;
			if(ucBluetoothData=='\n')
			{
				//rcv_data[count]='\0';
				TFT_ClearScreen(BLACK);
				GUI_WriteASCII(70,75,"TYUT",RED,BLACK);
				for(i=0;i<count;i++)
					dispASCII(75+5*i,120,rcv_data[i]);
				
				count=0;
			}
		}
		*/
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
/*
void dispASCII(int xpos,int ypos,unsigned char t)
{
	switch (t)
	{
		case 0x30:GUI_WriteASCII(xpos,ypos,'0',GREEN,BLACK);break;
		case 0x31:GUI_WriteASCII(xpos,ypos,'1',GREEN,BLACK);break;
		case 0x32:GUI_WriteASCII(xpos,ypos,'2',GREEN,BLACK);break;
		case 0x33:GUI_WriteASCII(xpos,ypos,'3',GREEN,BLACK);break;
		case 0x34:GUI_WriteASCII(xpos,ypos,'4',GREEN,BLACK);break;
		case 0x35:GUI_WriteASCII(xpos,ypos,'5',GREEN,BLACK);break;
		case 0x36:GUI_WriteASCII(xpos,ypos,'6',GREEN,BLACK);break;
		case 0x37:GUI_WriteASCII(xpos,ypos,'7',GREEN,BLACK);break;
		case 0x38:GUI_WriteASCII(xpos,ypos,'8',GREEN,BLACK);break;
		case 0x39:GUI_WriteASCII(xpos,ypos,'9',GREEN,BLACK);break;
		case 0x41:GUI_WriteASCII(xpos,ypos,'A',GREEN,BLACK);break;
		case 0x42:GUI_WriteASCII(xpos,ypos,'B',GREEN,BLACK);break;
		case 0x43:GUI_WriteASCII(xpos,ypos,'C',GREEN,BLACK);break;
		case 0x44:GUI_WriteASCII(xpos,ypos,'D',GREEN,BLACK);break;
		case 0x45:GUI_WriteASCII(xpos,ypos,'E',GREEN,BLACK);break;
		case 0x46:GUI_WriteASCII(xpos,ypos,'F',GREEN,BLACK);break;
		case 0x47:GUI_WriteASCII(xpos,ypos,'G',GREEN,BLACK);break;
		case 0x48:GUI_WriteASCII(xpos,ypos,'H',GREEN,BLACK);break;
		case 0x49:GUI_WriteASCII(xpos,ypos,'I',GREEN,BLACK);break;
		case 0x4A:GUI_WriteASCII(xpos,ypos,'J',GREEN,BLACK);break;
		case 0x4B:GUI_WriteASCII(xpos,ypos,'K',GREEN,BLACK);break;
		case 0x4C:GUI_WriteASCII(xpos,ypos,'L',GREEN,BLACK);break;
		case 0x4D:GUI_WriteASCII(xpos,ypos,'M',GREEN,BLACK);break;
		case 0x4E:GUI_WriteASCII(xpos,ypos,'N',GREEN,BLACK);break;
		case 0x4F:GUI_WriteASCII(xpos,ypos,'O',GREEN,BLACK);break;
		case 0x50:GUI_WriteASCII(xpos,ypos,'P',GREEN,BLACK);break;
		case 0x51:GUI_WriteASCII(xpos,ypos,'Q',GREEN,BLACK);break;
		case 0x52:GUI_WriteASCII(xpos,ypos,'R',GREEN,BLACK);break;
		case 0x53:GUI_WriteASCII(xpos,ypos,'S',GREEN,BLACK);break;
		case 0x54:GUI_WriteASCII(xpos,ypos,'T',GREEN,BLACK);break;
		case 0x55:GUI_WriteASCII(xpos,ypos,'U',GREEN,BLACK);break;
		case 0x56:GUI_WriteASCII(xpos,ypos,'V',GREEN,BLACK);break;
		case 0x57:GUI_WriteASCII(xpos,ypos,'W',GREEN,BLACK);break;
		case 0x58:GUI_WriteASCII(xpos,ypos,'X',GREEN,BLACK);break;
		case 0x59:GUI_WriteASCII(xpos,ypos,'Y',GREEN,BLACK);break;
		case 0x5A:GUI_WriteASCII(xpos,ypos,'Z',GREEN,BLACK);break;
		default:break;
	}
}
*/