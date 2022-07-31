/*******************************************************
This program was created by the CodeWizardAVR V3.46a 
Automatic Program Generator
� Copyright 1998-2021 Pavel Haiduc, HP InfoTech S.R.L.
http://www.hpinfotech.ro

Project : ic_tester
Version : 
Date    : 12/27/2021
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
#include <io.h>
#include <stdint.h>
#include <stdio.h>

#define HIGH 1;
#define LOW 0;
char i, j;
char check = 0;

// ----------------------------- IC 74164 ---------------------------------------- //
// Serial In Parallel Out 8-Bit Shift Register

// ATmega O/P's
#define IC_74164_A      PORTC.0
#define IC_74164_B      PORTC.1
#define IC_74164_GND    PORTC.6

#define IC_74164_CLOCK  PORTA.0
#define IC_74164_CLEAR  PORTA.1

// ATmega I/P's
#define IC_74164_Q0     PINC.2
#define IC_74164_Q1     PINC.3
#define IC_74164_Q2     PINC.4
#define IC_74164_Q3     PINC.5

#define IC_74164_Q4     PINA.2
#define IC_74164_Q5     PINA.3
#define IC_74164_Q6     PINA.4
#define IC_74164_Q7     PINA.5

/*
    IC PINS

        A   [-------] VCC
        B   [       ] Q7
        Q0  [       ] Q6
        Q1  [       ] Q5
        Q2  [       ] Q4 
        Q3  [       ] CLR-
        GND [-------] CLK 

*/ 
/*
    Truth table
    
                    INPUTS              |        OUTPUTS            |
    ------------------------------------|---------------------------|
            |           |   SERIAL IN   |       |                   |
            |           |-------|-------|       |                   |
    -CLEAR  |   CLOCK   |   A   |   B   |   QA  |   QB ....... QH   |
    --------|-----------|-------|-------|-------|-------------------|
        L   |     X     |   X   |   X   |   L   |   L  ....... L    |
    --------|-----------|-------|-------|-------|-------------------|
        H   |     L     |   X   |   X   |       NO  CHANGE          |
    --------|-----------|-------|-------|-------|-------------------|
        H   |     ^     |   H   |   H   |   H   |   QAn ....... QGn |
    --------|-----------|-------|-------|-------|-------------------|
        H   |     ^     |   L   |   X   |   L   |   QAn ....... QGn |
    --------|-----------|-------|-------|-------|-------------------|
        H   |     ^     |   X   |   L   |   L   |   QAn ....... QGn |
    ----------------------------------------------------------------|
*/  
char ic_74164(void)
{
    char D = 0b01010101;
    char X = 0b00000000;
    char temp=0b00000000;

    // Input/Output Ports initialization
    // Port A initialization
    // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=Out Bit0=Out 
    DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (1<<DDA1) | (1<<DDA0);
    // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=0 Bit0=0 
    PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);
    
    // Port C initialization
    // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=Out Bit0=Out 
    DDRC=(0<<DDC7) | (1<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (1<<DDC1) | (1<<DDC0);
    // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=0 Bit0=0 
    PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

    // Port D initialization
    // Function: Bit7=Out Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
    DDRD=(1<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
    // State: Bit7=0 Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
    PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

    check = 0;
    PIND=0b00000000;

    // Give the CLK LOW    
    IC_74164_CLOCK = LOW;
    // INPUTS A,B AND CLR` GIVEN HIGH
    IC_74164_A = HIGH; 
    IC_74164_B = HIGH; 
    IC_74164_CLEAR = HIGH;
     
    // CHECK
    for(i=0;i<2;i++)
    {
        X=D;
        for(j=0;j<8;j++)
        { 
            temp = ( ( (X & 0b11111111) ^ 0b11111111) )% 2;
            IC_74164_A = temp; 
            X = (X>>1);
            // Give a Rising Edge
            IC_74164_CLOCK = HIGH;
            IC_74164_CLOCK = LOW;
            delay_ms(500);
        }
        temp=((IC_74164_Q7<<7)|(IC_74164_Q6<<6)|(IC_74164_Q5<<5)|(IC_74164_Q4<<4)|(IC_74164_Q3<<3)|(IC_74164_Q2<<2)|(IC_74164_Q1<<1)|(IC_74164_Q0));
        if(temp == D){
            PIND=temp;
            check++;
        }
        else{
            PIND=temp;
            delay_ms(1000);
            PIND=0b00000000;
        }
        D = D^0b11111111;
        PORTD=0b00000000;
        delay_ms(2000);
    }
    delay_ms(500);
    // APPLY CLR AND CHECK
    IC_74164_CLEAR = LOW;
    IC_74164_CLEAR = HIGH;
    if( ((IC_74164_Q7 * (2^7) )+ (IC_74164_Q6 * (2^6) )+ (IC_74164_Q5 *(2^5))+ (IC_74164_Q4*(2^4))+ (IC_74164_Q3*(2^3))+(IC_74164_Q2*(2^2))+ (IC_74164_Q1*(2^1))+ (IC_74164_Q0*(1))) == 0)
    {
       check++;
    }
    if(check==3)
    {
        return 1;
    }      
    return 0;
}
// ------------------------------------------------------------------------------- //

// ----------------------------- IC 74165 ---------------------------------------- //
//Atmega I/P's
#define IC_74165_Q PINA.0
#define IC_74165_Q_ PINC.6

//Atmega O/P's
#define IC_74165_LOAD_ PORTC.0
#define IC_74165_CLK   PORTC.1

#define IC_74165_D4    PORTC.2
#define IC_74165_D5    PORTC.3
#define IC_74165_D6    PORTC.4
#define IC_74165_D7    PORTC.5

#define IC_74165_D0    PORTA.2
#define IC_74165_D1    PORTA.3
#define IC_74165_D2    PORTA.4  
#define IC_74165_D3    PORTA.5

#define IC_74165_SI    PORTA.1
#define IC_74165_EN_   PORTA.6

char ic_74165(void){
    char D = 0b01010101;
    char X=0;
    char Y=0;
    char temp=0; 
    
    // Input/Output Ports initialization
    // Port A initialization
    // Function: Bit7=In Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=In 
    DDRA=(0<<DDA7) | (1<<DDA6) | (1<<DDA5) | (1<<DDA4) | (1<<DDA3) | (1<<DDA2) | (1<<DDA1) | (0<<DDA0);
    // State: Bit7=T Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=T 
    PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

    // Port B initialization
    // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
    DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
    // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
    PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

    // Port C initialization
    // Function: Bit7=In Bit6=In Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
    DDRC=(0<<DDC7) | (0<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
    // State: Bit7=T Bit6=T Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
    PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

    // Port D initialization
    // Function: Bit7=Out Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
    DDRD=(1<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
    // State: Bit7=0 Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
    PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

    check = 0;
    IC_74165_CLK = LOW;
    IC_74165_EN_ = LOW;
    IC_74165_LOAD_ = HIGH;
    
    for(i=0;i<2;i++){
        X=D;
        for(j=0;j<8;j++){
            temp = (X & 0b11111111) % 2;
            IC_74165_SI = temp;
            X = (X>>1);
            IC_74165_CLK = HIGH;
            IC_74165_CLK = LOW;
            delay_ms(200);
        }
        X=0;
        Y=0;
        for(j=0;j<8;j++){
            X=(X>>1)|(IC_74165_Q<<7);
            Y=(Y>>1)|((~IC_74165_Q_)<<7);
            IC_74165_CLK = HIGH;
            IC_74165_CLK = LOW;
            delay_ms(200);
        }
        if(X==D | Y==D){
            check++;
        }
        D = D ^ 0b11111111;
        delay_ms(200);
    }
    delay_ms(500);
    for(i=0;i<2;i++){
        IC_74165_LOAD_ = LOW;
        IC_74165_D0=((D&0b10000000)>>7);
        IC_74165_D1=((D&0b01000000)>>6);
        IC_74165_D2=((D&0b00100000)>>5);
        IC_74165_D3=((D&0b00010000)>>4);
        IC_74165_D4=((D&0b00001000)>>3);
        IC_74165_D5=((D&0b00000100)>>2);
        IC_74165_D6=((D&0b10000010)>>1);
        IC_74165_D7=(D&0b00000001);
        IC_74165_CLK = HIGH;
        IC_74165_CLK = LOW;
        IC_74165_LOAD_ = HIGH;
        
        X=0;
        Y=0;
        for(j=0;j<8;j++){
            X=(X>>1)|(IC_74165_Q<<7);
            Y=(Y>>1)|((~IC_74165_Q_)<<7);
            IC_74165_CLK = HIGH;
            IC_74165_CLK = LOW;
            delay_ms(200);            
        }
        if(X==D | Y==D){
            check++;
        }
        D = D ^ 0b11111111;
        delay_ms(200);
    }
    if(check==4)
    {
        return 1;
    }      
    return 0;
}
// ------------------------------------------------------------------------------- //

// ----------------------------- IC 74166 ---------------------------------------- //
//ATMega I/P's
#define IC_74166_SO PINA.4

//ATMega O/P's
#define IC_74166_SI PORTC.0
#define IC_74166_D0 PORTC.1
#define IC_74166_D1 PORTC.2
#define IC_74166_D2 PORTC.3
#define IC_74166_D3 PORTC.4

#define IC_74166_D4 PORTA.1
#define IC_74166_D5 PORTA.2
#define IC_74166_D6 PORTA.3
#define IC_74166_D7 PORTA.5

#define IC_74166_CLK_INH    PORTC.5
#define IC_74166_CLK        PORTC.6

#define IC_74166_CLR_   PORTA.0
#define IC_74166_LOAD_  PORTA.6

char ic_74166(void){

    char D = 0b01010101;
    char X = 0;
    char temp = 0;
    
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

    check = 0;
    IC_74166_CLK_INH = LOW;
    IC_74166_CLK = LOW;
    
    IC_74166_CLR_ = HIGH;
    IC_74166_LOAD_ = HIGH;
    for(i=0;i<2;i++){
        X = D;
        for(j=0;j<8;j++){
            //SERIAL IN TRIAL
            temp = (X & 0b11111111) % 2;
            IC_74166_SI = temp;
            X = (X>>1);
            IC_74166_CLK = HIGH;
            IC_74166_CLK = LOW;
            delay_ms(200);
        }
        X = 0;
        for(j=0;j<8;j++){
            //CHECK SERIAL-IN OUTPUT
            X = (X>>1)|((IC_74166_SO)<<7);
            IC_74166_CLK = HIGH;
            IC_74166_CLK = LOW;
            delay_ms(200);
        }
        if(X == D){
            check++;
        }
        D = D^0b11111111;
        delay_ms(200);
    }
    delay_ms(1000);
    for(i=0;i<2;i++){
        IC_74166_LOAD_ = LOW;
        //PARALLEL-IN OUTPUT TEST
        IC_74166_D0 = ((D&0b10000000)>>7);
        IC_74166_D1 = ((D&0b01000000)>>6);
        IC_74166_D2 = ((D&0b00100000)>>5);
        IC_74166_D3 = ((D&0b00010000)>>4);
        IC_74166_D4 = ((D&0b00001000)>>3);
        IC_74166_D5 = ((D&0b00000100)>>2);
        IC_74166_D6 = ((D&0b10000010)>>1);
        IC_74166_D7 = (D&0b00000001);
        IC_74166_CLK = HIGH;
        IC_74166_CLK = LOW;
        IC_74166_LOAD_ = HIGH;
        X=0;
        for(j=0;j<8;j++){
            //PARALLEL-IN OUTPUT CHECK
            X = (X>>1)|((IC_74166_SO<<7));
            IC_74166_CLK = HIGH;
            IC_74166_CLK = LOW;
            delay_ms(500);
        }
        if(X==D){
            check++;
        }
        D = D^0b111111111;
        delay_ms(200);
    }
    
    IC_74166_CLR_ = LOW;
    delay_ms(1000);
    IC_74166_CLR_ = HIGH;
    
    X = 0;
    for(j=0;j<8;j++){
        //CLEAR CHECK
        X = (X>>1)|((IC_74166_SO)<<7);
        IC_74166_CLK = HIGH;
        IC_74166_CLK = LOW;
        delay_ms(500);
    }
    if(X == 0){
        check++;
    }
    if(check==5)
    {
        return 1;
    }      
    return 0;
}
// ------------------------------------------------------------------------------- //

// ----------------------------- IC 74173 ---------------------------------------- //
//ATMEGA I/P's

#define IC_74173_0Q      PINC.2
#define IC_74173_1Q      PINC.3
#define IC_74173_2Q      PINC.4
#define IC_74173_3Q      PINC.5

//ATMEGA O/P'S

#define IC_74173_0D      PORTA.5
#define IC_74173_1D      PORTA.4
#define IC_74173_2D      PORTA.3
#define IC_74173_3D      PORTA.2

#define IC_74173_OE1     PORTC.0
#define IC_74173_OE2     PORTC.1
#define IC_74173_DE1     PORTA.0
#define IC_74173_DE2     PORTA.1
#define IC_74173_REST    PORTA.6
#define IC_74173_CLK     PORTC.6

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

*/
/*
    Truth table

                INPUTS                                          |     OUTPUT      |
    ------------------------------------------------------------|-----------------|
            |           |       DATA ENABLE     |               |                 |
            |           |-----------|-----------|               |                 |
      CLR   |    CLK    |     DE1-  |    DE2-   |     DATA      |        Q        |
    --------|-----------|-----------|-----------|---------------|-----------------|
       H    |     X     |     X     |     X     |       X       |        L        |
    --------|-----------|-----------|-----------|---------------|-----------------|
       L    |     ^     |     X     |     X     |       X       |        Q0       |
    --------|-----------|-----------|-----------|---------------|-----------------|
       L    |     ^     |     H     |     X     |       X       |        Q0       |
    --------|-----------|-----------|-----------|---------------|-----------------|
       L    |     ^     |     X     |     H     |       X       |        Q0       |
    --------|-----------|-----------|-----------|---------------|-----------------|
       L    |     ^     |     L     |     L     |       L       |        L        |
    --------|-----------|-----------|-----------|---------------|-----------------|
       L    |     ^     |     L     |     L     |       H       |        H        |
*/
char ic_74173(void){

    char D=0b00000101;
    char temp=0b00000000;
     
    // Input/Output Ports initialization
    // Port A initialization 
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

    check = 0;
    IC_74173_CLK  = LOW;
    IC_74173_REST = LOW;
    
    IC_74173_OE1 = HIGH;
    IC_74173_OE2 = HIGH;
    
    IC_74173_DE1 = HIGH;
    IC_74173_DE2 = HIGH;
    
    //found = 0;
    for (i = 0; i < 2 ; i++)
    {
        IC_74173_DE1 = LOW;
        IC_74173_DE2 = LOW;
                 
        temp = ((D&0b00001000)>>3);
        IC_74173_3D = temp; 
        temp = ((D&0b00000100)>>2);
        IC_74173_2D = temp;
        temp = ((D&0b00000010)>>1);
        IC_74173_1D = temp;
        temp = (D&0b00000001);
        IC_74173_0D = temp;
        
        IC_74173_CLK = 1;
        IC_74173_CLK = 0;
        delay_ms(100);
        
        IC_74173_3D = 0;
        IC_74173_2D = 0;
        IC_74173_1D = 0;
        IC_74173_0D = 0;
        
        IC_74173_DE1 = HIGH;
        IC_74173_DE2 = HIGH;
        
        IC_74173_OE1 = LOW;
        IC_74173_OE2 = LOW;
        
        if((IC_74173_3Q==((D&0b00001000)>>3)) && (IC_74173_2Q==((D&0b00000100)>>2)) 
            && (IC_74173_1Q==((D&0b00000010)>>1)) && (IC_74173_0Q==(D&0b00000001)))
        {
            
            check++;
        }
        
        IC_74173_OE1 = HIGH;
        IC_74173_OE2 = HIGH;
        
        D=D^0b00001111;
        delay_ms(100);
    }
    
    IC_74173_REST = HIGH;
    IC_74173_REST = LOW;
                    
    IC_74173_OE1 = LOW;
    IC_74173_OE2 = LOW;
    
    if((IC_74173_3Q == 0x00) && (IC_74173_2Q == 0x00) 
        && (IC_74173_1Q == 0x00) && (IC_74173_0Q == 0x00))
    {
        check++;
    }
    
    IC_74173_OE1 = HIGH;
    IC_74173_OE2 = HIGH;
    
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
    
    if((IC_74173_3Q == 0x00) && (IC_74173_2Q == 0x00) 
        && (IC_74173_1Q == 0x00) && (IC_74173_0Q == 0x00))
    {
        check++;
    }
    
    /* WRITE HIGH TO THESE PINS */
    PORTC.2 = 1;
    PORTC.3 = 1;
    PORTC.4 = 1;
    PORTC.5 = 1;
    
    if((IC_74173_3Q == 0x01) && (IC_74173_2Q == 0x01) 
        && (IC_74173_1Q == 0x01) && (IC_74173_0Q == 0x01))
    {
        check++;
    }
    
    /* RESWITCH Q TO BE INPUT AGAIN */
    DDRC.2 = 0;
    DDRC.3 = 0;
    DDRC.4 = 0;
    DDRA.0 = 0;    
    if(check==5)
    {
        return 1;
    }      
    return 0;
}
// ------------------------------------------------------------------------------- //

// ----------------------------- IC 74174 ---------------------------------------- //
//ATMEGA I/P's
#define IC_74174_1Q      PINC.1
#define IC_74174_2Q      PINC.4
#define IC_74174_3Q      PINC.6
#define IC_74174_4Q      PINA.1
#define IC_74174_5Q      PINA.3
#define IC_74174_6Q      PINA.6


//ATMEGA O/P'S
#define IC_74174_1D      PORTC.2
#define IC_74174_2D      PORTC.3
#define IC_74174_3D      PORTC.5
#define IC_74174_4D      PORTA.2
#define IC_74174_5D      PORTA.4
#define IC_74174_6D      PORTA.5


#define IC_74174_CLK     PORTA.0
#define IC_74174_CLR     PORTC.0

/*
    IC PINS

        CLR- [-------] VCC
        1Q   [       ] 6Q
        1D   [       ] 6D
        2D   [       ] 5D
        2Q   [       ] 5Q 
        3D   [       ] 4D
        3Q   [       ] 4Q
        GND  [-------] CLK 

*/
/*
    Truth table

                INPUTS              |     OUTPUT      |
    --------------------------------|-----------------|
      CLR-  |    CLK    |     D     |       Q         |
    --------|-----------|-----------|-----------------|
       L    |     X     |     X     |       L         |
    --------|-----------|-----------|-----------------|
       H    |     ^     |     H     |       H         |
    --------|-----------|-----------|-----------------|
       H    |     ^     |     L     |       L         |
    --------|-----------|-----------|-----------------|
       H    |     L     |     X     |       Q0        |    

*/
char ic_74174(void){

    char D=0b00010101;
    char temp=0b00000000; 
    
    // Input/Output Ports initialization
    // Port A initialization 
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

    check = 0;
    IC_74174_CLK = LOW;
    IC_74174_CLR = HIGH;
    
    for (i = 0; i < 2 ; i++)
    {
        temp = ((D&0b00100000)>>5);
        IC_74174_6D = temp; 
        temp = ((D&0b00010000)>>4);
        IC_74174_5D = temp;         
        temp = ((D&0b00001000)>>3);
        IC_74174_4D = temp; 
        temp = ((D&0b00000100)>>2);
        IC_74174_3D = temp;
        temp = ((D&0b00000010)>>1);
        IC_74174_2D = temp;
        temp = (D&0b00000001);
        IC_74174_1D = temp;
        
        IC_74174_CLK = 1;
        IC_74174_CLK = 0;
        delay_ms(100);
        IC_74174_6D = 0;
        IC_74174_5D = 0;
        IC_74174_4D = 0;
        IC_74174_3D = 0;
        IC_74174_2D = 0;
        IC_74174_1D = 0;
        
        if((IC_74174_6Q ==((D&0b00100000)>>5)) && (IC_74174_5Q == ((D&0b00010000)>>4)) 
            && (IC_74174_4Q ==((D&0b00001000)>>3)) && (IC_74174_3Q==((D&0b00000100)>>2))
            && (IC_74174_2Q==((D&0b00000010)>>1)) && (IC_74174_1Q==(D&0b00000001)))
        {
            check++;
        }
        
        D=D^0b00111111;
        delay_ms(100);
        
    }
    if(check==2)
    {
        return 1;
    }      
    return 0;
}
// ------------------------------------------------------------------------------- //

// ----------------------------- IC 74175 ---------------------------------------- //
//ATMEGA I/P's
#define IC_74175_1Q      PINC.1
#define IC_74175_1Q_     PINC.2
#define IC_74175_2Q      PINC.6
#define IC_74175_2Q_     PINC.5

#define IC_74175_3Q      PINA.1
#define IC_74175_3Q_     PINA.2
#define IC_74175_4Q      PINA.6
#define IC_74175_4Q_     PINA.5


//ATMEGA O/P'S
#define IC_74175_1D  PORTC.3
#define IC_74175_2D  PORTC.4

#define IC_74175_3D  PORTA.3
#define IC_74175_4D  PORTA.4

#define IC_74175_CLK PORTA.0
#define IC_74175_CLR PORTC.0
/*
    IC PINS

        CLR- [-------] VCC
        1Q   [       ] 4Q
        1Q-  [       ] 4Q-
        1D   [       ] 4D
        2D   [       ] 3D 
        2Q   [       ] 3Q
        2Q-  [       ] 3Q-
        GND  [-------] CLK 

*/
/*
    Truth table

                INPUTS              |     OUTPUT      |
    --------------------------------|-----------------|
      CLR-  |    CLK    |     D     |   Q   |    Q-   |
    --------|-----------|-----------|-------|---------|
       L    |     X     |     X     |   L   |    H    |
    --------|-----------|-----------|-------|---------|
       H    |     ^     |     H     |   H   |    L    |
    --------|-----------|-----------|-------|---------|
       H    |     ^     |     L     |   L   |    H    |
    --------|-----------|-----------|-------|---------|
       H    |     L     |     X     |   Q0  |    Q0-  |    

*/
char ic_74175(void){

    char D=0b00000101;
    char temp=0b00000000;
    
    // Input/Output Ports initialization
    // Port A initialization
    // Function: Bit7=In Bit6=In Bit5=In Bit4=Out Bit3=Out Bit2=In Bit1=In Bit0=Out 
    DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (1<<DDA4) | (1<<DDA3) | (0<<DDA2) | (0<<DDA1) | (1<<DDA0);
    // State: Bit7=T Bit6=T Bit5=T Bit4=0 Bit3=0 Bit2=T Bit1=T Bit0=0 
    PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

    // Port B initialization
    // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
    DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
    // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
    PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

    // Port C initialization
    // Function: Bit7=In Bit6=In Bit5=In Bit4=Out Bit3=Out Bit2=In Bit1=In Bit0=Out 
    DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (1<<DDC4) | (1<<DDC3) | (0<<DDC2) | (0<<DDC1) | (1<<DDC0);
    // State: Bit7=T Bit6=T Bit5=T Bit4=0 Bit3=0 Bit2=T Bit1=T Bit0=0 
    PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

    // Port D initialization
    // Function: Bit7=Out Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
    DDRD=(1<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
    // State: Bit7=0 Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
    PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

    check = 0;
    IC_74175_CLK = LOW;
    IC_74175_CLR = HIGH;
    
    for (i = 0; i < 2 ; i++)
    {     
        temp = ((D&0b00001000)>>3);
        IC_74175_4D = temp; 
        temp = ((D&0b00000100)>>2);
        IC_74175_3D = temp;
        temp = ((D&0b00000010)>>1);
        IC_74175_2D = temp;
        temp = (D&0b00000001);
        IC_74175_1D = temp;
        
        IC_74175_CLK = 1;
        IC_74175_CLK = 0;
        delay_ms(1000);
        IC_74175_4D = 0;
        IC_74175_3D = 0;
        IC_74175_2D = 0;
        IC_74175_1D = 0;
        
        if( (IC_74175_4Q==((D&0b00001000)>>3)) && (IC_74175_3Q==((D&0b00000100)>>2)) && (IC_74175_2Q==((D&0b00000010)>>1)) && (IC_74175_1Q==(D&0b00000001)) ){
            check++;
        }
        if( (~IC_74175_4Q_==((D&0b00001000)>>3)) && (~IC_74175_3Q_==((D&0b00000100)>>2)) && (~IC_74175_2Q_==((D&0b00000010)>>1)) && (~IC_74175_1Q_==(D&0b00000001)) ){
            check++;
        }
        D=D^0b00001111;
        delay_ms(1000);
        
    }
    if(check==4)
    {
        return 1;
    }      
    return 0;
}
// ------------------------------------------------------------------------------- //

#define NUMBER_OF_ICS 6
char IC_FOUND = 0;
unsigned char *ICS[NUMBER_OF_ICS] = {"74164","74165","74166","74173","74174","74175"};
char (*ptr[NUMBER_OF_ICS])(void) = {ic_74164,ic_74165,ic_74166,ic_74173,ic_74174,ic_74175}; 
void main(void)
{
    // Timer/Counter 0 initialization
    // Clock source: System Clock
    // Clock value: Timer 0 Stopped
    // Mode: Normal top=0xFF
    // OC0 output: Disconnected
    TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (0<<CS02) | (0<<CS01) | (0<<CS00);
    TCNT0=0x00;
    OCR0=0x00;

    // Timer/Counter 1 initialization
    // Clock source: System Clock
    // Clock value: Timer1 Stopped
    // Mode: Normal top=0xFFFF
    // OC1A output: Disconnected
    // OC1B output: Disconnected
    // Noise Canceler: Off
    // Input Capture on Falling Edge
    // Timer1 Overflow Interrupt: Off
    // Input Capture Interrupt: Off
    // Compare A Match Interrupt: Off
    // Compare B Match Interrupt: Off
    TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
    TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
    TCNT1H=0x00;
    TCNT1L=0x00;
    ICR1H=0x00;
    ICR1L=0x00;
    OCR1AH=0x00;
    OCR1AL=0x00;
    OCR1BH=0x00;
    OCR1BL=0x00;

    // Timer/Counter 2 initialization
    // Clock source: System Clock
    // Clock value: Timer2 Stopped
    // Mode: Normal top=0xFF
    // OC2 output: Disconnected
    ASSR=0<<AS2;
    TCCR2=(0<<PWM2) | (0<<COM21) | (0<<COM20) | (0<<CTC2) | (0<<CS22) | (0<<CS21) | (0<<CS20);
    TCNT2=0x00;
    OCR2=0x00;

    // Timer(s)/Counter(s) Interrupt(s) initialization
    TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

    // External Interrupt(s) initialization
    // INT0: Off
    // INT1: Off
    // INT2: Off
    MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
    MCUCSR=(0<<ISC2);

    // USART initialization
    // USART disabled
    UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (0<<RXEN) | (0<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);

    // Analog Comparator initialization
    // Analog Comparator: Off
    // The Analog Comparator's positive input is
    // connected to the AIN0 pin
    // The Analog Comparator's negative input is
    // connected to the AIN1 pin
    ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
    SFIOR=(0<<ACME);

    // ADC initialization
    // ADC disabled
    ADCSRA=(0<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);

    // SPI initialization
    // SPI disabled
    SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);

    // TWI initialization
    // TWI disabled
    TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);

    while(1)
    {
        if(1)
        {
            IC_FOUND = 0;
            for(i=0;i<NUMBER_OF_ICS;i++)
            {                         
                if(ptr[i]())
                {
                    IC_FOUND = 1;
                    printf("IC %s is found",ICS[i]);
                    delay_ms(1000);
                    break;    
                }
            }
            if(IC_FOUND==0)
            {
                printf("No IC is found");
                delay_ms(1000);
            }    
        }
    } 
}
