#include <stdbool.h>

void USART_Init( unsigned int ubrr);
char ReadData( void );
void WriteData(char data);
void ReadStringData(char *str);
void WriteStringData(char *strData);
void WriteStr(char *str,uint8_t s);
void ReadStr(char *str,uint8_t s);
void ReadInput(char *str); 