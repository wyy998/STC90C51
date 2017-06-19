#ifndef BLUETOOTH
#define BLUETOOTH

sbit blue_re=P3^7;
sbit blue_se=P3^6;
sbit blue_vcc=P3^4;
sbit blue_gnd=P3^5;

int receive();
void send();

#endif