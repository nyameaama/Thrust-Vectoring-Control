#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#undef getc
#undef putc

#define main app_main
extern "C" int app_main ();

#define wait_ms(ms) vTaskDelay(ms / portTICK_PERIOD_MS)
#define ticks 0

extern void enableSysTick (uint32_t divider =0);

enum class Pinmode {
    in_float  = 0,
    //in_pullup = INPUT_PULLUP,
    out       = GPIO_MODE_OUTPUT,
    out_od    = GPIO_MODE_OUTPUT,
};

template<char port,int pin>
struct Pin {
    constexpr static int offset = port == 'B' ?  8 :  // PB 0..5 =>  8..13
                                  port == 'C' ? 14 :  // PC 0..7 => 14..21
                                                 0;   // PD 0..7 =>  0..7
    constexpr static int id = offset + pin;

    static void mode (Pinmode m) { gpio_set_direction(id, (int) m); }
    static int read () { return 0 /*digitalRead(id)*/; }
    static void write (int v) { gpio_set_level(id, v); }

    // shorthand
    operator int () const { return read(); }
    void operator= (int v) const { write(v); }

    static void toggle () { write(!read()); }
};

template< typename TX, typename RX >
class UartDev {
public:
    static bool init () { return true; }
    static void baud (int, int =0) {}
    static bool writable () { return true; }
    static void putc (int c) { putchar((char) c); }
    static bool readable () { return true; }
    static int getc () { return getchar(); }
};

#define UartBufDev UartDev
#define fullSpeedClock() 1
