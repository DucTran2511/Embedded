#include <io.h>
#include <delay.h>
#include <i2c.h>
#include <alcd.h>
#include <stdio.h>
#include <ds1307.h>

int d; // Blink flag
unsigned int dem; // Timer counter
unsigned char hour, minute, second; // Time variables
unsigned char day, month, year, weekday; // Date variables
//unsigned int count;


// Timer0 interrupt for blinking colon
interrupt[TIM0_OVF] void timer0_ovf_isr(void) {
    TCNT0 = 0x66; // Reload timer
    dem++;
    if (dem == 1000) d = 1; // Blink colon
    if (dem == 2000) {
        dem = 0;
        d = 0;
    }
}

const char *weekdays[] = {
    "Err", // Default for invalid day
    "Sun",
    "Mon",
    "Tue",
    "Wed",
    "Thu",
    "Fri",
    "Sat"
};

const char *get_weekday_name(unsigned char weekday) {
    if (weekday >= 1 && weekday <= 7) {
        return weekdays[weekday]; // Return valid day
    }
    return weekdays[0]; // Return "Err" for invalid
}


void main(void) {
    char time_str[16]; // Buffer for time
    char date_str[16]; // Buffer for date
    unsigned char prev_day = 31; // To detect day change   
    //DDRC.0 = 1;
    //PORTC.0 = 1;  

    // Initialize peripherals
    i2c_init();
    lcd_init(16);
    rtc_init(3, 1, 0);
    rtc_set_time(23, 59, 58); // Set time
    rtc_set_date(4, 31, 12, 24); // Set date

    #asm("sei") // Enable global interrupts

    while (1) {    
        // Fetch time and date
        rtc_get_time(&hour, &minute, &second);
        rtc_get_date(&weekday, &day, &month, &year);

        // Check for day change
        if (day != prev_day) {
            prev_day = day; // Update previous day
            weekday++; // Increment weekday
            if (weekday > 7) weekday = 1; // Wrap around if > 7    
        }

        // Format and display time
        sprintf(time_str, "%02u:%02u:%02u", hour, minute, second);
        lcd_clear();
        lcd_gotoxy(0, 0);
        lcd_puts("Time:");
        lcd_gotoxy(6, 0);
        lcd_puts(time_str);

        // Format and display date
        sprintf(date_str, "%02u/%02u/20%02u %s", day, month, year, get_weekday_name(weekday));
        lcd_gotoxy(0, 1);
        lcd_puts(date_str);

        delay_ms(500); // Avoid flicker
    }
}

