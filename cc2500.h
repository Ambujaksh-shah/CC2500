 #include<avr/io.h>
#include<util/delay.h>

#define CC_IOCFG2_value         0x2F
#define CC_IOCFG1_value         0x2E
#define CC_IOCFG0D_value        0x06
#define CC_FIFOTHR_value        0x07
#define CC_SYNC1_value          0xD3
#define CC_SYNC0_value          0x91
#define CC_PKTLEN_value         0x03
#define CC_PKTCTRL1_value       0x84
#define CC_PKTCTRL0_value       0x04
#define CC_ADDR_value           0x00
#define CC_CHANNR_value         0x00
#define CC_FSCTRL1_value        0x09
#define CC_FSCTRL0_value        0x00
#define CC_FREQ2_value          0x5D
#define CC_FREQ1_value          0xD8
#define CC_FREQ0_value          0x9D
#define CC_MDMCFG4_value        0x2D
#define CC_MDMCFG3_value        0x3B
#define CC_MDMCFG2_value        0x73
#define CC_MDMCFG1_value        0x23
#define CC_MDMCFG0_value        0x3B
#define CC_DEVIATN_value        0x01
#define CC_MCSM2_value          0x07
#define CC_MCSM1_value          0x30
#define CC_MCSM0_value          0x18
#define CC_FOCCFG_value         0x1D
#define CC_BSCFG_value          0x1C
#define CC_AGCCTRL2_value       0xC7
#define CC_AGCCTRL1_value       0x00
#define CC_AGCCTRL0_value       0xB2
#define CC_WOREVT1_value        0x87
#define CC_WOREVT0_value        0x6B
#define CC_WORCTRL_value        0xF8
#define CC_FREND1_value         0xB6
#define CC_FREND0_value         0x10
#define CC_FSCAL3_value         0xEA
#define CC_FSCAL2_value         0x0A
#define CC_FSCAL1_value         0x00
#define CC_FSCAL0_value         0x11
#define CC_RCCTRL1_value        0x41
#define CC_RCCTRL0_value        0x00
#define CC_FSTEST_value         0x59
#define CC_PTEST_value          0x7F
#define CC_AGCTEST_value        0x3F
#define CC_TEST2_value          0x88
#define CC_TEST1_value          0x31
#define CC_TEST0_value          0x0B
#define SRES                    0x30
#define SFSTXON                 0x31
#define SXOFF                   0x32
#define SCAL                    0x33
#define SRX                     0x34
#define STX                     0x35
#define SIDLE                   0x36
#define SAFC                    0x37
#define SWOR                    0x38
#define SPWD                    0x39
#define SFRX                    0x3A
#define SFTX                    0x3B
#define SWORRST                 0x3C
#define SNOP                    0x3D

const unsigned char CC_rfSettings[0x2F]=
{
CC_IOCFG2_value,
CC_IOCFG1_value,
CC_IOCFG0D_value,
CC_FIFOTHR_value,
CC_SYNC1_value,
CC_SYNC0_value,
CC_PKTLEN_value,
CC_PKTCTRL1_value,
CC_PKTCTRL0_value,
CC_ADDR_value,
CC_CHANNR_value,
CC_FSCTRL1_value,
CC_FSCTRL0_value,
CC_FREQ2_value,
CC_FREQ1_value,
CC_FREQ0_value,
CC_MDMCFG4_value,
CC_MDMCFG3_value,
CC_MDMCFG2_value,
CC_MDMCFG1_value,
CC_MDMCFG0_value,
CC_DEVIATN_value,
CC_MCSM2_value,
CC_MCSM1_value,
CC_MCSM0_value,
CC_FOCCFG_value,
CC_BSCFG_value,
CC_AGCCTRL2_value,
CC_AGCCTRL1_value,
CC_AGCCTRL0_value,
CC_WOREVT1_value,
CC_WOREVT0_value,
CC_WORCTRL_value,
CC_FREND1_value,
CC_FREND0_value,
CC_FSCAL3_value,
CC_FSCAL2_value,
CC_FSCAL1_value,
CC_FSCAL0_value,
CC_RCCTRL1_value,
CC_RCCTRL0_value,
CC_FSTEST_value,
CC_PTEST_value,
CC_AGCTEST_value,
CC_TEST2_value,
CC_TEST1_value,
CC_TEST0_value
};

#define transmmiter
#define receiver
 
#define CSn 0
#define MOSI 3
#define SCLK 5
#define SS 2

void SPI_init(); //initialize spi interface of atmega8
unsigned char SPI_TX(unsigned char); //transmit one byte from avr to CC

void config_reg();//creating array for assigned register values

unsigned char p,q,r,t;
 
void send(char data)  // send data in CC wirelessly
{
command(SFTX);      //flush tx FIFO
command(SIDLE);    //turn CC2500 into idle mode
 
command(SCAL);
PORTC=(0<<CSn);
while(bit_is_set(PINB,4));
PORTD|=(1<<4);
SPI_TX(0x7F);    // tx FIFO address in burst mode
SPI_TX(data); // data byte1
SPI_TX(data); // data byte2
SPI_TX(data);//data byte3
PORTC|=(1<<CSn);
command(STX);  //command to send data in tx FIFO wirelessly
_delay_ms(5);
PORTD&=~(1<<4);
}
void send_string(char data[])
{
	
	while(*data!='\0') 
	{
		send(*data++);
	}
}

 
 int receive()
{
command(SRX); // command to receive data wirelessly
command(SRX);
while(bit_is_clear(PINC,1)); // check GD0pin of CC2500
PORTC=(0<<CSn);
PORTD|=(1<<3);//LED 1
while(bit_is_set(PINB,PB4));
SPI_TX(0xFF); // rx FIFO address burst mode
p=SPI_TX(0x00); // data byte1
q=SPI_TX(0x00);// data byte2
r=SPI_TX(0x00);// data byte3
PORTC|=(1<<CSn);
command(SFRX); // flush receiver FIFO
command(SFRX); // flush receiver FIFO
command(SIDLE); // turn CC2500 into idle mode
command(SCAL);
//_delay_ms(10);
PORTD&=~(1<<3);//LED 2
return p;
return q;
return r;


}
void receive_string(char data[])
{
	
	while(*data!='\0') 
	{
		receive(*data++);
	}
}

void config_reg()//creating array for assigned register values
{
PORTC|=(1<<CSn);
for(int i=0x00;i<0x2F;i++)   // configure registers of CC2500
{
PORTC=(0<<CSn);
while(bit_is_set(PINB,4));
SPI_TX(i); //address byte
SPI_TX(CC_rfSettings[i]);// data byte
PORTC|=(1<<CSn);
}
}
void command(unsigned char a) // give commands to CC
{
PORTC=(0<<CSn);
while(bit_is_set(PINB,4));
SPI_TX(a);
PORTC|=(1<<CSn);
}
void SPI_init() //SPI initialization in atmega8
{

DDRD=(1<<3)|(1<<4);

DDRC|=(1<<CSn)|(0<<1);
DDRB=(1<<MOSI)|(1<<SCLK)|(1<<SS); // set MISO as output pin, rest as input
SPCR=(1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<SPR1); // Enable SPI
//SPSR=(1<<SPI2X)|(1<<WCOL);
}
unsigned char SPI_TX(unsigned char a)  // atmega 8 send one byte to CC and receive one byte from CC
{
SPDR=a;
while(!(SPSR &(1<<SPIF))); //wait until SPIF get high
return SPDR;
}
