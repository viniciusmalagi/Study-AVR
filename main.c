#include <avr/io.h>
#include<avr/interrupt.h>

//Global variable
int count=0;

ISR(PCINT0_vect);

int main (void) {
    char display[10] = {0b10000100,0b11010011,0b11010110,0b10110100,0b01110110,0b01111111,0b11000100,0b11111111,0b11111110,0b11100111};
    //Button configuration 
    DDRB = 0b00000000;
    PORTB = 0b00001000;

    //Display configuration
    DDRD |= 0b11111111;
    PORTD = display[0];

    //Interrupt configuration
    PCICR = 0b00000001; //PCINT0
    PCMSK0 =  0b00001000; //PB3

    //Enable "General key"
    sei();

    while(1) {
        PORTD = display[count];
    }
}

ISR(PCINT0_vect){
    if(!(PINB & (1<<3))){
        count++;
    }
    if (count > 9){
        count = 0;
    }
}