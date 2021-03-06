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

enum States{INIT, wait, inc, dec, reset, depress} state;
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
	if (val == 9) { break; }
	val = val + 1;
	PORTC = val;
	break;

    case (dec) :
	if (val == 0) { break;}
	val = val - 1;
	break;

    case (reset) :
	val = 0;
	PORTC = val;
	break;

    case (depress) :
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
	state = depress;
	break;

    case (dec) :
	state = depress;
	break;

    case (reset) :
	val = 0;
	PORTC = val;
	break;

   case (depress) :
	if (!PA0 && !PA1) { state = wait; }	
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
 
