#include <io.h>
#include <twi.h>
#include <io.h>
#include <delay.h>
#include <i2c.h>
#include <alcd.h>
#include <stdio.h>
#include <ds1307.h>

#define DS1307_ADDRESS 0x68 // DS1307 I2C address

// Function prototypes
void i2c_init();
void i2c_start();
void i2c_stop();
void i2c_write(uint8_t data);
uint8_t i2c_read_ack();
uint8_t i2c_read_nack();
uint8_t bcd_to_dec(uint8_t bcd);
void ds1307_get_datetime(uint8_t *seconds, uint8_t *minutes, uint8_t *hours, uint8_t *day, uint8_t *month, uint8_t *year);

int main() {
    uint8_t seconds, minutes, hours, day, month, year;

    i2c_init(); // Initialize I2C

    while (1) {
        ds1307_get_datetime(&seconds, &minutes, &hours, &day, &month, &year);

        // Now you have the full date and time:
        // Example: 14:25:36 on 27/11/2024
        // seconds = 36, minutes = 25, hours = 14, day = 27, month = 11, year = 24
    }
}

// I2C Initialization
void i2c_init() {
    TWSR = 0x00; // Prescaler set to 1
    TWBR = 0x47; // SCL frequency ~100kHz (for 16MHz CPU clock)
    TWCR = (1 << TWEN); // Enable TWI
}

// Start I2C Communication
void i2c_start() {
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT
}

// Stop I2C Communication
void i2c_stop() {
    TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
}

// Write Byte to I2C
void i2c_write(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT
}

// Read Byte from I2C with ACK
uint8_t i2c_read_ack() {
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT
    return TWDR;
}

// Read Byte from I2C with NACK
uint8_t i2c_read_nack() {
    TWCR = (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT
    return TWDR;
}

// Convert BCD to Decimal
uint8_t bcd_to_dec(uint8_t bcd) {
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

// Get Full Date and Time from DS1307
void ds1307_get_datetime(uint8_t *seconds, uint8_t *minutes, uint8_t *hours, uint8_t *day, uint8_t *month, uint8_t *year) {
    i2c_start();
    i2c_write((DS1307_ADDRESS << 1) | 0); // Write mode
    i2c_write(0x00); // Set register pointer to 0x00 (seconds)
    i2c_start();
    i2c_write((DS1307_ADDRESS << 1) | 1); // Read mode

    *seconds = bcd_to_dec(i2c_read_ack());  // Read seconds
    *minutes = bcd_to_dec(i2c_read_ack());  // Read minutes
    *hours = bcd_to_dec(i2c_read_ack());    // Read hours
    i2c_read_ack(); // Skip weekday (optional, not used here)
    *day = bcd_to_dec(i2c_read_ack());      // Read day of the month
    *month = bcd_to_dec(i2c_read_ack());    // Read month
    *year = bcd_to_dec(i2c_read_nack());    // Read year

    i2c_stop();
}

void ds1307_get_datetime(uint8_t *seconds, uint8_t *minutes, uint8_t *hours, uint8_t *day, uint8_t *month, uint8_t *year);

void main(void) {
    uint8_t seconds, minutes, hours, day, month, year;
    char time_str[16];
    char date_str[16];

    lcd_init();

    lcd_init(16);
    rtc_init(3, 1, 0);

    #asm("sei") // Enable global interrupts

    while (1) {    
        // Fetch time and date
        ds1307_get_datetime(&seconds, &minutes, &hours, &day, &month, &year);
        // Check for day change
        // Format and display time
        sprintf(time_str, "%02u:%02u:%02u", hours, minutes, seconds);
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