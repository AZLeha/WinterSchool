/*!
*	\defgroup timerCounter 	timerCounter
*	\ingroup timerCounter
* @{
*/


#ifndef TIMERCOUNTER_H_
#define TIMERCOUNTER_H_
#include <stdint.h>



/*	\file LCD
*	\brief 	Библиотека для работы c  
*
*/



/*!
 * \brief Причисления для выбора режима работы таймера. 
 *
 * Подробное описание режимов работы приведено в презентации на слайде №21
 */
typedef enum 
{
	TIMER_MODE_NORMAL = 0,  		//!< Normal режим
	TIMER_MODE_PHASE_CORRECT_PWM,	//!< PWM, Phase Correct диаграмма работы таймера приведена в презентации на слайде №22
	TIMER_MODE_PHASE_CTC,			//!< CTC диаграмма работы таймера приведена в презентации на слайде №23
	TIMER_MODE_FAST_PWM            	//!< Fast PWM диаграмма работы таймера приведена в презентации на слайде №24

}TIMER_MODE;


/*!
 * \brief Причисления с описанием масок разрешения прерываний. 
 *
 * Данное перечисление позволяет выключать/выключать соответствующий обработчик прерывания с помощью функций #timer_setInterrupt и #timer_resetInterrupt
 */
typedef enum
{
	TIMER_INTRRUPT_OVERFLOW = 1,	//!< Маска включения/отключения прерывания по переполнению
	TIMER_INTRRUPT_COMPARE			//!< Маска включения/отключения прерывания по сравнению
	
} TIMER_INTRRUPT;


/*!
 * \brief Причисления для выбора делителя на входе таймера. 
 *
 * Таймер тактируется с частотой ядра по умолчанию на стенде это 1МГц. Данное перечисление позволяет задать делитель частоты с которым будет работать таймер.  Рассчитать частоту наступления переполнения таймера можно по следующей формуле    
 * F_CLK/Prescaler/256
 */
typedef enum
{
	TIMER_PRESCALER_1 = 1,	//!< F_CLK/1
	TIMER_PRESCALER_8,		//!< F_CLK/8
	TIMER_PRESCALER_64,		//!< F_CLK/64
	TIMER_PRESCALER_256, 	//!< F_CLK/256
	TIMER_PRESCALER_1024	//!< F_CLK/1024
	
} TIMER_PRESCALER;


/*!
 * \brief Причисления для выбора режима работы вывода OCn 
 *
 * Поведение вывода OCn зависит от установленного режима работы таймера и непосредственно конфигурации битов отвечающих за сам вывод.    
 * 	  MODE | non-PWM Mode(normal или CTC) | Fast PWM Mode | Phase Correct PWM Mode
 *    ------------- | ------------------ | ------------ | ---------------------------------
 *	 |MODE_DISABEL|disconnected|disconnected|disconnected|
 *	 |MODE1| Toggle OC0|Reserved|Reserved|
 *	 |MODE2| Clear OC0| Clear OC0 on compare match, set OC0 at BOTTOM,(nin-inverting mode)|Clear OC0 on compare match when up-counting. Set OC0 on compare match when downcounting.|
 *	 |MODE3| Set OC0| Set OC0 on compare match, clear OC0 at BOTTOM,(inverting mode)|Set OC0 on compare match when up-counting. Clear OC0 on compare match when downcounting.|
 */
typedef enum
{

	TIMER_PIN_OUT_MODE_DISABEL = 0, //!< MODE_DISABEL
	TIMER_PIN_OUT_MODE1,			//!< MODE1
	TIMER_PIN_OUT_MODE2 ,			//!< MODE2
	TIMER_PIN_OUT_MODE3 			//!< MODE3
	
} TIMER_PIN_OUT_MODE;


/*!
* \brief Функция инициализации тйамера
*
* Функция позволяет инициализировать таймер с заданными параметрами
* \param[in] timerMode 	Выбор \link  #TIMER_MODE ирежима работы таймера \endlink 
* \param[in] pinMode 	Выбор \link  #TIMER_PIN_OUT_MODE выбор режима работы вывода OC0\endlink 
*/
 void timer_init(TIMER_MODE timerMode, TIMER_PIN_OUT_MODE pinMode);
 
 
 /*!
* \brief Функция включения прерывания
*
* Функция позволяет включить необходимое прерывание 
* \warning По мимо разрешения прерывания необходимо назначить его обработчик с помощью функций #timer_setCallbackFunctionTheOverflowInterrupt и  #timer_setCallbackFunctionTheCompareInterrupt
*
* \param[in] interrupt 	Установка \link  #TIMER_INTRRUPT  маски прерываний \endlink 
*/
 void timer_setInterrupt(TIMER_INTRRUPT interrupt);
 
 
 /*!
* \brief Функция выключения прерывания
*
* Функция позволяет выключить необходимое прерывание 

* \param[in] interrupt 	Установка \link  #TIMER_INTRRUPT  маски прерываний \endlink 
*/
 void timer_resetInterrupt(TIMER_INTRRUPT interrupt);
 
 
 /*!
* \brief Функция установки значения в регистр сравнения
*
* Функция при достижении установленного значения будет генерироваться событие по сравнению и если разрешено прерывание по сравнению то вызовется его обработчик   
* \param[in] value 	значение сравнения
*/
 void timer_setCompareValue(uint8_t value);
 
 
 /*!
* \brief Функция устанавливает текущее значение счётного регистра 
*
* Данная функция позволяет установить значение с которого начнётся отчёт таймера. 
* \param[in] value 	значение счётного регистра
*/
 void timer_setCounterValue(uint8_t value);


/*!
* \brief Функция установки обработчика прерывания по переполнению
*
* Даная функция позволяет установить функцию обратного вызова которая будет вызываться при  наступлении события переполнения. Обработчик должен иметь следующий вид:
    \code
    void handler(void)
	{	
	}
    \endcode
* \param[in] callback указатель на функцию обработчик	
*/
 void timer_setCallbackFunctionTheOverflowInterrupt(void (*callback)(void));
 
 
 /*!
* \brief Функция установки обработчика прерывания по переполнению
*
* Даная функция позволяет установить функцию обратного вызова которая будет вызываться при  наступлении события сравнения. Обработчик должен иметь следующий вид:
    \code
    void handler(void)
	{	
	}
    \endcode
* \param[in] callback указатель на функцию обработчик	
*/
 void timer_setCallbackFunctionTheCompareInterrupt(void (*callback)(void));
 
 
 /*!
* \brief Функция запуска таймера
*
* Функция позволяет запустить таймер, пр и запуске необходимо указатель предделителя частоты
* \param[in] prescaler 	Выбор \link  #TIMER_PRESCALER предделителя частоты\endlink 
*/
 void timer_run(TIMER_PRESCALER prescaler);
 
 
 /*!
* \brief Функция остановки таймера
*
* Функция останавливает таймер. 
*/
 void timer_stop(void);


#endif /* TIMERCOUNTER_H_ */
/*! @} */