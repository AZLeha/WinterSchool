
#ifndef TIMERCOUNTER_H_
#define TIMERCOUNTER_H_
#include <stdint.h>

typedef enum 
{
	TIMER_MODE_NORMAL = 0,
	TIMER_MODE_PHASE_CORRECT_PWM,
	TIMER_MODE_PHASE_CTC,
	TIMER_MODE_FAST_PWM
}TIMER_MODE;

typedef enum
{
	TIMER_INTRRUPT_OVERFLOW = 1,
	TIMER_INTRRUPT_COMPARE
	
} TIMER_INTRRUPT;

typedef enum
{
	TIMER_PRESCALER_1 = 1,
	TIMER_PRESCALER_8,
	TIMER_PRESCALER_64,
	TIMER_PRESCALER_256,
	TIMER_PRESCALER_1024
	
} TIMER_PRESCALER;


//в перзентации сделать описание конфигурации вывода в соотвествие выбора режима
typedef enum
{
	TIMER_PIN_OUT_MODE_DISABEL = 0,
	TIMER_PIN_OUT_MODE1,
	TIMER_PIN_OUT_MODE2 ,
	TIMER_PIN_OUT_MODE3 
	
} TIMER_PIN_OUT_MODE;

 void timer_init(TIMER_MODE timerMode, TIMER_PIN_OUT_MODE pinMode);
 void timer_setInterrupt(TIMER_INTRRUPT interrupt);
 void timer_resetInterrupt(TIMER_INTRRUPT interrupt);
 void timer_setCompareValue(uint8_t value);
 void timer_setCounterValue(uint8_t value);
 void timer_setCallbackFunctionTheOverflowInterrupt(void (*callback)(void));
 void timer_setCallbackFunctionTheCompareInterrupt(void (*callback)(void));
 void timer_run(TIMER_PRESCALER prescaler);
 void timer_stop(void);


#endif /* TIMERCOUNTER_H_ */