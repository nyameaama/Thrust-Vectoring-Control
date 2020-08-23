// DCF77 time signal decoder, see https://en.wikipedia.org/wiki/DCF77

struct DCF77 {
    static constexpr int period = 45; // ms, call process() this often

    uint32_t signal = 0;
    uint64_t message = 0;
    uint8_t mm, hh, dy, mo, yr, dow, dst;

    bool process (bool state) {
        signal <<= 1;
        signal |= state;
                                     //  9876543210
        constexpr uint32_t pulseMask = 0b0011100001;
        constexpr uint32_t pulseBits = 0b0001100000;
        constexpr uint32_t pulseData = 0b0000001000;

        if ((signal & pulseMask) == pulseBits) {
            bool decodedBit = (signal & pulseData) != 0;
            message >>= 1;
            message |= ((uint64_t) decodedBit) << 58;
        }
                                     //  2......1.........0.........
                                     //  654321098765432109876543210
        constexpr uint32_t gapMask   = 0b001110000100000000000000011;
        constexpr uint32_t gapBits   = 0b000110000000000000000000000;

        return (signal & gapMask) == gapBits;
    }

    bool decode (bool bcd =false) {
        if ((message & 0x100001) == 0x100000 && // b20 must be 1, b0 must be 0
                parityOk(36, 58) && parityOk(29, 35) && parityOk(21, 28)) {
            mm = (message >> 21) & 0x7F;
            hh = (message >> 29) & 0x3F;
            dy = (message >> 36) & 0x3F;
            mo = (message >> 45) & 0x1F;
            yr = (message >> 50) & 0xFF;
            if (!bcd) {
                mm -= 6 * (mm/16);
                hh -= 6 * (hh/16);
                dy -= 6 * (dy/16);
                mo -= 6 * (mo/16);
                yr -= 6 * (yr/16);
            }
            dow = (message >> 42) & 0x07;
            dst = (message >> 17) & 0x01;
            return yr <= 99 && mo <= 12 && dy <= 31 && hh <= 23 && mm <= 59;
        }
        return false;
    }

    bool parityOk (int loBit, int hiBit) {
        bool ok = true;
        for (int i = loBit; i <= hiBit; ++i)
            if ((message >> i) & 1)
                ok = !ok;
        return ok;
    }
};
