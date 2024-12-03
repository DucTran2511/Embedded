/*
 * bai_4.c
 *
 * Created: 2024/10/13 3:11:11 PM
 * Author: ADMIN
 */

#include <io.h>
#include <alcd.h>
#include <delay.h>
#include <stdlib.h>
#define BT1 PINB.2
#define BT2 PINB.3
#define led PORTD.5
int dem = 0;
char buf[6];
void main(void)
{
    DDRB = 0x00;
    PORTB = 0x0C;
    DDRD = 0xA0;
    PORTD = 0xA0;
    lcd_init(16);
    while(1)
    {
        if (BT1 == 0)
        {
            while(BT2);
            delay_ms(250);
            dem++;
            itoa(dem,buf);
            lcd_clear();
            lcd_gotoxy(0,0);
            lcd_puts(buf);
        }
        if (BT2 == 0)
        {
            while(BT1);
            delay_ms(250);
            dem--;
            if (dem < 0) dem = 0;
            itoa(dem, buf);
            lcd_clear();
            lcd_gotoxy(0,0);
            lcd_puts(buf);
        }                 
        
        if (dem > 0) led = 1;
        else led = 0;
    }
}
