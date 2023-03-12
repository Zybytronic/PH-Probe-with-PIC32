/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "LCD_commands.h"
#include <stdio.h>
#include <stddef.h>                     
#include <stdbool.h>                   
#include <stdlib.h>                     
#include "definitions.h"                

#define VREFA                (5.2f)


uint8_t i, n=10, j;
float t, median, a[10];

uint16_t raw_PH;
float volt_PH;
float PH = 0.00;
float conversion_value = 21.34 + 0.28;
char LCD_buff[5] = {0};

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize (NULL);
    LCD_Select(1);
    lcd_init ();
    ADC0_Enable();
    delay_ms(1000);
    
    LCD_Goto (1,1);
    LCD_string("Measured PH:");
    
    while ( true )
    {
   
		for (i = 0; i <= 11 ; i++)
			{
			raw_PH = ADC0_ConversionResultGet();
			volt_PH = (float)raw_PH * VREFA / 4095U;
			PH = -5.70 * volt_PH + conversion_value;
			a[i] = PH;
			}
       
				for (i = 1 ; i <= 10 ; i++)
					{ 
						for (j = 1 ; j <= 11-i ; j++)
							{
								if (a[j] <= a[j+1]) 
									{ 
									t = a[j];
									a[j] = a[j+1];
									a[j+1] = t;
									}
								else
								continue ;
							}
					}
    
		if ( n % 2 == 0)
			median = (a[n/2] + a[n/2+1])/2.0 ;
				else 
					median = a[n/2 + 1];
   
        sprintf(LCD_buff,"%.2f",median);
        LCD_Goto (1,14);
        LCD_string(LCD_buff);
        delay_ms(2000);
        
    }
    
    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

