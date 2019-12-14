#include "ADC.h"
#include <avr/io.h>

void ADC_Init(ADC_VRS source, ADC_CHANNEL channel, ADC_PRESCALER prescaler)
{
	ADMUX = (source<<REFS0) | channel;
	DDRA &= ~(1<<channel);
	
	ADCSRA = (1<<ADEN) | prescaler;
	
}
uint16_t ADC_Read()
{
	ADCSRA |= 1<<ADSC;
	
	for(uint32_t i = 0; (i < 0xFFFFFF) && !(ADCSRA&(1<<ADIF)) ; i++) asm("NOP");
	
	return  ADCW;
}