// Show a snake running across two 8x8 LED matrix displays w/ MAX7219.

#include <jee.h>
#include <jee/spi-max7219.h>

SpiGpio< PinA<7>, PinA<6>, PinA<5>, PinA<4> > spi;
MAX7219< decltype(spi), 2 > matrix;

int main() {
    enableSysTick();

    spi.init();
    matrix.init();

    while (true)
        for (int y = 0; y < 8; ++y) {
            // first turn each X pixel on
            for (int x = 0; x < 16; ++x) {
                matrix.pixel(x, y, 1);
                wait_ms(20);
            }
            // then turn each X pixel off again
            for (int x = 0; x < 16; ++x) {
                matrix.pixel(x, y, 0);
                wait_ms(20);
            }
        }
}
