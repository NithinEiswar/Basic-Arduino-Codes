#define F_CPU  16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
//Author Name:NITHIN EISWAR.V
//Domain:EMBEDDED AND ELECTRONICS
//Functions:usart_init(),usart_write(),ADC_START

//Function Name:usart_init
//Description:configure USART at 9600bps, Asynchronous Mode, Normal Speed, No parity, 1 Stop bit and 8 bit of data.
//Example Call:usart_init();
void usart_init()
{
  UCSR0A = 0X00;
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
  UBRR0 = 103;
}
//Function Name:usart_write
//Description:print character
//Example Call:usart_write('a');
void usart_write(int data)
{
  while ( !(UCSR0A & (1 << UDRE0))) { }
  UDR0 = data;
}
//Function Name:send_string
//Description:print string
//Example Call:send_string("moon");
void send_string(char s[])
{
  int i = 0;

  while (s[i] != 0x00)
  {
    usart_write(s[i]);
    i++;
  }
}

//Function Name:getDecimal
//Description:function to extract decimal part of float
//Example call:getDecimal(12.5);
long getDecimal(float val)
{
  int intPart = int(val);
  long decPart = 1000 * (val - intPart); //I am multiplying by 1000 assuming that the float values will have a maximum of 3 decimal places.
  //Change to match the number of decimal places you need
  if (decPart > 0)return (decPart);       //return the decimal part of float number if it is available
  else if (decPart < 0)return ((-1) * decPart); //if negative, multiply by -1
  else if (decPart = 0)return (00);       //return 0 if decimal part of float number is not available
}


int main(void)
{ float v1 = 0.0;
  float v2 = 0.0;
  int val = 0;
  int n = 0; //to print values after certain readings to improve accuracy
  int m = 0;//to print values after certain readings to improve accuracy

  usart_init();
  ADCSRA |= 1 << ADEN | 1 << ADATE;
  ADCSRA |= 1 << ADPS0 | 1 << ADPS1;
  //setting the prescaler as 8

  ADMUX |= 1 << REFS0;
  ADCSRA |= 1 << ADSC ;
  //conversion is starting
  int x = 0, y = 0;

  while (1)
  {char charVal[6];                      //initialise character array to store the values
   char charVal1[6];                      //initialise character array to store the values
    ADMUX |= 1 << MUX1 | 1 << MUX0;     //changing channel
    while (ADCSRA & (1 << ADIF) == 0);
    x = ADC;
    v1 = (x * 5) / 1023;
    if (v1 < 0.09) //condition
    {
      v1 = 0.00; //statement to quash undesired reading
    }
    n++;
    if (n < 2)
    { send_string("");
    }

    else {
      send_string("VOLTAGE1=");
      String stringVal = "";
      stringVal += String(int(v1)) + "." + String(getDecimal(v1)); //combining both whole and decimal part in string with a fullstop between them
      
      for (uint8_t i = 0; i < sizeof(charVal); i++) //passing the value of the string to the character array
      {
        charVal[i] = stringVal[i];
      }
      for (uint8_t i = 0; i < sizeof(charVal); i++) //display character array
      {
        usart_write(charVal[i]);
      }
      usart_write('\n');
    }      _delay_ms(1000); //for maintaining the speed of the output in serial monitor

    ADMUX ^= 1 << MUX1;
    // changing channel
    while (ADCSRA & (1 << ADIF) == 0);
    y = ADC;
    v2 = (y * 5) / 1023;
    if (v2 < 0.09) //condition
    {
      v2 = 0.00; //statement to quash undesired reading
    }
    m++;
    if (m < 2)
    { send_string("");
    }

    else {
      send_string("VOLTAGE2=");
      String stringVal1 = "";
      stringVal1 += String(int(v2)) + "." + String(getDecimal(v2)); //combining both whole and decimal part in string with a fullstop between them
      for (uint8_t i = 0; i < sizeof(charVal1); i++) //passing the value of the string to the character array
      {
        charVal1[i] = stringVal1[i];
      }
      for (uint8_t i = 0; i < sizeof(charVal1); i++) //display character array
      {
        usart_write(charVal1[i]);
      }
      usart_write('\n');
    }      _delay_ms(1000); //for maintaining the speed of the output in serial monitor




    DDRB |= (1 << PORTB1); // Set OC1A as output

    TCCR1A |= (1 << COM1A1); // Clear OC1A/OC1B on Compare Match (Set output to low level).
    TCCR1A |= (1 << WGM11) | (1 << WGM10); // Fast PWM Mode 15 TOP = OCR1A
    TCCR1B |= (1 << WGM13) | (1 << WGM12); // Fast PWM Mode 15 TOP = OCR1A
    TCCR1B |= (1 << CS12) | (1 << CS10); // clkI/O/1024 (From prescaler)
    TIMSK1 |= (1 << OCIE0A) | (1 << OCIE0B); // Output Compare A and Compare B Match Interrupt Enable

    OCR1A = 1000; // Freq OC1A = clk / prescale * (1 + TOP)
    OCR1B = 750; // Duty Cycle

    sei(); // Enable global interrupts

    while (1)
    {
    }
  

  ISR(TIMER1_COMPA_vect) {

  }

  ISR(TIMER1_COMPB_vect) {

  }
  }
} 
