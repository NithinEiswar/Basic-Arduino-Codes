#include<avr/io.h>
#include<util/delay.h>
void usart_init() 
{
  UCSR0A = 0X00;
  UCSR0B = (1<<RXEN0) | (1<<TXEN0);
  UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
  UBRR0 = 103;
}
char usart_read()
 {
  while( !(UCSR0A & (1<<RXC0))) { }
  return UDR0;
}
void usart_write(char data) 
{
  while( !(UCSR0A & (1<<UDRE0))) { }
  UDR0=data;
}
void usart_puts( char *str ) 
{ 

    while (*str) { 
        usart_write(*str); 
        str++; 
    } 
}

int main()
{
char ch;
int data=0;
usart_init();
DDRD|=0b01000000; 
TCCR0A|=(1<<COM0A1)|(1<<WGM01)|(1<<WGM00);
// non inverter mode and fast pwm
TCCR0B|=(1<<CS00);
//prescaler1
while(1)
  {
    ch=usart_read();
    if(ch=='a')
    {
     data+=20;
     if(data>255)
     {
      data=255;
      usart_puts( "MAXIMUM BRIGHTNESS\r\n" );
     }
     OCR0A=data;
    }
    if(ch=='b')
    { 
     data-=20;
     if(data<0)
     {
      data=0;
      usart_puts( "MINIMUM BRIGHTNESS\r\n" );
     }
     OCR0A=data;
    }
  }
}
