// Use RFM69 as spectrum waterfall display on an SPI-attached 320x240 LCD.
// See https://github.com/jeelabs/jeeh/tree/master/examples/waterfall

#include <jee.h>
#include <jee/spi-rf69.h>
#include <jee/spi-ili9325.h>
#include <jee/spi-ili9341.h>

UartDev< PinA<9>, PinA<10> > console;

int printf(const char* fmt, ...) {
    va_list ap; va_start(ap, fmt); veprintf(console.putc, fmt, ap); va_end(ap);
    return 0;
}

// this code can be used with two different types of TFT LCD boards
#if 1
SpiGpio< PinB<5>, PinB<4>, PinB<3>, PinB<0>, 1 > spiA;
ILI9325< decltype(spiA) > lcd;
#else
SpiGpio< PinB<5>, PinB<4>, PinB<3>, PinB<0> > spiA;
ILI9341< decltype(spiA), PinA<3> > lcd;
#endif

// controlling the radio takes most time, use hardware SPI @ 9 MHz for it
SpiHw< PinA<7>, PinA<6>, PinA<5>, PinA<4> > spiB;
RF69< decltype(spiB) > rf;

PinA<1> led;

// the range 0..255 is mapped as black -> blue -> yellow -> red -> white
// gleaned from the GQRX project by Moe Wheatley and Alexandru Csete (BSD, 2013)
// see https://github.com/csete/gqrx/blob/master/src/qtgui/plotter.cpp

static uint16_t palette [256];

static int setRgb (uint8_t r, uint8_t g, uint8_t b) {
    return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);  // rgb565
}

static void initPalette () {
    uint16_t* p = palette;
    for (int i = 0; i < 20; ++i)
        *p++ = setRgb(0, 0, 0);
    for (int i = 0; i < 50; ++i)
        *p++ = setRgb(0, 0, (140*i)/50);
    for (int i = 0; i < 30; ++i)
        *p++ = setRgb((60*i)/30, (125*i)/30, (115*i)/30+140);
    for (int i = 0; i < 50; ++i)
        *p++ = setRgb((195*i)/50+60, (130*i)/50+125, 255-(255*i)/50);
    for (int i = 0; i < 100; ++i)
        *p++ = setRgb(255, 255-(255*i)/100, 0);
    for (int i = 0; i < 6; ++i)
        *p++ = setRgb(255, (255*i)/5, (255*i)/5);
};

int main () {
    fullSpeedClock();
    led.mode(Pinmode::out);

    printf("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");

    // disable JTAG in AFIO-MAPR to release PB3, PB4, and PA15
    constexpr uint32_t afio = 0x40010000;
    MMIO32(afio + 0x04) |= 1 << 25;

    // rtp touch screen is on the same SPI bus, make sure it's disabled
    PinB<2> rtpcs;
    rtpcs = 1;
    rtpcs.mode(Pinmode::out);

    // the following is needed to use h/w SPI1 with pins B5..B3/A15 iso A7..A4
    //MMIO32(afio + 0x04) |= (1<<0);  // SPI1_REMAP in AFIO's MAPR

    spiA.init();
    lcd.init();
    // lcd.clear();

    initPalette();

    spiB.init();
    rf.init(63, 42, 8683);    // node 63, group 42, 868.3 MHz
    rf.writeReg(0x29, 0xFF);  // minimal RSSI threshold
    rf.writeReg(0x2E, 0xB8);  // sync size 7+1
    rf.writeReg(0x58, 0x29);  // high sensitivity mode
    rf.writeReg(0x19, 0x4C);  // reduced Rx bandwidth

    // dump all RFM69 registers
    printf("   ");
    for (int i = 0; i < 16; ++i)
        printf("%3x", i);
    for (int i = 0; i < 0x80; i += 16) {
        printf("\n%02x:", i);
        for (int j = 0; j < 16; ++j)
            printf(" %02x", rf.readReg(i+j));
    }
    printf("\n");

    rf.setMode(rf.MODE_RECEIVE);

    while (true) {
        uint32_t start = ticks;

        for (int y = 0; y < lcd.height; ++y) {
            // 868.3 MHz = 0xD91300, with 80 steps per pixel, a sweep can cover
            // 240*80*61.03515625 = 1,171,875 Hz, i.e. slightly under ± 600 kHz
            constexpr uint32_t middle = 0xD91300;  // 0xE4C000 for 915.0 MHz
            constexpr uint32_t step = 80;
            uint32_t first = middle - 120 * step;

            static uint16_t pixelRow [lcd.width];

            for (int x = 0; x < lcd.width; ++x) {
                // step to a new frequency
                uint32_t freq = first + x * step;
                rf.writeReg(rf.REG_FRFMSB,   freq >> 16);
                rf.writeReg(rf.REG_FRFMSB+1, freq >> 8);
                rf.writeReg(rf.REG_FRFMSB+2, freq);

                // take the average of 16 RSSI readings
                int sum = 0;
                for (int i = 0; i < 16; ++i)
                    sum += rf.readReg(rf.REG_RSSIVALUE);
                uint8_t rssi = ~sum >> 4;

                // add some grid points for reference
                if ((y & 0x1F) == 0 && x % 40 == 0)
                    rssi = 0xFF; // white dot
                pixelRow[x] = palette[rssi];
            }

            lcd.vscroll(y);                         // set scroll
            lcd.bounds(lcd.width-1, y);             // write one line
            lcd.pixels(0, y, pixelRow, lcd.width);  // update the display
        }

        printf("%d ms\n", ticks - start);
        led.toggle();
    }
}
