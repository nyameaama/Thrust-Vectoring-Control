// Print some numbers to an 84x48 Nokia 5110 graphics LCD.
//
// This assumes that the display is connected as follows:
//  PA0 = CLK
//  PA1 = DIN
//  PA2 = DC
//  PA3 = CE
//  PA4 = RST
//  PA5 = LIGHT
// Change pins below as needed.
// The backlight is optional, could be PWM'ed.

#include <jee.h>
#include <jee/dio-pcd8544.h>
#include <jee/text-font.h>

PinA<6> light;
PCD8544< PinA<0>, PinA<1>, PinA<3>, PinA<4>, PinA<5> > lcd;
Font5x7< decltype(lcd) > console;

int printf(const char* fmt, ...) {
    va_list ap; va_start(ap, fmt); veprintf(console.putc, fmt, ap); va_end(ap);
    return 0;
}

int main() {
    enableSysTick();

    light.mode(Pinmode::out);
    lcd.init();
    lcd.clear();

    while (1) {
        printf("%d ", ticks);
        wait_ms(500);
    }
}
