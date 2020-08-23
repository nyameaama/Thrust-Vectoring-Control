// Minimal serial output to USART1.

#include <jee.h>

UartDev< PinA<9>, PinA<10> > console;

void puts (const char* s) {
    while (*s)
        console.putc(*s++);
}

int main () {
    // TODO the baud rate is fixed at 115200 baud @ 8 MHz for now

    while (true) {
        puts("Hello!\n");

        for (int i = 0; i < 1000000; ++i)
            __asm("");
    }
}
