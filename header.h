#include<LPC21XX.H>
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short int u16;

// delay prototypes
extern void delay_ms(u32 ms);
extern void delay_sec(u32 sec);
// lcd_driver
// lcd_driver control pins
#define RS (1<<17)
#define RW (1<<18)
#define EN (1<<19)
extern void lcd_init(void);
extern void lcd_cmd(u8);
extern void lcd_data(u8);
extern void lcd_string(u8 *s);
extern void lcd_integer(u32 num);
extern void lcd_float(float);
extern void lcd_hex(u32 num);
// uart0_driver
#define THRE ((U0LSR>>5)&1)
#define RDR ((U0LSR)&1)
extern void uart0_init(u32 baud);
extern void uart0_tx(u8 data);
extern u8 uart0_rx(void);
extern void uart0_tx_string(u8 *s);
extern void uart0_rx_string(u8 *s,u32 n);
extern void uart0_float(float f);
extern void uart0_int(u32 num);
extern u32 pal(u8 *s);
extern u32 cmp(u8 *s1,u8 *s2);
extern void uart0_tx_hex(u32 num);
// spi0_driver
extern void spi0_init(void);
extern u8 spi0(u8 data);
// mcp3204_driver
extern u32 mcp3204_read(u8 ch_num);
// adc_driver

extern void adc_init(void);
extern u32 adc_read(u8 ch_num);



// i2c driver
extern void i2c_init(void);
extern u8 i2c_byte_read_frame(u8 sa,u8 mr);
extern void i2c_byte_write_frame(u8 sa,u8 mr,u8 data);
extern u8 i2c_detect_frame(u8 sa);
extern void text(u32 n);
