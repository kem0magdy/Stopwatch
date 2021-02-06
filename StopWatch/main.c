#include <avr/interrupt.h>
#include <util/delay.h>
#include "STD_TYPES.h"
#include "STPW_interface.h"


u8 GLOBAL_u8Tick=0;
u8 Flag_u8Counter=0;
u8 Sec_u8Counter=0;
u8 Min_u8Counter=0;
u8 Hour_u8Counter=0;




int main()
{

	DIO_Enable();
	/* Global Interrupt */
	SREG|= (1<<7);

	INT1_Enable();
	INT0_Enable();
	INT2_Enable();
	TMR1_Enable();

	while(1)
	{
		if(Flag_u8Counter== 1)
		{
			Sec_u8Counter++;
			if(Sec_u8Counter== 60)
			{
				Sec_u8Counter= 0;
				Min_u8Counter++;
			}

			if(Min_u8Counter== 60)
			{
				Min_u8Counter= 0;
				Hour_u8Counter++;
			}

			if(Hour_u8Counter== 12)
			{
				Hour_u8Counter= 0;
			}

		/* Reset Flag after full count*/
			Flag_u8Counter= 0;
		}
		else
		{

			PORTA= (PORTA & 0) | 0x01;
			PORTC= (PORTC & 0xF0) | (Sec_u8Counter%10);
			_delay_ms(2);
			PORTA= (PORTA & 0) | 0x02;
			PORTC= (PORTC & 0xF0) | (Sec_u8Counter/10);
			_delay_ms(2);

			PORTA= (PORTA & 0) | 0x04;
			PORTC= (PORTC & 0xF0) | (Min_u8Counter%10);
			_delay_ms(2);
			PORTA= (PORTA & 0) | 0x08;
			PORTC= (PORTC & 0xF0) | (Min_u8Counter/10);
			_delay_ms(2);

			PORTA= (PORTA & 0) | 0x10;
			PORTC= (PORTC & 0xF0) | (Hour_u8Counter%10);
			_delay_ms(2);
			PORTA= (PORTA & 0) | 0x20;
			PORTC= (PORTC & 0xF0) | (Hour_u8Counter/10);
			_delay_ms(2);
		}
	}
}

ISR(TIMER1_COMPA_vect)
{
	/* After OCR1A reaching 1000 => after 1 sec */
	Flag_u8Counter = 1;
}

ISR(INT1_vect)
{
	/* Clear 3 bit => close timer => pausing stop watch*/
	TCCR1B&= ~(1<< CS10);
	TCCR1B&= ~(1<< CS11);
	TCCR1B&= ~(1<< CS12);
}

ISR(INT0_vect)
{
	/* Resetting stop watch by apply zeros to counters */
	Sec_u8Counter = 0;
	Min_u8Counter = 0;
	Hour_u8Counter = 0;
}

ISR(INT2_vect)
{
	/* Set prescaler => open timer => resume stop watch */
	TCCR1B|= (1<<CS10);
	TCCR1B|= (1<<CS12);
}
