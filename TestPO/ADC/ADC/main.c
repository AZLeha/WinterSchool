
#include <avr/io.h>
#include "ADC.h"

int main(void)
{
	DDRB = 0xFF;
	
	ADC_Init(ADC_VRS_EXTERNAL_AREF, ADC_CHANNEL_6, ADC_PRESCALER_32);
	
	while (1) 
    {	
		PORTB = (uint8_t) ADC_Read();
    }
}

