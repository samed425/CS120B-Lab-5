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

enum States{INIT, wait, inc, dec, reset} state;
unsigned char temp;
unsigned char val;

void Tick()
{
    switch (state) {
    case (INIT) :
	val = 7;
	PORTC = val;
	break;

    case (wait) :
	PORTC = val;
	break;
    
    case (inc) :
	val = val + 1;
	PORTC = val;
	break;

    case (dec) :
	val = val - 1;
	break;

    case (reset) :
	val = 0;
	PORTC = val;
	break;

    default:
	break;    
}

    switch(state) {
    case (INIT) : 
	state = wait;
	break;
  
    case (wait) :
	if (PA0 && !PA1) {state = inc;}
	else if (!PA0 && PA1) {state = dec;}
	else if (PA0 && PA1) {state = reset;}
	else {state = wait;}
	break;

    case (inc) :
	state = wait;
	break;

    case (dec) :
	state = wait;
	break;

    case (reset) :
	val = 0;
	PORTC = val;
	break;

    default:
	state = INIT;
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
        Tick();
    }
}
 
