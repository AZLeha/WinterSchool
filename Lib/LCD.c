#include "LCD.h"
#include <avr/io.h>
#include <util/delay.h>


#define LCD_IR 0
#define LCD_DR 1


static void LCDLolLVLInit();


__attribute__((always_inline)) static inline void LCDSetRegister(uint8_t reg);
__attribute__((always_inline)) static inline void LCDWriteHalfWord(uint8_t word);
static void writeOneByteinLSD(uint8_t reg, uint8_t data);

static void LCDdelay(int delay);



void LCD_Init()
{
	LCDdelay(150);
	LCDLolLVLInit();

	writeOneByteinLSD(LCD_IR,0x33);
	writeOneByteinLSD(LCD_IR,0x32);
	writeOneByteinLSD(LCD_IR,0x28);
	writeOneByteinLSD(LCD_IR,0x0C);
	LCD_Clear();
}


void LCD_WriteChar(char data)
{
	writeOneByteinLSD(LCD_DR,data);
}


void LCD_WriteString(char *data)
{
	for( int i = 0; (i < 15) && (*data != '\0'); i++, data++)
	LCD_WriteChar(*data);
}


void LCD_WriteInt(int data)
{
	char dataArray[16];

	sprintf(dataArray,"%d",data);
	LCD_WriteString(dataArray);
}


void LCD_Clear()
{
	writeOneByteinLSD(LCD_IR,0x01);
	LCDdelay(10);
}


void LCD_SetCursor(uint8_t row, uint8_t column)
{
	writeOneByteinLSD(LCD_IR, ((0xC0 * row) + column) | 0x80);
}






static void LCDLolLVLInit()
{
	// A4 A5 A0 A1 A2 A3	
	// RS E  D4 D5 D6 D7
	DDRA |= 0x3F;
	PORTA &= ~0x3F; 
		
}


__attribute__((always_inline)) static inline void LCDSetRegister(uint8_t reg)
{
	// A4 A5 A0 A1 A2 A3
	// RS E  D4 D5 D6 D7
	#define LCD_RS 0x10 //1<<4
	if(reg == LCD_DR)
		PORTA |= LCD_RS;
	else
		PORTA &= ~LCD_RS;
}


__attribute__((always_inline)) static inline void LCDWriteHalfWord(uint8_t word)
{
	// A4 A5 A0 A1 A2 A3
	// RS E  D4 D5 D6 D7
	PORTA &= 0xF0;
	PORTA |= word&0x0f;
	
	#define LCD_E 0x20 //1<<4

	PORTA |= LCD_E;
	LCDdelay(1);
	PORTA &= ~LCD_E;
	LCDdelay(1);

}


static void writeOneByteinLSD(uint8_t reg, uint8_t data)
{
	LCDSetRegister(reg);

	//MSB
	LCDWriteHalfWord(data>>4);
	LCDWriteHalfWord(data & 0x0f);
}


static void LCDdelay(int delay)
{
	for(; delay; delay--)
		_delay_ms(1);
}