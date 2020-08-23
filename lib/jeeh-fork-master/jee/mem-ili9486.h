// Driver for an ILI9486-based 480x320 LCD TFT display, using 16b-mode FSMC
// see https://jeelabs.org/ref/ILI9486.pdf

template< uint32_t ADDR >
struct ILI9486 {
    constexpr static int width = 320;
    constexpr static int height = 480;

    static void init () {
        static uint8_t const config [] = {
            // cmd, count, data bytes ...
            0xFF, 10,
#if 0
            0x3A, 1, 0x55, // pxiel format 16b
            0x36, 1, 0xB8, // orientation, bits 7..4 = MY MX MV ML
            // TODO more setup is probably needed for proper colour gamma, etc
#else
            0xF2, 9, 0x1C, 0xA3, 0x32, 0x02, 0xB2, 0x12, 0xFF, 0x12, 0x00,
            0xF1, 2, 0x36, 0xA4, 
            0xF8, 2, 0x21, 0x04, 
            0xF9, 2, 0x00, 0x08, 
            0xC0, 2, 0x0D, 0x0D, 
            0xC1, 2, 0x43, 0x00, 
            0xC2, 1, 0x00, 
            0xC5, 2, 0x00, 0x48, 
            0xE0, 15, 0x0F, 0x24, 0x1C, 0x0A, 0x0F, 0x08, 0x43, 0x88,
                      0x32, 0x0F, 0x10, 0x06, 0x0F, 0x07, 0x00,
            0xE1, 15, 0x0F, 0x38, 0x30, 0x09, 0x0F, 0x0F, 0x4E, 0x77,
                      0x3C, 0x07, 0x10, 0x05, 0x23, 0x1B, 0x00, 
            0x36, 1, 0xB8, //0x0A, 
            0x3A, 1, 0x55, 
#endif
            0x11, 0,       // sleep off
            0xFF, 120,
            0x29, 0        // DISPON
        };

        for (uint8_t const* p = config; p < config + sizeof config; ++p) {
            if (*p == 0xFF)
                wait_ms(*++p);
            else {
                cmd(*p);
                int n = *++p;
                while (--n >= 0)
                    out8(*++p);
            }
        }
    }

    static void cmd (int v) {
        MMIO8(ADDR-1) = v;
    }

    static void out8 (int v) {
        MMIO8(ADDR) = v;
    }

    static void out16 (int v) {
        MMIO8(ADDR) = v>>8;
        MMIO8(ADDR) = v;
    }

    static void pixel (int x, int y, uint16_t rgb) {
        cmd(0x2A);
        out16(y);
        out16(yEnd);

        cmd(0x2B);
        out16(x);
        out16(xEnd);

        cmd(0x2C);
        out16(rgb);
    }

    static void pixels (int x, int y, uint16_t const* rgb, int len) {
        pixel(x, y, *rgb);

        for (int i = 1; i < len; ++i)
            out16(rgb[i]);
    }

    static void bounds (int xend =width-1, int yend =height-1) {
        xEnd = xend;
        yEnd = yend;
    }

    static void fill (int x, int y, int w, int h, uint16_t rgb) {
        bounds(x+w-1, y+h-1);
        pixel(x, y, rgb);

        int n = w * h;
        while (--n > 0)
            out16(rgb);
    }

    static void clear () {
        fill(0, 0, width, height, 0);
    }

    static void vscroll (int vscroll =0) {
        cmd(0x37);
        out16(vscroll>>8);
        out16(vscroll);
    }

    static uint16_t xEnd, yEnd;
};

template< uint32_t ADDR>
uint16_t ILI9486<ADDR>::xEnd = width-1;

template< uint32_t ADDR>
uint16_t ILI9486<ADDR>::yEnd = height-1;
