#include"header.h"
/*4BIT LCD DRIVER */
void lcd_data(u8 data){
	IOCLR1=0XFE<<16;
	IOSET1=((data&0XF0)<<16);
	IOSET1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delay_ms(2);
	IOCLR1=EN;



	IOCLR1=0XFE<<16;
	IOSET1=((data&0X0F)<<20);
	IOSET1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delay_ms(2);
	IOCLR1=EN;
}
void lcd_cmd(u8 cmd){	
	IOCLR1=0XFE<<16;
	IOSET1=((cmd&0XF0)<<16);
	IOCLR1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delay_ms(2);
	IOCLR1=EN;


	IOCLR1=0XFE<<16;
	IOSET1=((cmd&0X0F)<<20);
	IOCLR1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delay_ms(2);
	IOCLR1=EN;
}


 void lcd_init(){
	IODIR1=0XFE<<16;
	PINSEL2=0X0;
	IOCLR0=EN;
	lcd_cmd(0X02);
	lcd_cmd(0X28);
	lcd_cmd(0X0E);
	lcd_cmd(0X01);
}




void lcd_string(u8 *s){
	while(*s){
		lcd_data(*s);
		s++;
	}
}

void lcd_integer(u32 num){
	int i;
	u32 a[100];
	if(num<0)
		{
		lcd_data('-');
		num=-num;
	}
	if(num==0){
	lcd_data('0');
	return;
	}
	for(i=0;num;i++,num/=10)
		a[i]=num%10+48;
	for(i=i-1;i>=0;i--)
		lcd_data(a[i]);
}
void lcd_hex(u32 num){
	u8 temp;
	lcd_string("0X");
	temp=(num&0XF0)>>4;
	if(temp>9)
		lcd_data('A'+temp-10);
	else
		lcd_data(temp+48);
	temp=num&0X0F;
	if(temp>9)
	lcd_data('A'+temp-10);
	else
	lcd_data(temp+48);
}

void lcd_float(float f)
{
int num;
if(f<0)
{
lcd_data('-');
f=-f;
}
if(f==0)
{
lcd_string("0.0");
return;
}
num=f;
lcd_integer(num);
lcd_data('.');
num=(f-num)*10;
lcd_integer(num);
}
