// Driver for the Sensirion SHT21/25 sensors, connected over I2C
// see https://jeelabs.org/ref/SHT21.pdf

template< typename I2C, int addr =0x40 >
struct SHT2x {
    static void init () {
        I2C::start(addr<<1);
        I2C::write(0xFE); // reset
        I2C::stop();

        wait_ms(15);
    }

    uint16_t reading (int type) {
        I2C::start(addr<<1);
        I2C::write(type);
        I2C::stop();

        switch (type) {
            case 0xF3: wait_ms(85); break;
            case 0xF5: wait_ms(29); break;
        }

        I2C::start((addr<<1)+1);
        uint16_t v = I2C::read(false) << 8;
        v |= I2C::read(false);
        I2C::read(true); // ignore checksum
        I2C::stop();

        return v & ~0x3;
    }

    int16_t temp100 () {
        return (17572 * reading(0xF3) >> 16) - 4685;
    }

    int16_t humidity10 () {
        return (1250 * reading(0xF5) >> 16) - 60;
    }
};
