/*
 * bai8.c
 *
 * Created: 24/10/27 2:04:48 PM
 * Author: ADMIN
 */

#include <io.h>
#include <stdio.h>
#include <delay.h>
#define servo_1 PORTC.7
#define BT1 PINB.2
#define BT2 PINB.3
int dem;
char vi_tri;
interrupt [TIM0_OVF] void timer0_ovf_isr(void){
    TCNT0 = 0xB0;
    dem++;
    if(dem == 2000) dem = 0;
    if(dem < vi_tri) servo_1 = 1;
    else servo_1 = 0;
}


void main(void)
{
    DDRC = 0x80;
    DDRB = 0x00;
    PORTB = 0x0C;
    ASSR = 0x00;
    TCCR0 = 0x01;
    TCNT0 = 0xB0;
    OCR0 = 0x00;
    TIMSK = 0x01;
    ETIMSK = 0x00;
    #asm("sei")
while (1)
    {
    // Please write your application code here
    if(BT1 == 0){
        vi_tri = 150;
    }   
    if(BT2 == 0){
        vi_tri= 175;
    }
    }   
}
