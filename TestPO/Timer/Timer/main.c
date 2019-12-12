#define  F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "timerCounter.h"


void compareHandler(void);
void overflowHandler(void);

;int main(void)
{
	timer_init(TIMER_MODE_NORMAL,TIMER_PIN_OUT_MODE_DISABEL);
	
	timer_setInterrupt(TIMER_INTRRUPT_COMPARE|TIMER_INTRRUPT_OVERFLOW);
	
	timer_setCallbackFunctionTheCompareInterrupt(compareHandler);
	timer_setCallbackFunctionTheOverflowInterrupt(overflowHandler);
	
	timer_setCompareValue(127);	
	timer_run(TIMER_PRESCALER_256);
	
	DDRB = 0xFF;
	
    while (1) 
    {
		PORTB |= 1<<5;
		_delay_ms(500);
		PORTB &= ~(1<<5);
		_delay_ms(500);
    }
}

void compareHandler(void)
{
	PORTB |= 1<<6;	
}

void overflowHandler(void)
{
	PORTB &= ~(1<<6);
}