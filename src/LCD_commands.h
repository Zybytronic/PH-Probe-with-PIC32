#ifndef LCD_commands_H
#define LCD_commands_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus // Provide C Compatibility

    extern "C" {

#endif
// *****************************************************************************
// *****************************************************************************
// Section: Handler Routines
// *****************************************************************************
// *****************************************************************************

void delay_ms(uint16_t ms);        
void LCD_Select(uint8_t Select);
void lcd_send_cmd (unsigned char data);
void lcd_send_data (unsigned char data);
void LCD_string(char *str);
void lcd_init (void);
void LCD_Goto(uint8_t row, uint8_t col);



// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END

#endif 
 