// Driver for an ILI9325-based 320x240 LCD TFT display, connected over SPI
// tested with http://www.hotmcu.com/x-p-121.html
// see https://jeelabs.org/ref/ILI9325.pdf

template< typename SPI >
struct ILI9325 {
    constexpr static int width = 240;
    constexpr static int height = 320;

    static void init () {
        static uint16_t const config [] = {
            0xE7, 0x0010, 0x00, 0x0001, 0x01, 0x0100, 0x02, 0x0700,
            0x03, 0x1038, 0x04, 0x0000, 0x08, 0x0207, 0x09, 0x0000,
            0x0A, 0x0000, 0x0C, 0x0001, 0x0D, 0x0000, 0x0F, 0x0000,
            0x10, 0x0000, 0x11, 0x0007, 0x12, 0x0000, 0x13, 0x0000,
             999,     50, 0x10, 0x1590, 0x11, 0x0227,  999,     50,
            0x12, 0x009C,  999,     50, 0x13, 0x1900, 0x29, 0x0023,
            0x2B, 0x000E,  999,     50, 0x20, 0x0000, 0x21, 0x0000,
             999,     50, 0x30, 0x0007, 0x31, 0x0707, 0x32, 0x0006,
            0x35, 0x0704, 0x36, 0x1F04, 0x37, 0x0004, 0x38, 0x0000,
            0x39, 0x0706, 0x3C, 0x0701, 0x3D, 0x000F,  999,     50,
            0x50, 0x0000, 0x51, 0x00EF, 0x52, 0x0000, 0x53, 0x013F,
            0x60, 0xA700, 0x61, 0x0003, 0x6A, 0x0000, 0x80, 0x0000,
            0x81, 0x0000, 0x82, 0x0000, 0x83, 0x0000, 0x84, 0x0000,
            0x85, 0x0000, 0x90, 0x0010, 0x92, 0x0000, 0x93, 0x0003,
            0x95, 0x0110, 0x97, 0x0000, 0x98, 0x0000, 0x07, 0x0133,
            0x20, 0x0000, 0x21, 0x0000, 9999
        };
        
        for (uint16_t const* p = config; p[0] != 9999; p += 2)
            if (p[0] == 999)
                wait_ms(p[1]);
            else
                write(p[0], p[1]);
    }

    static void write (int reg, int val) {
        SPI::enable();
        SPI::transfer(0x70);
        out16(reg);
        SPI::disable();
        SPI::enable();
        SPI::transfer(0x72);
        out16(val);
        SPI::disable();
    }

    static void out16 (int v) {
        SPI::transfer(v >> 8);
        SPI::transfer(v);
    }

    static void pixel (int x, int y, uint16_t rgb) {
        write(0x20, x);
        write(0x50, x);
        write(0x21, y);
        write(0x52, y);
        write(0x22, rgb);
    }

    static void pixels (int x, int y, uint16_t const* rgb, int len) {
        pixel(x, y, *rgb);

        SPI::enable();
        SPI::transfer(0x72);
        for (int i = 1; i < len; ++i)
            out16(rgb[i]);
        SPI::disable();
    }

    static void bounds (int xend =width-1, int yend =height-1) {
        write(0x51, xend);
        write(0x53, yend);
    }

    static void fill (int x, int y, int w, int h, uint16_t rgb) {
        bounds(x+w-1, y+h-1);
        pixel(x, y, rgb);

        SPI::enable();
        SPI::transfer(0x72);
        int n = w * h;
        while (--n > 0)
            out16(rgb);
        SPI::disable();
    }

    static void clear () {
        fill(0, 0, width, height, 0);
    }

    static void vscroll (int vscroll =0) {
        write(0x6A, vscroll);
    }
};
