#include<lpc21xx.h>
#include"header.h"
int main()
{
u8 h,m,s,flag,date,month,year,index;
u32 adc_out;
float temp,vout;
int temp2;
uart0_init(9600);
adc_init();
lcd_init();
lcd_cmd(0xc0);
lcd_data('A');
spi0_init();
i2c_init();


/* set rtc time to 11:59:55pm*/
i2c_byte_write_frame(0xD0,0x0,0x55);//set sec
i2c_byte_write_frame(0xD0,0x1,0x59);//set min
i2c_byte_write_frame(0xD0,0x2,0x23);
	i2c_byte_write_frame(0XD0,0X4,0X31);
		i2c_byte_write_frame(0XD0,0X5,0X01);
		i2c_byte_write_frame(0XD0,0X6,0X25);
		i2c_byte_write_frame(0XD0,0X3,0X05);
while(1)
{
h=i2c_byte_read_frame(0xD0,0x2);
m=i2c_byte_read_frame(0xD0,0x1);
s=i2c_byte_read_frame(0xD0,0x0);
		 date=i2c_byte_read_frame(0XD0,0X04);	  
		 month=i2c_byte_read_frame(0XD0,0X05);
		 year=i2c_byte_read_frame(0XD0,0X06);
		 index=i2c_byte_read_frame(0XD0,0X03);
	     

uart0_tx((h/0x10)+48);
uart0_tx((h%0x10)+48);
uart0_tx(':');

uart0_tx((m/0x10)+48);
uart0_tx((m%0x10)+48);
uart0_tx(':');

uart0_tx((s/0x10)+48);
uart0_tx((s%0x10)+48);
uart0_tx_string("\r\n");


lcd_cmd(0x80);
lcd_data((h/0x10)+48);
lcd_data((h%0x10)+48);
lcd_data(':');

lcd_data((m/0x10)+48);
lcd_data((m%0x10)+48);
lcd_data(':');

lcd_data((s/0x10)+48);
lcd_data((s%0x10)+48);

    
	
		 if((h>>5)&1)
		   {
	        flag=1;
	   	   }	
	      else
		   {
			 flag=0;
		    }  
			 if(flag==1)
		    lcd_string(" PM");
		 else
		     lcd_string(" AM");

		 lcd_cmd(0xc0);
			  lcd_data(date/16+48);
		lcd_data(date%16+48);
		lcd_data('/');
	
		lcd_data(month/16+48);
		lcd_data(month%16+48);
		lcd_data('/');
	
		lcd_data(year/16+48);
		lcd_data(year%16+48);
	
		 lcd_cmd(0xcf-6);
		 if(index==1)
		    lcd_string("SUN");
		 if(index==2)
		    lcd_string("MON");
		 if(index==3)
		    lcd_string("TUE");
		 if(index==4)
		    lcd_string("WED");
		 if(index==5)
		    lcd_string("THU");
		 if(index==6)
		    lcd_string("FRI");
		 if(index==7)
		    lcd_string("SAT");



uart0_tx_string("mcp3204 \r\n");
temp2=mcp3204_read(2);
vout=(temp2*5)/4095;
uart0_tx_string("LDR=");
temp=100-(vout*100)/4095;
uart0_int(temp);
 lcd_cmd(0xcf-2);
lcd_integer(temp);
//uart0_int(temp);
uart0_tx_string("  ");
delay_ms(300);




//lcd_cmd(0xc5);
adc_out=adc_read(1);
vout=adc_out*3.3/1023;
temp=(vout-0.5)/0.01;

uart0_tx_string("TEMP=");
uart0_float(temp);
lcd_cmd(0x8c);
lcd_float(temp);
lcd_data('c');
uart0_tx('c');
uart0_tx(' ');

lcd_cmd(0xcA);
adc_out=adc_read(2);
vout=adc_out*3.3/1023;
temp=(vout-0.5)/0.01;

uart0_tx_string("POT=");
uart0_float(temp);
//lcd_float(temp);
//lcd_data('v');
uart0_tx('v');
uart0_tx_string("\r\n");
delay_ms(400);
lcd_cmd(0x01);

 

 }
 }

 