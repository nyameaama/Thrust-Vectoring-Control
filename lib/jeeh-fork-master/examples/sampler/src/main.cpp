// Sample project, used to compile and run the standalone examples in JeeH.
// The source is selected via "build_flags = -D <name>" in platformio.ini

#if EXAMPLE_ADC
#include "../../adc.cpp"
#endif

#if EXAMPLE_BLINK
#include "../../blink.cpp"
#endif

#if EXAMPLE_DHT22
#include "../../dht22.cpp"
#endif

#if EXAMPLE_FLASH
#include "../../flash.cpp"
#endif

#if EXAMPLE_HELLO
#include "../../hello.cpp"
#endif

#if EXAMPLE_I2C
#include "../../i2c.cpp"
#endif

#if EXAMPLE_IHEX
#include "../../ihex.cpp"
#endif

#if EXAMPLE_IOBOARD
#include "../../ioboard.cpp"
#endif

#if EXAMPLE_LOGO
#include "../../logo.cpp"
#endif

#if EXAMPLE_NOKIA
#include "../../nokia.cpp"
#endif

#if EXAMPLE_OLED
#include "../../oled.cpp"
#endif

#if EXAMPLE_PRINTF
#include "../../printf.cpp"
#endif

#if EXAMPLE_RF69RECV
#include "../../rf69recv.cpp"
#endif

#if EXAMPLE_SNAKE
#include "../../snake.cpp"
#endif

#if EXAMPLE_SPIFLASH
#include "../../spiflash.cpp"
#endif

#if EXAMPLE_SYSTICK
#include "../../systick.cpp"
#endif
