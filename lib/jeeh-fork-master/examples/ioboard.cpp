// Demo of a TM1638-based I/O board with 8x 7-seg, 8x LED, and 8x buttons.
//
// Assumes this board is connected as follows:
//  STB => Pin A6
//  CLK => Pin A5
//  DIO => Pin A4
// Change pins below as needed.
// Kepresses are reported on the serial console.
//
// The board is available from eBay, e.g. https://www.ebay.com/itm/400531985021

#include <jee.h>
#include <jee/dio-tm1638.h>

UartDev< PinA<9>, PinA<10> > console;

int printf(const char* fmt, ...) {
    va_list ap; va_start(ap, fmt); veprintf(console.putc, fmt, ap); va_end(ap);
    return 0;
}

TM1638< PinA<6>, PinA<5>, PinA<4> > ioboard;

int main () {
    enableSysTick();

    // 0..9 to 7-seg conversion table
    static uint8_t const digits [] = {
        0b0111111, 0b0000110, 0b1011011, 0b1001111, 0b1100110,
        0b1101101, 0b1111101, 0b0000111, 0b1111111, 0b1100111,
    };

    for (uint32_t seq = 0; true; ++seq) {
        uint8_t buf [8];

        // the first four displays show some raw segment data
        *(uint32_t*) buf = ticks;

        // the last four displays show a decimal counter, no leading zeros
        buf[4] = seq < 1000 ? 0 : digits[seq/1000 % 10];
        buf[5] = seq < 100  ? 0 : digits[seq/100  % 10];
        buf[6] = seq < 10   ? 0 : digits[seq/10   % 10];
        buf[7] =                  digits[seq      % 10];
        ioboard.send(buf);

        // print elapsed time and key presses
        printf("%d ms, %032b\n", ticks, ioboard.receive());

        wait_ms(100);
    }
}

// sample output:
//
//  1002 ms, 00000000000000000000000000000000
//  1102 ms, 00000000000000010000000000000000
//  1202 ms, 00000000000000010000000000000000
//  1302 ms, 00000000000000010000000000000000
//  1402 ms, 00000000000000010000000000000000
//  1502 ms, 00000000000000000000000000000000
//  1602 ms, 00000000000000000000000000000000
//  1702 ms, 00000000000000000000000000000000
//  1802 ms, 00000000000000000000000000000000
//  1902 ms, 00000000000000000000000100000000
//  2002 ms, 00000000000000000000000100000000
