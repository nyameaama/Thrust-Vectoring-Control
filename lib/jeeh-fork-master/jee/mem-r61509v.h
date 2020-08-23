// Driver for an R61509V-based 400x240 LCD TFT display, using 16b-mode FSMC
// tested with a "PZ6806L" board, e.g. https://www.ebay.com/itm/371993346994
// see https://jeelabs.org/ref/R61509V.pdf

// TODO vertical scrolling has been disabled, see below

template< uint32_t REG, uint32_t DAT >
struct R61509V {
    constexpr static int width = 240;
    constexpr static int height = 400;

    static void init () {
        static uint16_t const config [] = {  // R61509V_CPT3.0
            0x000, 0x0000,  9999, 10,
            0x400, 0x6200, 0x008, 0x0808, 0x300, 0x0005, 0x301, 0x4C06,
            0x302, 0x0602, 0x303, 0x050C, 0x304, 0x3300, 0x305, 0x0C05,
            0x306, 0x4206, 0x307, 0x060C, 0x308, 0x0500, 0x309, 0x0033,
            0x010, 0x0014, 0x011, 0x0101, 0x012, 0x0000, 0x013, 0x0001,
            0x100, 0x0330, 0x101, 0x0247, 0x103, 0x1000, 0x280, 0xDE00,
            0x102, 0xD1B0,  9999, 10,     0x001, 0x0100, 0x002, 0x0100,
            0x003, 0x1038, 0x009, 0x0001, 0x00C, 0x0000, 0x090, 0x8000,
            0x00F, 0x0000, 0x210, 0x0000, 0x211, 0x00EF, 0x212, 0x0000,
            0x213, 0x018F, 0x500, 0x0000, 0x501, 0x0000, 0x502, 0x005F,  
            0x401, 0x0003, 0x404, 0x0000,  9999, 10,     0x007, 0x0100,
              999, 10,     0x200, 0x0000, 0x201, 0x0000, 9999, 10,
            0x202, 0x0000, 55555
        };
    
        for (uint16_t const* p = config; p[0] != 55555; p += 2)
            if (p[0] == 9999)
                wait_ms(p[1]);
            else
                write(p[0], p[1]);
    }

    static void write (int reg, int val) {
        MMIO16(REG) = reg;
        out16(val);
    }

    static void out16 (int v) {
        MMIO16(DAT) = v;
    }

    static void pixel (int x, int y, uint16_t rgb) {
        write(0x200, x);
        write(0x210, x);
        write(0x201, y);
        write(0x212, y);
        write(0x202, rgb);
    }

    static void pixels (int x, int y, uint16_t const* rgb, int len) {
        pixel(x, y, *rgb);

        for (int i = 1; i < len; ++i)
            out16(rgb[i]);
    }

    static void bounds (int xend =width-1, int yend =height-1) {
        write(0x211, xend);
        write(0x213, yend);
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
        // FIXME scrolling is wrong, due to 432-line mem vs 400-line display?
        //write(0x404, vscroll);
    }
};
