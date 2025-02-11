/*
 * bai_7.c
 *
 * Created: 24/10/20 2:20:13 PM
 * Author: ADMIN
 */

#include <alcd.h>
#include <delay.h>

#define BT1 PINB.2
#define BT2 PINB.3
#define BT3 PINB.0
#define LED PORTD.5

unsigned char x = 0;
unsigned char dem = 0, dem_1 = 0;

interrupt [TIM0_OVF] void timer0_ovf_isr(void) {
    TCNT0 = 0x06;  // Reload timer for ~1 ms (depends on clock and prescaler)
    if (x == 1) {
        dem_1++;
        if (dem_1 == 10) {  // 10 ms
            dem++;
            dem_1 = 0;
        }
        if (dem == 100) {   // 1 second
            LED = 1;
        }
        if (dem == 200) {   // 2 seconds
            LED = 0;
            dem = 0;
        }
    }
}

void main(void) {
    DDRB = 0x00;  // Configure PORTB as input
    PORTB = 0x0D; // Enable pull-up resistors for BT1, BT2, BT3
    DDRD = 0x20;  // Configure PORTD.5 as output
    
    ASSR = 0 << AS0;   // Use internal clock source
    TCCR0 = 0x03;      // Timer0 with prescaler 64
    TCNT0 = 0x06;      // Initialize timer     
    OCR0 = 0x00;
    TIMSK = 0x01;
    ETIMSK = 0x00; // Enable Timer0 overflow interrupt
    
    #asm("sei")  // Enable global interrupts

    while (1) {
        if (BT1 == 0) {  // Button BT1 pressed
            delay_ms(250);  // Debounce
            LED = 1;
            x = 0;  // Stop timer logic
        }
        if (BT2 == 0) {  // Button BT2 pressed
            delay_ms(250);  // Debounce
            LED = 0;
            x = 0;  // Stop timer logic
        }
        if (BT3 == 0) {  // Button BT3 pressed
            delay_ms(250);  // Debounce
            x = 1;  // Start timer logic
        }
    }
}