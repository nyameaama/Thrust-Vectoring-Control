// Driver for an ILI9341-based 320x240 LCD TFT display, using 16b-mode FSMC
// see https://jeelabs.org/ref/ILI9341.pdf

template< uint32_t ADDR >
struct ILI9341 {
    constexpr static int width = 240;
    constexpr static int height = 320;

    static void init () {
        static uint8_t const config [] = {
            // cmd, count, data bytes ...
           0x3A, 1, 0x55, // pxiel format 16b
           0x36, 1, 0xB8, // orientation, bits 7..4 = MY MX MV ML
           0x11, 0,       // sleep off
           // TODO more setup is probably needed for proper colour gamma, etc
        };

        for (uint8_t const* p = config; p < config + sizeof config; ++p) {
            if (*p == 0xFF)
                wait_ms(*++p);
            else {
                cmd(*p);
                int n = *++p;
                while (--n >= 0)
                    out16(*++p);
            }
        }

        wait_ms(120);
        cmd(0x29);      // DISPON
    }

    static void cmd (int v) {
        MMIO16(ADDR-2) = v;
    }

    static void out16 (int v) {
        MMIO16(ADDR) = v;
    }

    static void pixel (int x, int y, uint16_t rgb) {
        cmd(0x2A);
        out16(y>>8);
        out16(y);
        out16(yEnd>>8);
        out16(yEnd);

        cmd(0x2B);
        out16(x>>8);
        out16(x);
        out16(xEnd>>8);
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
uint16_t ILI9341<ADDR>::xEnd = width-1;

template< uint32_t ADDR>
uint16_t ILI9341<ADDR>::yEnd = height-1;
