// Driver for Fujitsu MB85RS2MTA spi fram memory
// see https://jeelabs.org/ref/MB85RS2MTA.pdf

template< typename SPI >
struct Fram {
    static void init () {
		SPI::init();
		SPI::enable();
		SPI::transfer(0x06);  // write enable
		SPI::disable();
	}

    static uint32_t devId () {
		SPI::enable();
		SPI::transfer(0x9F);  // read id
		uint32_t v = SPI::transfer(0) << 24;
		v |= SPI::transfer(0) << 16;
		v |= SPI::transfer(0) << 8;
		v |= SPI::transfer(0);
		SPI::disable();
		return v;
	}

	static void read (uint32_t addr, uint8_t* buf, int len) {
		SPI::enable();
		SPI::transfer(0x03);  // read
		SPI::transfer(addr >> 16);
		SPI::transfer(addr >> 8);
		SPI::transfer(addr);
		while (len-- > 0)
			*buf++ = SPI::transfer(0);
		SPI::disable();
	}

	static void write (uint32_t addr, uint8_t const* buf, int len) {
		SPI::enable();
		SPI::transfer(0x02);  // write
		SPI::transfer(addr >> 16);
		SPI::transfer(addr >> 8);
		SPI::transfer(addr);
		while (len-- > 0)
			SPI::transfer(*buf++);
		SPI::disable();
	}
};
