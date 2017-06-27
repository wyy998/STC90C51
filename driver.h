#ifndef DRIVER
#define DRIVER

#define on						1
#define off						0

sbit left_switch	= P1^0;
sbit left_con1		=	P1^1;
sbit left_con2		=	P1^2;
sbit right_con1		=	P1^3;
sbit right_con2		= P1^4;
sbit right_switch	=	P1^5;

void stop();
void turn_left();
void turn_right();
void forward();
void back();
void lock();

#endif