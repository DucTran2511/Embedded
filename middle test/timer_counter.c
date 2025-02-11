#include <io.h>
#include <interrupt.h>
#include <delay.h>

// Pin definitions
#define BUZZER_PIN PORTB.0       // Buzzer connected to PORTB bit 0

// Timekeeping variables
volatile unsigned char seconds = 0;
volatile unsigned char minutes = 0;
volatile unsigned char hours = 8; // Start from 8:00 AM

// Predefined bell timings (hours and minutes)
const unsigned char bell_timings[][2] = {
    {8, 0},  // 8:00 AM
    {9, 30}, // 9:30 AM
    {12, 0}, // 12:00 PM
    {15, 0}  // 3:00 PM
};

// Function to initialize Timer1
void timer1_init() {
    TCCR1A = 0x00;               // Normal mode
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC mode, prescaler 1024
    OCR1A = 15624;               // Compare value for 1 second (16 MHz clock)
    TIMSK |= (1 << OCIE1A);      // Enable Timer1 compare interrupt
}

// Function to activate the buzzer
void activate_buzzer() {
    BUZZER_PIN = 1;              // Turn on buzzer
    delay_ms(3000);              // Keep buzzer on for 3 seconds
    BUZZER_PIN = 0;              // Turn off buzzer
}

// Function to check if the current time matches bell timing
unsigned char check_bell(unsigned char hour, unsigned char minute) {
    unsigned char i;
    for (i = 0; i < sizeof(bell_timings) / 2; i++) {
        if (bell_timings[i][0] == hour && bell_timings[i][1] == minute) {
            return 1; // Match found
        }
    }
    return 0; // No match
}

// Timer1 Compare Match Interrupt Service Routine (ISR)
interrupt [TIM1_COMPA] void timer1_isr(void) {
    seconds++; // Increment seconds
    if (seconds >= 60) {
        seconds = 0;
        minutes++;
        if (minutes >= 60) {
            minutes = 0;
            hours++;
            if (hours >= 24) {
                hours = 0; // Reset to midnight
            }
        }
    }
}

void main(void) {
    // Set clock frequency (optional, use CodeWizardAVR for configuration if needed)
    #asm
        cli // Disable interrupts during setup
    #endasm

    // Initialize buzzer pin
    DDRB.0 = 1;    // Configure PORTB.0 as output
    BUZZER_PIN = 0; // Ensure buzzer is off

    // Initialize Timer1
    timer1_init();

    // Enable global interrupts
    #asm
        sei
    #endasm

    while (1) {
        // Check if it's time to ring the bell
        if (check_bell(hours, minutes)) {
            activate_buzzer(); // Activate buzzer for the bell
        }

        // Main loop can include additional logic (e.g., display code)
    }
}
