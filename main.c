#include <reg51.h>
//#include "delay.h"
#include "driver.h"
//#include "bluetooth.h"

void main()
{
	unsigned char time=3000;
	stop();
	while(receive());
	forward(time);
	back(time);
	turn_left(time);
	turn_right(time);
}