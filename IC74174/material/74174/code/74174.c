/*******************************************************
This program was created by the CodeWizardAVR V3.46a 
Automatic Program Generator
? Copyright 1998-2021 Pavel Haiduc, HP InfoTech S.R.L.
http://www.hpinfotech.ro

Project : IC 74175
Version : 0.1a
Date    : 12/31/2021
Author  : T17
Company : 
Comments: 


Chip type               : ATmega32
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*******************************************************/
#include <mega32.h>
#include <delay.h>
#include <stdint.h>

#define HIGH 1
#define LOW 0
      
//ATMEGA I/P's
#define Pin_1Q      PINC.1
#define Pin_2Q      PINC.4
#define Pin_3Q      PINC.6
#define Pin_4Q      PINA.1
#define Pin_5Q      PINA.3
#define Pin_6Q      PINA.6


//ATMEGA O/P'S
#define Pin_1D      PORTC.2
#define Pin_2D      PORTC.3
#define Pin_3D      PORTC.5
#define Pin_4D      PORTA.2
#define Pin_5D      PORTA.4
#define Pin_6D      PORTA.5


#define Pin_CLK     PORTA.0
#define Pin_CLR     PORTC.0

//Indication
#define LED         PORTD.7
// Declare your global variables here
/*
    IC PINS

        CLR_ [-------] VCC
        1Q  [       ] 6Q
        1D  [       ] 6D
        2D  [       ] 5D
        2Q  [       ] 5Q 
        3D  [       ] 4D
        3Q  [       ] 4Q
        GND [-------] CLK 
        
        PINS[1 3 4 6 9 11 13 14] : INPUT
        PIN[2 5 7 10 12 15] : OUTPUT
        PINS[8] : GND
        PIN[16] : VCC
        PIN[9]  : LOW
        PIN[1] : HIGH

*/

char i;
int IC74174(void){
    int found = 0;
    char D=0b00010101;
    char temp=0b00000000;
    Pin_CLK = LOW;
    Pin_CLR = HIGH;
    
    
    for (i = 0; i < 2 ; i++)
    {
        temp = ((D&0b00100000)>>5);
        Pin_6D = temp; 
        temp = ((D&0b00010000)>>4);
        Pin_5D = temp;         
        temp = ((D&0b00001000)>>3);
        Pin_4D = temp; 
        temp = ((D&0b00000100)>>2);
        Pin_3D = temp;
        temp = ((D&0b00000010)>>1);
        Pin_2D = temp;
        temp = (D&0b00000001);
        Pin_1D = temp;
        
        Pin_CLK = 1;
        Pin_CLK = 0;
        delay_ms(100);
        Pin_6D = 0;
        Pin_5D = 0;
        Pin_4D = 0;
        Pin_3D = 0;
        Pin_2D = 0;
        Pin_1D = 0;
        
        if((Pin_6Q ==((D&0b00100000)>>5)) && (Pin_5Q == ((D&0b00010000)>>4)) 
            && (Pin_4Q ==((D&0b00001000)>>3)) && (Pin_3Q==((D&0b00000100)>>2))
            && (Pin_2Q==((D&0b00000010)>>1)) && (Pin_1Q==(D&0b00000001)))
        {
            found++;
        }
        
        D=D^0b00111111;
        delay_ms(100);
        
    }
  return found;
  
    
}

void main(void)
{
  int x;
    
// Function: Bit7=In Bit6=In Bit5=Out Bit4=Out Bit3=In Bit2=Out Bit1=In Bit0=Out 
DDRA=(0<<DDA7) | (0<<DDA6) | (1<<DDA5) | (1<<DDA4) | (0<<DDA3) | (1<<DDA2) | (0<<DDA1) | (1<<DDA0);
// State: Bit7=T Bit6=T Bit5=0 Bit4=0 Bit3=T Bit2=0 Bit1=T Bit0=0 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit7=In Bit6=In Bit5=Out Bit4=In Bit3=Out Bit2=Out Bit1=In Bit0=Out 
DDRC=(0<<DDC7) | (0<<DDC6) | (1<<DDC5) | (0<<DDC4) | (1<<DDC3) | (1<<DDC2) | (0<<DDC1) | (1<<DDC0);
// State: Bit7=T Bit6=T Bit5=0 Bit4=T Bit3=0 Bit2=0 Bit1=T Bit0=0 
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=Out Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(1<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=0 Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

   
   //while (1)
  // {
       x = IC74174();
       if (x == 2)
       {
         LED = HIGH;
         delay_ms(100);
         LED = LOW; 
         LED = HIGH;
         delay_ms(100);
         LED = LOW;
       }  
   //}
   

}