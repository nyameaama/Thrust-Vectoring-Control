// Formatted printf output examples.

#include <jee.h>

UartDev< PinA<9>, PinA<10> > console;

int printf(const char* fmt, ...) {
    va_list ap; va_start(ap, fmt); veprintf(console.putc, fmt, ap); va_end(ap);
    return 0;
}

int main () {
    printf("%%b <%b> %%3o <%3o> %%d <%d> %%04x <%04x> %%2c <%2c> %%2s <%2s>\n",
            '!', '!', '!', '!', '!', "!");
}

// output:
//  %b <100001> %3o < 41> %d <33> %04x <0021> %2c < !> %2s <! >
