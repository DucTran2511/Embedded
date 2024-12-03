/*
 * bai_10.c
 *
 * Created: 24/10/27 2:23:21 PM
 * Author: ADMIN
 */

#include <io.h>
#include <delay.h>
#include <alcd.h>
#include <stdio.h>
unsigned int gia_tri_adc;
char buffer[10];
#define ADC_VREF_TYPE 0x00
unsigned int read_adc(unsigned char adc_input){
    ADMUX = adc_input | ADC_VREF_TYPE;
    delay_us(10);
    ADCSRA |= 0x40;
    while((ADCSRA & 0x10)==0);
    ADCSRA |= 0x10;
    return ADCW;
}

void main(void)
{
    DDRD = 0x80;
    PORTD = 0x80;
    lcd_init(16);
    ADMUX = ADC_VREF_TYPE;
    ADCSRA = 0x83;

while (1)
    {
    // Please write your application code here      
    gia_tri_adc = read_adc(0);
    sprintf(buffer, "%d", gia_tri_adc);
    lcd_gotoxy(0,0);
    lcd_puts(buffer);
    delay_ms(100);
    }
}
