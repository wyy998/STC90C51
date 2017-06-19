#ifndef DELAY
#define DELAY

void delay(unsigned char s)
{
	int i;
	while(s--)
	{
		for(i=0;i<300;i++);
	}
}

#endif