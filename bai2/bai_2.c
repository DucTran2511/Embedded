/*
 * bai_2.c
 *
 * Created: 2024/10/13 2:22:05 PM
 * Author: ADMIN
 */

#include <io.h>
#include <alcd.h>
#include <delay.h>
#define BT1 PINB.2
#define BT2 PINB.3
#define BT3 PINB.0
#define BL PORTD.7
#define bam 0
void main()
{
    DDRB = 0x00;
    PORTB = 0x0D;
    DDRD = 0x80;
    PORTD = 0x80;
    lcd_init(16);
    lcd_clear();
    lcd_gotoxy(1,0);
    lcd_putsf("hello world");
    while(1)
    {
    
    }
}