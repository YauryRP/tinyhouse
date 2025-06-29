#include "mbed.h"
#include "max7219.h"

SPI spi(D11, NC, D13);
Max7219 display(&spi, D10);

// Bitmap-Daten
const uint8_t H[8] = {0b10000010, 0b10000010, 0b11111110, 0b10000010, 0b10000010, 0b10000010, 0b10000010, 0b00000000};
const uint8_t O[8] = {0b01111100, 0b10000010, 0b10000010, 0b10000010, 0b10000010, 0b10000010, 0b01111100, 0b00000000};
const uint8_t L[8] = {0b10000000, 0b10000000, 0b10000000, 0b10000000, 0b10000000, 0b10000000, 0b11111110, 0b00000000};
const uint8_t A[8] = {0b11111110, 0b10000010, 0b10000010, 0b11111110, 0b10000010, 0b10000010, 0b10000010, 0b00000000};


void show_char(uint8_t address, const uint8_t *bitmap) {
    for (int row = 0; row < 8; row++) {
        display.write_digit(address + 1, row + 1, bitmap[row]);
    }
    wait_us(100);
}

int main() {
    display.set_num_devices(4);

    max7219_configuration_t cfg = {
        .device_number = 1,
        .decode_mode   = 0x00,  // Kein BCD-Decode
        .intensity     = 7,
        .scan_limit    = 7      // 8 Zeilen (0-7)
    };

    display.init_display(cfg);
    display.enable_display();
    display.display_all_off();
    wait_us(100);

    show_char(3, H);
    show_char(0, A);
    show_char(2, O);
    show_char(1, L);


    while (true) {
        // Endlosschleife
    }
}
