// Show a map of devices found on the I2C bus.

#include <jee.h>

UartDev< PinA<9>, PinA<10> > console;

int printf(const char* fmt, ...) {
    va_list ap; va_start(ap, fmt); veprintf(console.putc, fmt, ap); va_end(ap);
    return 0;
}

I2cBus< PinB<7>, PinB<6> > bus;  // standard I2C pins for SDA and SCL

template< typename T >
void detectI2c (T bus) {
    for (int i = 0; i < 128; i += 16) {
        printf("%02x:", i);
        for (int j = 0; j < 16; ++j) {
            int addr = i + j;
            if (0x08 <= addr && addr <= 0x77) {
                bool ack = bus.start(addr<<1);
                bus.stop();
                printf(ack ? " %02x" : " --", addr);
            } else
                printf("   ");
        }
        printf("\n");
    }
}

int main () {
    detectI2c(bus);
}

// sample output:
//
//  00:                         -- -- -- -- -- -- -- --
//  10: -- -- -- -- -- -- -- -- -- -- -- -- -- 1D -- --
//  20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
//  30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
//  40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
//  50: 50 51 52 53 54 55 56 57 -- -- -- -- -- -- -- --
//  60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
//  70: -- -- -- -- -- -- -- --
