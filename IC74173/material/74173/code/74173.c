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


#define Pin_0Q      PINC.2
#define Pin_1Q      PINC.3
#define Pin_2Q      PINC.4
#define Pin_3Q      PINC.5





//ATMEGA O/P'S

#define Pin_0D      PORTA.5
#define Pin_1D      PORTA.4
#define Pin_2D      PORTA.3
#define Pin_3D      PORTA.2





#define Pin_OE1     PORTC.0
#define Pin_OE2     PORTC.1
#define Pin_DE1     PORTA.0
#define Pin_DE2     PORTA.1
#define Pin_REST    PORTA.6
#define Pin_CLK     PORTC.6

// Indication
#define LED         PORTD.7
// Declare your global variables here
/*
    IC PINS

        OE1 [-------] VCC
        OE2 [       ] REST
        0Q  [       ] 0D
        1Q  [       ] 1D
        2Q  [       ] 2D 
        3Q  [       ] 3D
        CLK [       ] DE2
        GND [-------] DE1 
        
        PINS[1 2 7  9 10 11 12 13 14 15 ] : INPUT
        PIN[3 4 5 6] : OUTPUT
        PINS[8] : GND
        PIN[16] : VCC
        PIN[7 15]  : LOW
        PIN[1 2 9 10] : HIGH

*/

char i;
void IC74175(void){
    int found;
    char D=0b00000101;
    char temp=0b00000000;
    
    Pin_CLK  = LOW;
    Pin_REST = LOW;
    
    Pin_OE1 = HIGH;
    Pin_OE2 = HIGH;
    
    Pin_DE1 = HIGH;
    Pin_DE2 = HIGH;
    
    for (i = 0; i < 2 ; i++)
    {
        Pin_DE1 = LOW;
        Pin_DE2 = LOW;
                 
        temp = ((D&0b00001000)>>3);
        Pin_3D = temp; 
        temp = ((D&0b00000100)>>2);
        Pin_2D = temp;
        temp = ((D&0b00000010)>>1);
        Pin_1D = temp;
        temp = (D&0b00000001);
        Pin_0D = temp;
        
        Pin_CLK = 1;
        Pin_CLK = 0;
        delay_ms(100);
        
        Pin_3D = 0;
        Pin_2D = 0;
        Pin_1D = 0;
        Pin_0D = 0;
        
        Pin_DE1 = HIGH;
        Pin_DE2 = HIGH;
        
        Pin_OE1 = LOW;
        Pin_OE2 = LOW;
        
        if((Pin_3Q==((D&0b00001000)>>3)) && (Pin_2Q==((D&0b00000100)>>2)) 
            && (Pin_1Q==((D&0b00000010)>>1)) && (Pin_0Q==(D&0b00000001)))
        {
           found++; 
            
        }
        
        Pin_OE1 = HIGH;
        Pin_OE2 = HIGH;
        
        D=D^0b00001111;
        delay_ms(100);
        
    }
    
    Pin_REST = HIGH;
    Pin_REST = LOW;
                    
    Pin_OE1 = LOW;
    Pin_OE2 = LOW;
    
    if((Pin_3Q == 0x00) && (Pin_2Q == 0x00) 
        && (Pin_1Q == 0x00) && (Pin_0Q == 0x00))
    {
        found++; 
    }
    
    Pin_OE1 = HIGH;
    Pin_OE2 = HIGH;
    
    /* SWITCH THE INPUT Q TO BE OUTPUT*/
    DDRC.2 = 1;
    DDRC.3 = 1;
    DDRC.4 = 1;
    DDRC.5 = 1;
    
    /* WRITE LOW TO THESE PINS */
    PORTC.2 = 0;
    PORTC.3 = 0;
    PORTC.4 = 0;
    PORTC.5 = 0;
    
    if((Pin_3Q == 0x00) && (Pin_2Q == 0x00) 
        && (Pin_1Q == 0x00) && (Pin_0Q == 0x00))
    {
       found++;  
        
    }
    
    /* WRITE HIGH TO THESE PINS */
    PORTC.2 = 1;
    PORTC.3 = 1;
    PORTC.4 = 1;
    PORTC.5 = 1;
    
    if((Pin_3Q == 0x01) && (Pin_2Q == 0x01) 
        && (Pin_1Q == 0x01) && (Pin_0Q == 0x01))
    {
        found++; 
    }
    
    /* RESWITCH Q TO BE INPUT AGAIN */
    DDRC.2 = 0;
    DDRC.3 = 0;
    DDRC.4 = 0;
    DDRA.0 = 0;    
  return found;
  
    
}

void main(void)
{
    int x;
    
// Function: Bit7=In Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRA=(0<<DDA7) | (1<<DDA6) | (1<<DDA5) | (1<<DDA4) | (1<<DDA3) | (1<<DDA2) | (1<<DDA1) | (1<<DDA0);
// State: Bit7=T Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit7=In Bit6=Out Bit5=In Bit4=In Bit3=In Bit2=In Bit1=Out Bit0=Out 
DDRC=(0<<DDC7) | (1<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (1<<DDC1) | (1<<DDC0);
// State: Bit7=T Bit6=0 Bit5=T Bit4=T Bit3=T Bit2=T Bit1=0 Bit0=0 
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=Out Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(1<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=0 Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);



    x = IC74175();
    if (x == 5)
    {
        LED=HIGH;
        delay_ms(100);
        LED=LOW;
        delay_ms(100); 
    } 
   
  
        
         
    
}