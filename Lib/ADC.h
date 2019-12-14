#ifndef ADC_H_
#define ADC_H_
#include <stdint.h>

typedef enum 
{
	ADC_VRS_INTERNAL_AREF = 0,
	ADC_VRS_EXTERNAL_AREF,
	ADC_VRS_INTERNAL_2_56 = 3
} ADC_VRS; //ADC voltage reference source

typedef enum
{
	ADC_CHANNEL_0 = 0,
	ADC_CHANNEL_1,
	ADC_CHANNEL_2,
	ADC_CHANNEL_3,
	ADC_CHANNEL_4,
	ADC_CHANNEL_5,
	ADC_CHANNEL_6,
	ADC_CHANNEL_7
} ADC_CHANNEL; //ADC voltage reference source

typedef enum
{
	ADC_PRESCALER_2 = 1,
	ADC_PRESCALER_4,
	ADC_PRESCALER_8,
	ADC_PRESCALER_16,
	ADC_PRESCALER_32,
	ADC_PRESCALER_64,
	ADC_PRESCALER_128
} ADC_PRESCALER; //ADC voltage reference source


void ADC_Init(ADC_VRS source, ADC_CHANNEL channel, ADC_PRESCALER prescaler);
uint16_t ADC_Read();


#endif /* ADC_H_ */