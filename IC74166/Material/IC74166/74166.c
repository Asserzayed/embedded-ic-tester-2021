/*******************************************************
This program was created by the CodeWizardAVR V3.46a 
Automatic Program Generator
© Copyright 1998-2021 Pavel Haiduc, HP InfoTech S.R.L.
http://www.hpinfotech.ro

Project : IC 74166
Version : 
Date    : 1/1/2022
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
#include <delay.h> //Delay introductions in programs
#include <stdint.h>

//8-Bit Parallel-In/Serial-
//Out Shift Register

//ATMega I/P's
#define PISO_SO PINA.4

//ATMega O/P's
#define PISO_SI PORTC.0
#define PISO_D0 PORTC.1
#define PISO_D1 PORTC.2
#define PISO_D2 PORTC.3
#define PISO_D3 PORTC.4

#define PISO_D4 PORTA.1
#define PISO_D5 PORTA.2
#define PISO_D6 PORTA.3
#define PISO_D7 PORTA.5

#define PISO_CLK_INH    PORTC.5
#define PISO_CLK        PORTC.6

#define PISO_CLR_   PORTA.0
#define PISO_LOAD_  PORTA.6



#define LED PORTD.7
#define HIGH 1
#define LOW 0

char i;
char j;
void IC74166(void){

    char D = 0b01010101;
    char X = 0;
    char temp = 0;
    
    PISO_CLK_INH = LOW;
    PISO_CLK = LOW;
    
    PISO_CLR_ = HIGH;
    PISO_LOAD_ = HIGH;
    for(i=0;i<2;i++){
        X = D;
        for(j=0;j<8;j++){
            //SERIAL IN TRIAL
            temp = (X & 0b11111111) % 2;
            PISO_SI = temp;
            X = (X>>1);
            PISO_CLK = HIGH;
            PISO_CLK = LOW;
            delay_ms(200);
        }
        X = 0;
        for(j=0;j<8;j++){
            //CHECK SERIAL-IN OUTPUT
            X = (X>>1)|((PISO_SO)<<7);
            PISO_CLK = HIGH;
            PISO_CLK = LOW;
            delay_ms(200);
        }
        if(X == D){
            LED=HIGH;
            delay_ms(500);
            LED=LOW;
        }
        D = D^0b11111111;
        delay_ms(200);
    }
    delay_ms(1000);
    for(i=0;i<2;i++){
        PISO_LOAD_ = LOW;
        //PARALLEL-IN OUTPUT TEST
        PISO_D0 = ((D&0b10000000)>>7);
        PISO_D1 = ((D&0b01000000)>>6);
        PISO_D2 = ((D&0b00100000)>>5);
        PISO_D3 = ((D&0b00010000)>>4);
        PISO_D4 = ((D&0b00001000)>>3);
        PISO_D5 = ((D&0b00000100)>>2);
        PISO_D6 = ((D&0b10000010)>>1);
        PISO_D7 = (D&0b00000001);
        PISO_CLK = HIGH;
        PISO_CLK = LOW;
        PISO_LOAD_ = HIGH;
        X=0;
        for(j=0;j<8;j++){
            //PARALLEL-IN OUTPUT CHECK
            X = (X>>1)|((PISO_SO<<7));
            PISO_CLK = HIGH;
            PISO_CLK = LOW;
            delay_ms(500);
        }
        if(X==D){
            LED = HIGH;
            delay_ms(500);
            LED = LOW;
        }
        D = D^0b111111111;
        delay_ms(200);
    }
    
    PISO_CLR_ = LOW;
    delay_ms(1000);
    PISO_CLR_ = HIGH;
    
    X = 0;
    for(j=0;j<8;j++){
        //CLEAR CHECK
        X = (X>>1)|((PISO_SO)<<7);
        PISO_CLK = HIGH;
        PISO_CLK = LOW;
        delay_ms(500);
    }
    if(X == 0){
        LED = HIGH;
        delay_ms(500);
        LED = LOW;
    }
    return;

}


// Declare your global variables here

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=Out Bit5=Out Bit4=In Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRA=(0<<DDA7) | (1<<DDA6) | (1<<DDA5) | (0<<DDA4) | (1<<DDA3) | (1<<DDA2) | (1<<DDA1) | (1<<DDA0);
// State: Bit7=T Bit6=0 Bit5=0 Bit4=T Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit7=In Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRC=(0<<DDC7) | (1<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
// State: Bit7=T Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=Out Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(1<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=0 Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);


while (1)
      {
      // Place your code here
      IC74166();
      delay_ms(1000);
      }
}
