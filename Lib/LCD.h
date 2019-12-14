#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>

/*! Инцилизация LCD
*/
void LCD_Init(void);

/*! Инцилизация LCD
* par[in] data входыне данныу
*/
void LCD_WriteChar(char data);
void LCD_WriteString(char *data);
void LCD_WriteInt(int data);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t row, uint8_t column);

#endif /* LCD_H_ */