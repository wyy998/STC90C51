#include <reg51.h>
#include "bluetooth.h"

int receive()
{
	blue_vcc=1;
	blue_gnd=0;
	return blue_re;
}

void send()
{
	blue_se=1;
}