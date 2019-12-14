

#include <avr/io.h>
#include "LCD.h"

int main(void)
{
	LCD_Init();
	LCD_WriteString("Test 1 row");
	LCD_SetCursor(1,0);
	LCD_WriteString("Test 2 row");
   
    while (1) 
    {
    }
}

