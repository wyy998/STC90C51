#ifndef DRIVER
#define DRIVER

#define on						1
#define off						0

sbit left_switch	= P0^2;
sbit left_con1		=	P0^0;
sbit left_con2		=	P0^1;
sbit right_switch	=	P0^5;
sbit right_con1		=	P0^3;
sbit right_con2		= P0^4;

void stop();
void turn_left();
void turn_right();
void forward();
void back();
void lock();

#endif