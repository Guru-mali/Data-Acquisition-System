#include <LPC21xx.H>
#include"header.h"
#include<string.h>
#define THRE ((U0LSR>>5)&1)
//#define RDR (U0LSR&1)

void uart0_init(u32 baud)
{
u32 a[]={15,60,30,15,15};
u32 pclk,result=0;
pclk=a[VPBDIV]*1000000;
result=pclk/(16*baud);
PINSEL0 =0X05;
U0LCR=0X83;
U0DLL=(result) & 0xff ;
U0LCR=0X03;
}

void uart0_tx (u8 data)
{
U0THR=data;
while(THRE==0);
}

void uart0_tx_string(u8 *p)
{
while(*p)
{
U0THR=*p;
while(THRE==0);
p++;
}
}


u8 uart0_rx(void)
{
while(RDR==0);
return U0RBR;
}


 //print ascci of the given charcter
void uart0_ascii(s8 ch)
{
u32 num=ch,i=0,r,temp=0,c=0;
while(num)
{
r=num%10;
c++;
temp=temp*10+r;
num=num/10;
}
if(c==2)
{
while(temp)
{
r=temp%10;
uart0_tx(r+48);
temp=temp/10;
}
}
else
{
while(i<3)
{
r=temp%10;
uart0_tx( r+48);
temp=temp/10;
i++;
}
}
}



//RECEIVNG THE STRING
void uart0_rx_str(u8 *p,int len)
{
u32 i;
for(i=0;i<len;i++)
{
//while(RDR==0);
//p[i]=U0RBR;
p[i]=uart0_rx();
uart0_tx(p[i]);
if(p[i]=='\r')
{
break;
}
}
p[i]='\0';
}

 
//printing the number
void uart0_int(u32 num)
{
 char arr[10];
 u32 i=0,r,len;
 if(num==0)
 {
 uart0_tx('0');
 return ;
 }
 while(num)
 {
 r=num%10;
 arr[i]=r+48;
 i++;
 num=num/10;
 }
 arr[i]='\0';
 for(len=0;arr[len];len++);
 for(i=len-1;arr[i];i--)
 {
 uart0_tx(arr[i]);
 }
 }


//float
void uart0_float(float f)
{
int num,i,j;
num=f;
uart0_int(num);
uart0_tx('.');


f=(f-num);
for(i=0,j=10;i<6;i++,j=j*10)
{
//num=(f*j); //for 6 digits
num=f*10;
}

uart0_int(num);
}
