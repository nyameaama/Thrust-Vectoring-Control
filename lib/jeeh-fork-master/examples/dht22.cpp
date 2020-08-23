// Periodically read out a DHT22 sensor attached to Pin A5.

#include <jee.h>
#include <jee/dio-dht22.h>

UartDev< PinA<9>, PinA<10> > console;

int printf(const char* fmt, ...) {
    va_list ap; va_start(ap, fmt); veprintf(console.putc, fmt, ap); va_end(ap);
    return 0;
}

DHT22< PinA<5> > sensor;

int main() {
    fullSpeedClock();
    sensor.init();

    while (true) {
        int16_t t, h;
        if (sensor.read(t, h))
            printf("temp: %d, humi: %d\n", t, h);
        wait_ms(1000);
    }
}

// sample output:
//
//  temp: 219, humi: 587
//  temp: 220, humi: 593
//  temp: 235, humi: 698
//  temp: 223, humi: 741
//  temp: 246, humi: 772
