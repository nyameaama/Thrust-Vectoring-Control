// Driver for the PCD8544, as used in the 84x48 Nokia 5110 graphics LCD.
// see https://jeelabs.org/ref/PCD8544.pdf

template< typename C, typename I, typename D, typename E, typename R >
struct PCD8544 {
    constexpr static int width = 84;
    constexpr static int height = 48;

    static void init (int contrast =0x38) {
        ck.mode(Pinmode::out);
        in.mode(Pinmode::out);
        dc.mode(Pinmode::out);
        en.mode(Pinmode::out);
        rs.mode(Pinmode::out);

        en = 1;
        ck = 0;
        rs = 1;

        cmd(0x21);  // extended mode
        cmd(0x04);  // temp coeff
        cmd(0x14);  // bias 4
        cmd(0x80 | contrast);
        cmd(0x20);  // normal mode
        cmd(0x0C);  // display control normal
    }

    static void cmd (int v) {
        en = 0;
        write(v);
        en = 1;
    }

    static void clear () {
        // this is not needed, since the entire graphics ram will be cleared
        // in horizontal mode, writes will wrap no matter where they started
        //
        cmd(0x40);
        cmd(0x80);

        dc = 1;
        en = 0;
        for (int i = 0; i < width*height/8; ++i)
            write(0);
        en = 1;
        dc = 0;
    }

    // data is written in "bands" of 8 pixels high, bit 0 is the topmost line
    static void copyBand (int x, int y, uint8_t const* ptr, int len) {
        cmd(0x40 + (y >> 3));
        cmd(0x80 + x);
        dc = 1;
        en = 0;
        for (int i = 0; i < len; ++i)
            write(ptr[i]);
        en = 1;
        dc = 0;
    }

    static void write (int v) {
        for (int i = 0; i < 8; ++i) {
            in = v & 0x80;
            in = v & 0x80;
            ck = 1;
            v <<= 1;
            ck = 0;
        }
    }

    static C ck;
    static I in;
    static D dc;
    static E en;
    static R rs;
};

template< typename C, typename I, typename D, typename E, typename R >
C PCD8544<C,I,D,E,R>::ck;

template< typename C, typename I, typename D, typename E, typename R >
I PCD8544<C,I,D,E,R>::in;

template< typename C, typename I, typename D, typename E, typename R >
D PCD8544<C,I,D,E,R>::dc;

template< typename C, typename I, typename D, typename E, typename R >
E PCD8544<C,I,D,E,R>::en;

template< typename C, typename I, typename D, typename E, typename R >
R PCD8544<C,I,D,E,R>::rs;
