/**
 * ************* Simple example using step motor (28BYJ-48) 5VDC *******************
 * [For student purposes]
 * @file main.c
 * @author Vinicius Malagi name (vinicius.malagi@outlook.com)
 * @brief
 * @version 0.1
 * @date 2022-10-30
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <avr/io.h>
#include <avr/interrupt.h>

volatile int count = 0;
int fullStep[4] = {0b00000011, 0b00000110, 0b00001100, 0b00001001};
int waveStep[4] = {0b00000001, 0b00000010, 0b00000100, 0b00001000};

ISR(TIMER0_OVF_vect)
{
    TCNT0 = 220; // Reload time
    if (count > 3)
        count = 0;
    PORTD = fullStep[count];
    count++;
}
int main(void)
{
    DDRD = 0xFF;
    PORTD = 0x00;

    // set prescaler 1024
    TCCR0B = 0b00000101;
    // set Flag Overflow - Timer 8 bits
    TIMSK0 = 0b00000001;
    // set timer value 02ms
    TCNT0 = 220;
    // Enable General key
    sei();

    for (;;)
    {
    }
}