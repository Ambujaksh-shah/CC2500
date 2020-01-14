#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include"cc2500.h"


#include"usart.h"


void main()
{
 
 USART_Init(103);

_delay_ms(5);
SPI_init();
config_reg();

sei();
while(1)
{


UDR=receive();


}
}

ISR(USART_RXC_vect)
{
	cli();

send(ReadData());
  	sei();
}
