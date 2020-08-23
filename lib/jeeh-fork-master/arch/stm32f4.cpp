#include <jee.h>

uint16_t vrefint_cal = *((uint16_t*)VREFINT_CAL_ADDR);  // read VREFINT_CAL_ADDR memory location
uint16_t temp_30 = *((uint16_t*)TS_CAL1);
uint16_t temp_110 = *((uint16_t*)TS_CAL2);

void enableClkAt168MHz() {
    MMIO32(Periph::flash + 0x00) = 0x705; // flash acr, 5 wait states
    MMIO32(Periph::rcc + 0x00) = (1 << 16); // HSEON
    while (Periph::bit(Periph::rcc + 0x00, 17) == 0) {} // wait for HSERDY
    MMIO32(Periph::rcc + 0x08) = (4 << 13) | (5 << 10) | (1 << 0); // prescaler w/ HSE
    MMIO32(Periph::rcc + 0x04) = (7 << 24) | (1 << 22) | (0 << 16) | (168 << 6) | (4 << 0);
    Periph::bit(Periph::rcc + 0x00, 24) = 1; // PLLON
    while (Periph::bit(Periph::rcc + 0x00, 25) == 0) {} // wait for PLLRDY
    MMIO32(Periph::rcc + 0x08) = (4 << 13) | (5 << 10) | (2 << 0);
}

int fullSpeedClock() {
    constexpr uint32_t hz = 168000000;
    enableClkAt168MHz();                 // using external 8 MHz crystal
    enableSysTick(hz / 1000);              // systick once every 1 ms
    return hz;
}