#include"header.h"
#define SI ((I2CONSET>>3)&1)
void i2c_init(void){
	PINSEL0|=0x50;//P0.2->SCL & P0.3->SDA
	I2SCLH=I2SCLL=75;//100kbps ...standard speed
	I2CONSET=(1<<6);//Enable I2C peripherral
}

	 //byte Writing
void i2c_byte_write_frame(u8 sa,u8 mr,u8 data){
	//Generate start condition/	
	I2CONSET=(1<<5);//STA=1
	I2CONCLR=(1<<3);//clear SI flag
	while(SI==0);
	I2CONCLR=(1<<5);//STA=0;
	if(I2STAT!=0X08){
	//	uart0_tx_string("Err:start");
		goto exit;
	}
	/* send SA+W & check ACK*/	
	I2DAT=sa;//send SA+W
	I2CONCLR=(1<<3);//clear SI flag SI=0
	while(SI==0);
	if(I2STAT==0X20){
      uart0_tx_string("err:SA+W");
		goto exit;
	}
	/* send m/r address & check ACK*/	
	I2DAT=mr;//send m/r address
	I2CONCLR=(1<<3);//clear SI flag SI=0
	while(SI==0);
	if(I2STAT==0X30){
		uart0_tx_string("Err:mr addr");
		goto exit;
}	

	/* send data & check ACK*/	
	I2DAT=data;//send data
	I2CONCLR=(1<<3);//clear SI flag SI=0
	while(SI==0);
	if(I2STAT==0X30){
		uart0_tx_string("Err:Data");
		goto exit;
	}
	//Generate stop condition/
	exit:
		I2CONSET=(1<<4);//STO=1
		I2CONCLR=(1<<3);//clear SI flag

}


 u8 i2c_byte_read_frame(u8 sa, u8 mr){
   u8 temp;

	I2CONSET=(1<<5);//STA=1
	I2CONCLR=(1<<3);//clear SI flag
	while(SI==0);
	I2CONCLR=(1<<5);//STA=0;
	if(I2STAT!=0X08){
		uart0_tx_string("Err:start");
		goto exit;
	}
	/* send SA+W & check ACK*/
	I2DAT=sa;//send SA+W
	I2CONCLR=(1<<3);//clear SI flag SI=0
	while(SI==0);
	if(I2STAT==0X20){
	uart0_tx_string("Err:SA+W");
	goto exit;
	}

	/* send m/r address & check ACK*/
	I2DAT=mr;//send m/r address
	I2CONCLR=(1<<3);//clear SI flag SI=0
	while(SI==0);
	if(I2STAT==0X30){
	uart0_tx_string("Err:mr addr");
	goto exit;

	}	
	//Generate restart condition/	
	I2CONSET=(1<<5);//STA=1
	I2CONCLR=(1<<3);//clear SI flag
	while(SI==0);
	I2CONCLR=(1<<5);//STA=0;
	if(I2STAT!=0X10){
	uart0_tx_string("Err:Restart");
		goto exit;
	}

	/* send SA+R & check ACK*/	
	I2DAT=sa|1;//send SA+R,for reading purpose 0th bit is set
	I2CONCLR=(1<<3);//clear SI flag SI
	while(SI==0);
	if(I2STAT==0X48){
	uart0_tx_string("Err:SA+R");
		goto exit;
	}

	   /*Data read and send No ack */
    I2CONCLR=(1<<3);//clear SI flag SI=0
	while(SI==0);//waiting for data to receive
	temp=I2DAT;
	exit:
		I2CONSET=(1<<4);//STO=1
		I2CONCLR=(1<<3);//clear SI flag

    /* return received data*/
    return temp;
  }
