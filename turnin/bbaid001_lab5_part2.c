/*	Author: bbaid001
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{INIT, s0, s1, s2, s3, s4}state;
unsigned char temp;
unsigned char val;

void Tick()
{
    switch(state)
    {
       case INIT:
        state = s0;
        break;

        case s0:
            if(temp == 0x01)
            {
              state = s1;

            }
            else if(temp == 0x02)
            {
              state = s2;
            }
            else if(temp == 0x03)
            {
              state = s3;
            }
            else
            {
              state = s0;
            }
            break;

        case s4:
            if(temp == 0x00)
            {
              state = s0;
            }
            else if(temp == 0x03)
            {
              state = s3;
            }
            break;

        case s1:
            state = s4;
            break;

        case s2:
            state = s4;
            break;

        case s3:
            state = s4;
            break;

        default:
            break;
    }

    switch(state) {

        case INIT:
            break;

        case s0:
            PORTC = val;
            break;

        case s4:
            PORTC = val;
            break;

        case s1:
            if(PORTC == 0x09)
            {
                PORTC = val;
            }
            else
            {
                PORTC = val + 0x01;
                val = val + 0x01;
            }
            break;

        case s2:
            if(PORTC == 0x00)
            {
                PORTC = val;
            }
            else
            {
                PORTC = val - 0x01;
                val = val - 0x01;
            }
            break;

        case s3:
            PORTC = 0x00;
            val = 0x00;
            break;

        default:
            break;
    }
}

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

    val = 0x00;
    state = INIT;
    
    while (1)
    {
        temp = (~PINA & 0x03);
        Tick();
    }
}
 
