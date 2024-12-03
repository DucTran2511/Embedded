/*
 * bai_5.c
 *
 * Created: 2024/10/13 3:23:38 PM
 * Author: ADMIN
 */

#include <io.h>
#include <delay.h>

void hienThi()
{
    int i;
    for (i = 0; i<= 9; i++)
    {
        if (i == 0) 
        {
            PORTF = 0x81;
            PORTD = 0xF9;
            PORTA = 0x7F;
        }                
        
        if (i == 1)
        {
            PORTF = 0x87;
            PORTD = 0xFF;
            PORTA = 0x7F;
        }                
        
        if (i == 2)
        {
            PORTF = 0x85;
            PORTD = 0xF1;
            PORTA = 0xFF;
        }                
        
        if (i == 3)
        {
            PORTF = 0x85;
            PORTD = 0xF5;
            PORTA = 0x7F;
        }              
        
        if (i == 4)
        {
            PORTF = 0x83;
            PORTD = 0xF7;
            PORTA = 0x7F;
        }              
        
        if (i == 5)
        {
            PORTF = 0xA1;
            PORTD = 0xF5;
            PORTA = 0x7F;
        }              
        
        if (i == 6)
        {
            PORTF = 0xA1;
            PORTD = 0xF1;
            PORTA = 0x7F;
        }              
        
        if (i == 7)
        {
            PORTF = 0x85;
            PORTD = 0xFF;
            PORTA = 0x7F;
        }              
        
        if (i == 8)
        {
            PORTF = 0x81;
            PORTD = 0xF1;
            PORTA = 0x7F;
        }
        
        if (i == 9)
        {
            PORTF = 0x81;
            PORTD = 0xF5;
            PORTA = 0x7F;
        }               
        
        delay_ms(500);
    }   
}


void main(void)
{
    DDRF = 0xFF;
    DDRD = 0xFF;
    DDRA = 0xFF;
    while(1)
    {
        hienThi();
    }
}
