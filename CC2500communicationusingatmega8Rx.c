#include<avr/io.h>
#include<util/delay.h>
#include <avr/interrupt.h>
 //#include"lcd.h"
 #include"cc2500.h"
 #include"usart.h"
//unsigned int x[255];
//volatile char buff[255];

void main()
 {
USART_Init(51);


_delay_ms(5);
SPI_init();
config_reg();
sei();

while(1)
{
//receive_string(x);
//WriteStringData(x);
UDR=receive();

}
}
/*
ISR(USART_RXC_vect)
{
	cli();

send(ReadData());
 
	sei();
}


*/
