#include "LCD_commands.h"
#include "definitions.h"

#define LCD1_ADD 				0x27
#define LCD2_ADD                0x26
#define LINE_ONE                0x80
#define LINE_TWO                0xC0
#define LINE_THREE              0x94
#define LINE_FOUR               0xD4
#define LCD_HOME                0x02
#define LCD_CLEAR               0x01
#define LCD_ON                  0x0C
#define LCD_OFF                 0x08
#define CURSOR_ON               0x0A
#define CURSOR_OFF              0x08
#define CURSOR_BLINK            0x0F
#define CURSOR_INC              0x06
#define LCD_CURSOR_ON           0x0F
#define LCD_CURSOR_OFF          0x0C
#define LCD_UNDERLINE_ON        0x0E
#define LCD_SHIFT_LEFT          0x18
#define LCD_SHIFT_RIGHT         0x1E

uint8_t LCD_ADDR;

void delay_ms(uint16_t ms)
{
    uint16_t t;
    
    for (t=0; t<ms; t++)
    {
       TC0_TimerStart(); 
       while(!TC0_TimerPeriodHasExpired());
       TC0_TimerStop(); 
    }
}
void LCD_Select(uint8_t Select)
{
		
    switch (Select)
    {
        case 1:
            LCD_ADDR = LCD1_ADD;
            break;

        case 2:
            LCD_ADDR = LCD2_ADD;
            break;

        default:
            LCD_ADDR = LCD1_ADD;
            break;
    }
    
}

void lcd_send_cmd (unsigned char data)
{
	unsigned char data_l, data_u;
	data_l = (data<<4)&0xf0;
	data_u = data&0xf0; 
    uint8_t I2C_data[4];
   
	I2C_data[0] = (data_u|0x0C);  //enable=1 and rs =0
	I2C_data[1] = (data_u|0x08);  //enable=0 and rs =0
	I2C_data[2] = (data_l|0x0C);  //enable =1 and rs =0
	I2C_data[3] = (data_l|0x08);  //enable=0 and rs =0
    
    SERCOM0_I2C_Write(LCD_ADDR, I2C_data, 4);
    while(SERCOM0_I2C_IsBusy() == true);
}

void lcd_send_data (unsigned char data) 
{
    unsigned char data_l, data_u;
	data_l = (data<<4)&0xf0;
	data_u = data&0xf0; 
    uint8_t I2C_data[4];
	
    I2C_data[0] = (data_u|0x0D);  //enable=1 and rs =1
	I2C_data[1] = (data_u|0x09);  //enable=0 and rs =1
	I2C_data[2] = (data_l|0x0D);  //enable=1 and rs =1
	I2C_data[3] = (data_l|0x09);  //enable=0 and rs =1
    
    SERCOM0_I2C_Write(LCD_ADDR, I2C_data, 4);
    while(SERCOM0_I2C_IsBusy() == true);
}

void LCD_string(char *str) 
{
    while (*str) lcd_send_data(*str++);
}

void lcd_init (void)
{  
	lcd_send_cmd (0x02);
	lcd_send_cmd (0x28);
	lcd_send_cmd (0x0C);
	lcd_send_cmd (0x80);
    lcd_send_cmd (0x01);
    delay_ms(50);
}

void LCD_Goto(uint8_t row, uint8_t col)
{
  switch(row)
  {
    case 1:
      lcd_send_cmd(LINE_ONE + col - 1);
      break;
    case 2:
      lcd_send_cmd(LINE_TWO + col - 1);
      break;
    case 3:
      lcd_send_cmd(LINE_THREE  + col - 1);
      break;
    case 4:
      lcd_send_cmd(LINE_FOUR + col - 1);
    break;
    default:      
      lcd_send_cmd(LINE_ONE + col - 1);
  }
}
