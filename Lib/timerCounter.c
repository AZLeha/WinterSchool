#include "timerCounter.h"
#include <avr/io.h>	
#include <avr/interrupt.h>
#include <stddef.h>

static void(*compareHandler)(void) = NULL;
static void(*overflowHandler)(void) = NULL;


void timer_init(TIMER_MODE timerMode, TIMER_PIN_OUT_MODE pinMode)
{
	TCCR0 = 0;
	if(timerMode & 1) TCCR0 |=  1<<WGM00;
	if(timerMode & 2) TCCR0 |=  1<<WGM01;
	
	TCCR0 |= pinMode<<COM00;
}


void timer_setInterrupt(TIMER_INTRRUPT interrupt)
{
	TIMSK |= interrupt;
	sei();
}


void timer_resetInterrupt(TIMER_INTRRUPT interrupt)
{
	TIMSK &= ~interrupt;
}


void timer_setCompareValue(uint8_t value)
{
	OCR0 = value;
}


 void timer_setCounterValue(uint8_t value)
 {
	 TCNT0 =value;
 }

void timer_setCallbackFunctionTheOverflowInterrupt(void (*callback)(void))
{
	overflowHandler = callback;
}


void timer_setCallbackFunctionTheCompareInterrupt(void (*callback)(void))
{
	compareHandler = callback;
}


void timer_run(TIMER_PRESCALER prescaler)
{
	timer_stop();
	SFIOR = 1<<PSR10;
	TCCR0 |= prescaler<<CS00;
}


void timer_stop(void)
{
	TCCR0 &= ~((1<<CS02) | (1<<CS01) | (1<<CS00));
}

ISR(TIMER0_COMP_vect)
{
	if(compareHandler != NULL) compareHandler();
	
}

ISR(TIMER0_OVF_vect)
{
	if(overflowHandler != NULL) overflowHandler();
}