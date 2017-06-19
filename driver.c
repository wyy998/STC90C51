#include <reg51.h>
#include "driver.h"
#include "delay.h"


void stop()
{
	left_switch=off;
	right_switch=off;
}

void forward(unsigned char i)
{
	left_switch=on;
	right_switch=on;
	left_con1=on;
	left_con2=off;
	right_con1=off;
	right_con2=on;
	delay(i);
}

void back(unsigned char i)
{
	left_switch=on;
	right_switch=on;
	left_con1=off;
	left_con2=on;
	right_con1=on;
	right_con2=off;
	delay(i);
}

void turn_left(unsigned char i)
{
	left_switch=on;
	right_switch=on;
	left_con1=off;
	left_con2=on;
	right_con1=off;
	right_con2=on;
	delay(i);
}

void turn_right(unsigned char i)
{
	left_switch=on;
	right_switch=on;
	left_con1=on;
	left_con2=off;
	right_con1=on;
	right_con2=off;
	delay(i);
}