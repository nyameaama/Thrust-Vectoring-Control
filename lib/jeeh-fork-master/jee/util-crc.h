struct CRC16 {
    static uint16_t calculate (void const* ptr, int len, uint16_t sum =0xFFFF) {
        for (int i = 0; i < len; ++i) {
            uint8_t data = ((uint8_t const*) ptr)[i];
            sum = (uint16_t) ((sum>>4) ^ table[sum&0xF] ^ table[data&0xF]);
            sum = (uint16_t) ((sum>>4) ^ table[sum&0xF] ^ table[data>>4]);
        }
        return sum;
    }

    static uint16_t const table[];
};

uint16_t const CRC16::table[] = {
    0x0000, 0xCC01, 0xD801, 0x1400, 0xF001, 0x3C00, 0x2800, 0xE401,
    0xA001, 0x6C00, 0x7800, 0xB401, 0x5000, 0x9C01, 0x8801, 0x4400,
};
