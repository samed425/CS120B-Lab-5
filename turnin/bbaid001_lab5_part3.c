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
unsigned char temp;
unsigned char val;

void Tick()
{
   switch (state) {

	case (INIT) :
	   state = s0;
	   break;

	case (s0) :
	   if (PORTA == 0x01) { state = s1; }
	   else { state = s0; }
	   break;

	case (s1) :
	   if (PORTA == 0x00) {state = s2; }
	   else { state = s1; }
	   break;
	
	case (s2) :
	   if (PORTA == 0x01) { state = s3; }
	   else { state = s2; }
	   break;

	case (s3) :
	   if (PORTA == 0x00) { state = s0; }
	   else { state = s3; }
	   break;

	default:
	   break;
   }

   switch (state) {
	case (INIT) :
	   break;
	
	case (s0) :
	   PORTB = 0x2A;
	   break;

	case (s1) :
	   break;
	
	case (s2) :
	   PORTB = 0x15;
	   break;
	
	case (s3) :
	   break;
	
	default :
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
 
