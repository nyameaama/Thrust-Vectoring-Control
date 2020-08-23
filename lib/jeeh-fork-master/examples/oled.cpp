// Use a 128x64 OLED as printf console.

#include <jee.h>
#include <jee/i2c-ssd1306.h>
#include <jee/text-font.h>

I2cBus< PinB<7>, PinB<6> > bus;  // standard I2C pins for SDA and SCL
SSD1306< decltype(bus) > oled;
Font5x7< decltype(oled) > console;

int printf(const char* fmt, ...) {
    va_list ap; va_start(ap, fmt); veprintf(console.putc, fmt, ap); va_end(ap);
    return 0;
}

int main () {
    enableSysTick();

    oled.init();
    oled.clear();

    printf("ASCII character set:\n");

    for (int o = 32; o < 128; o += 16) {
        printf("\n%02x: ", o);
        for (int i = 0; i < 16; ++i)
            console.putc(o+i);
    }

    wait_ms(5000);

    // start printing incrementing integers after 5 seconds
    int i = 0;
    while (true) {
        printf(" %d", ++i);
        wait_ms(100);
    }
}
