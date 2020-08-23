// Use the system tick timer to blink at 1 Hz.

#include <jee.h>

PinC<13> led;

int main () {
    enableSysTick();
    led.mode(Pinmode::out);

    while (true) {
        led = !led;

        wait_ms(500);
    }
}
