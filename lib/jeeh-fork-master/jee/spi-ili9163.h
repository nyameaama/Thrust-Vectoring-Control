// Driver for an ILI9163-based 128x128 LCD TFT display, connected over SPI
// see https://jeelabs.org/ref/ILI9163.pdf

template< typename SPI, typename DC >
struct ILI9163 {
    constexpr static int width = 128;
    constexpr static int height = 128;

    static void init () {
        DC::write(1);
        DC::mode(Pinmode::out);
        SPI::enable();

        static uint8_t const config [] = {
            // cmd, count, data bytes ...
    // https://github.com/Bodmer/TFT_eSPI/blob/master/TFT_Drivers/ILI9163_Init.h
            0x11,  0,    // Exit sleep mode
            0x3A,  1, 0x05, // Set pixel format
#if 0
            0x26,  1, 0x04, // Set Gamma curve 3
            0xF2,  1, 0x01, // Gamma adjustment enabled
            0xE0, 15, 0x3F, 0x25, 0x1C, 0x1E, 0x20, 0x12, 0x2A, 0x90,
                      0x24, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, // Pos Gamma
            0xE1, 15, 0x20, 0x20, 0x20, 0x20, 0x05, 0x00, 0x15,0xA7,
                      0x3D, 0x18, 0x25, 0x2A, 0x2B, 0x2B, 0x3A, // Neg Gamma
#endif
            0xB1,  2, 0x08, 0x08, // Frame rate control 1
            0xB4,  1, 0x07,       // Display inversion
            0xC0,  2, 0x0A, 0x02, // Power control 1
            0xC1,  1, 0x02,       // Power control 2
            0xC5,  2, 0x50, 0x5B, // Vcom control 1
            0xC7,  1, 0x40,       // Vcom offset
            0x36,  1, 0x88,       // Set address mode
            0x29,  0,
        };

        for (uint8_t const* p = config; p < config + sizeof config; ++p) {
            cmd(*p);
            int n = *++p;
            while (--n >= 0)
                SPI::transfer(*++p);
        }

        SPI::disable();
    }

    static void cmd (int v) {
        DC::write(0);
        SPI::transfer(v);
        DC::write(1);
    }

    static void out16 (int v) {
        SPI::transfer(v >> 8);
        SPI::transfer(v);
    }

    static void pixel (int x, int y, uint16_t rgb) {
        SPI::enable();

        cmd(0x2A);
        out16(y);
        out16(yEnd);

        cmd(0x2B);
        out16(x);
        out16(xEnd);

        cmd(0x2C);
        out16(rgb);

        SPI::disable();
    }

    static void pixels (int x, int y, uint16_t const* rgb, int len) {
        pixel(x, y, *rgb);

        SPI::enable();
        for (int i = 1; i < len; ++i)
            out16(rgb[i]);
        SPI::disable();
    }

    static void bounds (int xend =width-1, int yend =height-1) {
        xEnd = xend;
        yEnd = yend;
    }

    static void fill (int x, int y, int w, int h, uint16_t rgb) {
        bounds(x+w-1, y+h-1);
        pixel(x, y, rgb);

        SPI::enable();
        int n = w * h;
        while (--n > 0)
            out16(rgb);
        SPI::disable();
    }

    static void clear () {
        fill(0, 0, width, height, 0);
    }

    static void vscroll (int vscroll =0) {
        SPI::enable();
        cmd(0x37);
        out16(vscroll);
        SPI::disable();
    }

    static uint16_t xEnd, yEnd;
};

template< typename SPI, typename DC>
uint16_t ILI9163<SPI,DC>::xEnd = width-1;

template< typename SPI, typename DC>
uint16_t ILI9163<SPI,DC>::yEnd = height-1;
