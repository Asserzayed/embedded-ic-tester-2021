/*******************************************************
This program was created by the CodeWizardAVR V3.46a 
Automatic Program Generator
© Copyright 1998-2021 Pavel Haiduc, HP InfoTech S.R.L.
http://www.hpinfotech.ro

Project : IC74164
Version : 0.1a
Date    : 12/29/2021
Author  : Asser
Company : T17 Hardware Embedded
Comments: 

Chip type               : ATmega32
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*******************************************************/

#include <mega32.h>
#include <delay.h> //Delay introductions in programs
#include <stdint.h>

#define HIGH 1;
#define LOW 0;

// ----------------------------- IC 74164 ---------------------------------------- //
// Serial In Parallel Out 8-Bit Shift Register

// ATmega O/P's
#define SIPO_A      PORTC.0
#define SIPO_B      PORTC.1

#define SIPO_CLOCK  PORTA.0
#define SIPO_CLEAR  PORTA.1

// ATmega I/P's
#define SIPO_Q0     PINC.2
#define SIPO_Q1     PINC.3
#define SIPO_Q2     PINC.4
#define SIPO_Q3     PINC.5

#define SIPO_Q4     PINA.2
#define SIPO_Q5     PINA.3
#define SIPO_Q6     PINA.4
#define SIPO_Q7     PINA.5

//#define SIPO_PIPO_GND    PORTB.3
//#define SIPO_PIPO_VCC    PORTB.6

#define LED PORTD.7
// truth table 
/*
                    INPUTS              |        OUTPUTS            |
    ------------------------------------|---------------------------|
            |           |   SERIAL IN   |       |                   |
            |           |-------|-------|       |                   |
    -CLEAR  |   CLOCK   |   A   |   B   |   QA  |   QB ....... QH   |
    --------|-----------|-------|-------|-------|-------------------|
        0   |     X     |   X   |   X   |   0   |   0  ....... 0    |
    --------|-----------|-------|-------|-------|-------------------|
        1   |     0     |   X   |   X   |       NO  CHANGE          |
    --------|-----------|-------|-------|-------|-------------------|
        1   |     1     |   0   |   X   |   0   |   QAn ....... QGn |
    --------|-----------|-------|-------|-------|-------------------|
        1   |     1     |   X   |   0   |   0   |   QAn ....... QGn |
    --------|-----------|-------|-------|-------|-------------------|
        1   |     1     |   1   |   1   |   1   |   QAn ....... QGn |
    ----------------------------------------------------------------|
*/  
char i, j;
char check = 0;

char I74164(void)
{

    char D = 0b01010101;
    char X = 0b00000000;
    char temp=0b00000000;
    PIND=0b00000000;


    LED = LOW;
    // Give the CLK LOW    
    SIPO_CLOCK = LOW;
    // INPUTS A,B AND CLR` GIVEN HIGH
    SIPO_A = HIGH; 
    SIPO_B = HIGH; 
    SIPO_CLEAR = HIGH;
     
    
    // CHECK
    for(i=0;i<2;i++)
    {
        X=D;
        for(j=0;j<8;j++)
        { 
            temp = ( ( (X & 0b11111111) ^ 0b11111111) )% 2;
            SIPO_A = temp; 
            X = (X>>1);
            // Give a Rising Edge
            SIPO_CLOCK = HIGH;
            SIPO_CLOCK = LOW;
            delay_ms(500);
        }
        temp=((SIPO_Q7<<7)|(SIPO_Q6<<6)|(SIPO_Q5<<5)|(SIPO_Q4<<4)|(SIPO_Q3<<3)|(SIPO_Q2<<2)|(SIPO_Q1<<1)|(SIPO_Q0));
        if(temp == D){
            PIND=temp;
            check++;
            LED=HIGH;
            delay_ms(500);
            LED=LOW;
        }
        else{
            PIND=temp;
            delay_ms(500);
            PIND=0b00000000;
        }
        D = D^0b11111111;
        PORTD=0b00000000;
        delay_ms(500);
    }
    delay_ms(500);
    // APPLY CLR AND CHECK
    SIPO_CLEAR = LOW;
    SIPO_CLEAR = HIGH;
   if( ((SIPO_Q7 * (2^7) )+ (SIPO_Q6 * (2^6) )+ (SIPO_Q5 *(2^5))+ (SIPO_Q4*(2^4))+ (SIPO_Q3*(2^3))+(SIPO_Q2*(2^2))+ (SIPO_Q1*(2^1))+ (SIPO_Q0*(1))) == 0)
    {
       check++;
       LED=HIGH;
       delay_ms(500);
       LED=LOW;  
    }
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void main(void)
{
    LED=HIGH;
    delay_ms(500);
    LED=LOW;
    // Input/Output Ports initialization
    // Port A initialization
    // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=Out Bit0=Out 
    DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (1<<DDA1) | (1<<DDA0);
    // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=0 Bit0=0 
    PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);
    
    // Port C initialization
    // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=Out Bit0=Out 
    DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (1<<DDC1) | (1<<DDC0);
    // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=0 Bit0=0 
    PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

    // Port D initialization
    // Function: Bit7=Out Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
    DDRD=(1<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
    // State: Bit7=0 Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
    PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

    
    while(1)
    {
        I74164();
        if(check==3){
            delay_ms(500);
            LED=LOW;
        }
        delay_ms(500);
        check=0; 
    } 
}
