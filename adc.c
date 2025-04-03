#include"header.h"
#define DONE ((ADDR>>31)&1)
void adc_init(void){
	PINSEL1|=0X15400000;  //P0.27 TO P0.30 pins are Ain0 - Ain3
	ADCR=0x00200400;
} 
u32 adc_read(u8 ch_num){
	u32 result=0;
	ADCR|=(1<<ch_num);/* Select channel num*/
	ADCR|=(1<<24);//set 24th bit  to start ADC conversion/
	while(((ADDR>>31)&1)==0);//wait for DONE flag to be set/
	ADCR^=(1<<24);//clear 24th bit to stop the ADC conversion/
	ADCR^=(1<<ch_num);/* diselect channel num*/
	result=(ADDR>>6)&0x3FF; /* Extract 10 bits difital result*/
	return result; /* retuen result*/
}
