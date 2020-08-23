// Analog input demo.

#include <jee.h>

UartDev< PinA<9>, PinA<10> > console;

int printf(const char* fmt, ...) {
    va_list ap; va_start(ap, fmt); veprintf(console.putc, fmt, ap); va_end(ap);
    return 0;
}

ADC<1> adc;
PinA<0> ana1;
PinA<1> ana2;

int main () {
    fullSpeedClock();
    adc.init();

    while (true) {
        // supply voltage can be estimated via the 1.2V bandgap reading
        int vref = (4095 * 1200) / adc.read(17);

        // a temperature reading of 1720 is roughly equivalent to:
        //  (1720*3332/4095-1430)/4.3+25 = 17.9 °C

        printf("1: %d, 2: %d, temp: %d, vref: %d mV\n",
                adc.read(ana1), adc.read(ana2), adc.read(16), vref);

        wait_ms(500);
    }
}

// sample output:
//  1: 105, 2: 1626, temp: 1720, vref: 3330 mV
//  1: 105, 2: 1628, temp: 1719, vref: 3330 mV
//  1: 105, 2: 1630, temp: 1719, vref: 3330 mV
//  1: 105, 2: 1632, temp: 1720, vref: 3330 mV
//  1: 104, 2: 1632, temp: 1720, vref: 3332 mV
