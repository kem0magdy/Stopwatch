/*******************************************************************/ 
/**************** Name    : Kamal Magdy Kamal ElDin ****************/
/**************** Date    : 2/2/2021                ****************/
/**************** Version : 1.0.0                   ****************/
/**************** SWC     : StopWatch               ****************/

#include"STPW_interface.h"
#include<avr/io.h>
#include <avr/interrupt.h>



void DIO_Enable (void)
{
	/* Config of out and inputs pins */
	DDRC|= 0b00001111;
	DDRA|= 0b00111111;
	DDRB&= ~(1<<2);
	DDRD&= ~(1<<2);
	DDRD&= ~(1<<3);
	
	/* Pull Up Resis */
	PORTB&= ~(1<<2);
	PORTD&= ~(1<<2);
	
	/* Zeros At begining */
	PORTC|= 0b11110000;
	PORTA|= 0b00111111;
	
}
void TMR1_Enable(void)
{
	TCNT1 = 0; 
	/* Comparing reg OCR1A with 1000 (1 sec) */
	OCR1A= 1000; 
	TIMSK|= (1<<OCIE1A);
	TCCR1A= (1<<FOC1A) | (1<<FOC1B);
	TCCR1B|= (1<<WGM12);
	TCCR1B|= (1<<CS10);
	TCCR1B|= (1<<CS12);
}

void INT1_Enable(void)
{
	/* External Interrupt */
	GICR|= (1<<INT1);
	/* INT1 Raising Edge */
	MCUCR|= (1<<ISC10);
	MCUCR|= (1<<ISC11);

}

void INT0_Enable(void)
{
	/* External Interrupt */
	GICR|= (1<<INT0);
	/* INT0 Falling Edge*/
	MCUCR&= ~(1<<ISC00);
	MCUCR|= (1<<ISC01);
}


void INT2_Enable(void)
{
	/* External Interrupt */
	GICR|= (1<<INT2);
	/* INT2 Falling edge */
	MCUCSR&= ~(1<<ISC2);

}
