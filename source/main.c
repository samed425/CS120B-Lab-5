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

enum States{INIT, s0, s1, s2, s3} state;
unsigned char button;
unsigned char led;
void Tick()
{
   switch (state) {

	case (INIT) :
	   state = s0;
	   break;

	case (s0) :
	   if (button) { state = s1; }
	   else { state = s0; }
	   break;

	case (s1) :
	   if (!button) {state = s2; }
	   else { state = s1; }
	   break;
	
	case (s2) :
	   if (button) { state = s3; }
	   else { state = s2; }
	   break;

	case (s3) :
	   if (!button) { state = s0; }
	   else { state = s3; }
	   break;

	default:
	   break;
   }

   switch (state) {
	case (INIT) :
	   break;
	
	case (s0) :
	   led  = 0x2A;
	   break;

	case (s1) :
	   break;
	
	case (s2) :
	   led = 0x15;
	   break;
	
	case (s3) :
	   break;
	
	default :
	   break;
   }
   PORTB = led;
}

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    state = INIT;
    led = 0x00;
    button = 0x00;
    while (1)
    {
	button = ~PINA & 0x01;
        Tick();
    }
}
 
