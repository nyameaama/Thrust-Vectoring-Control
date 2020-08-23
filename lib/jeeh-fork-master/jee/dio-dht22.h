// Readout of DHT11/DHT22 one-wire temperature/humidity sensors.
// see https://jeelabs.org/ref/DHT22.pdf

template< typename DAT, int CLK =72000000 >
struct DHT22 {
    static bool init () {
        DAT::mode(Pinmode::out_od);
        DAT::write(1);
        return true;
    }

    static bool read (int16_t& t, int16_t& h) {
        DAT::write(0);
        wait_ms(18);    // trigger a readout
        DAT::write(1);

        bool ok = wait(0) & wait(1) & wait(0);  // expect an ack pulse

        uint8_t buf [5];
        for (int i = 0; i < (int) sizeof buf; ++i)
            for (int j = 0; j < 8; ++j) {
                buf[i] <<= 1;
                ok &= wait(1);
                uint32_t t = clock.micros();
                ok &= wait(0);
                if (clock.micros() - t >= 50)
                    buf[i] |= 1;
            }

        if ((uint8_t) (buf[0] + buf[1] + buf[2] + buf[3]) != buf[4])
            return false;  // checksum is not valid

        // for DHT11, adjust readings using: h = (h>>8)*10; t = (t>>8)*10;
        // (optionally leave off the "*10" part to get integral values)
        h = (buf[0]<<8) + buf[1];
        t = (buf[2]<<8) + buf[3];

        if (t < 0) // if sub-zero, convert to negative int, i.e. 2s complement
            t = - (t & 0x7FFF);

        return ok;
    }

    static bool wait (int expected) {
        for (int i = 0; i < 50; ++i) {
            if (DAT::read() == expected)
                return true;
            clock.wait_us(2);
        }
        return false;
    }

    static SysTick<CLK> clock;
};

template< typename DAT, int CLK>
SysTick<CLK> DHT22<DAT,CLK>::clock;
