#include <avr/io.h>
#include "usart.h"



void USART_Init( unsigned int ubrr)
{
/* Set baud rate */
UBRRH = (unsigned char)(ubrr>>8);
UBRRL = (unsigned char)ubrr;

/* Enable receiver and transmitter */
UCSRB=(1<<RXEN)|(1<<TXEN)|(1<<RXCIE);//|(1<<TXCIE);
/* Set frame format: 8data, 1stop bit */
UCSRC = (1<<URSEL)|(3<<UCSZ0);

}

char ReadData( void )
{
/* Wait for data to be received */
while ( !(UCSRA & (1<<RXC)) )
;
/* Get and return received data from buffer */
return UDR;
}


void WriteData(char data)
{
    //Wait For Transmitter to become ready
    while(!(UCSRA & (1<<UDRE)));

    //Now write
    UDR=data;
}


void ReadStringData(char *str){
    
        char c;
        do{
            c=ReadData();
            *str=c;
            str++;
        }
        while(c!='\0');
        

    return;
    
}

void WriteStringData(char *strData)
{
    while(*strData!='\0')
    {
        WriteData(*strData);
        strData++;
    }
    //WriteData('\0');
    return;

}



void SendInt(uint16_t nbr)
{
    uint8_t array[4];
    uint8_t d;
    uint16_t number= nbr;

    for (int i = 3; i >= 0; i--) {
        array[i] = (number % 10) + 48;
        d = (number % 10) + 48;
        number /= 10;
    }
    
    WriteStringData(array);
}

void WriteStr(char *str,uint8_t s){
    
        char c;
        for (uint8_t i=0;i<s;i++)
        {
            WriteData(*str);
            str++;
        }
        WriteData('\n');
        
    return;
    
}

void ReadStr(char *str,uint8_t s){
    
        char c;
        for (uint8_t i=0;i<s;i++)
        {
            c=ReadData();
            *str=c;
            str++;
        }
        *str='\0';
        
    return;
    
}



void ReadInput(char *str)
{
    char c;
        do{
            c=ReadData();
            *str=c;
            str++;
        }
        while(c!='\n');
        
    //c='\0';
    return;
}
