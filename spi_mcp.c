#include <LPC21xx.H>
#include"header.h"


#define CS0 (1<<7)
void spi0_init(void)
{
PINSEL0|=0x1500;
IODIR0|=CS0;
IOSET0|=CS0;


S0SPCR=0x20;
S0SPCCR=15;
}

#define spif ((S0SPSR>>7)&1)
/*spi transfer function*/
u8 spi0(u8 data)
{
S0SPDR=data;
while(spif==0);
return S0SPDR;
}



//MCP3204
 #define cs (1<<7)
u32 mcp3204_read(u8 ch_num){
	u8 tempH=0,tempL=0;
	u32 result=0;
	ch_num=ch_num<<6;
	IOCLR0=cs;
	spi0(0x06);
	tempH=spi0(ch_num);//d1,d0
	tempL=spi0(0x00);
	IOSET0=cs;
	tempH&=0x0f;
	result=(tempH<<8)|tempL;
	return result;
}
