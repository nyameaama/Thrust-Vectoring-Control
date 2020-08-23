// Basic 5x7 ASCII font, e.g. for OLED with copyBand support.

extern uint8_t const font5x7 [];

template< typename T, int S =6 >
struct Font5x7 {
    constexpr static int width = T::width;
    constexpr static int height = T::height;
    constexpr static int tabsize = 8 * 6;

    static void putc (int c) {
        switch (c) {
            case '\f': x = y = 0; T::clear(); return;
            case '\t': x += tabsize - x % tabsize; return;
            case '\r': x = 0; return;
            case '\n': x = width; break;
        }
        if (x + S > width) {
            x = 0;
            y += 8;
            if (y >= height)
                y = 0;
            // fill the new line with spaces
            for (int i = 0; i < width-5; i += S)
                T::copyBand(i, y, font5x7, 5);
        }
        if (c != '\n') {
            if (c < ' ' || c > 127)
                c = 127;
            uint8_t const* p = font5x7 + 5 * (c-' ');
            T::copyBand(x, y, p, 5);
            x += S;
        }
    }

    static uint16_t y, x;
};

template< typename T, int S >
uint16_t Font5x7<T,S>::y;

template< typename T, int S >
uint16_t Font5x7<T,S>::x;

// optional adapter to print scrolling text on pixel-oriented displays

template< typename LCD >
struct TextLcd : LCD {
    static void copyBand (int x, int y, uint8_t const* ptr, int len) {
        // not very efficient code, but it avoids a large buffer
        uint16_t col [8];
        for (int xi = 0; xi < len; ++xi) {
            uint8_t v = *ptr++;
            for (int i = 0; i < 8; ++i) {
                col[i] = v & 1 ? fg : bg;
                v >>= 1;
            }
            LCD::pixels(x+xi, y, col, 8);
        }

        // when in col 0: adjust v-scroll so the band is always at the bottom
        if (x == 0) {
            y += 8;
            LCD::vscroll(y < LCD::height ? y : 0);
        }
    }

    static uint16_t fg, bg;
};

template< typename LCD >
uint16_t TextLcd<LCD>::fg = 0xFFFF;

template< typename LCD >
uint16_t TextLcd<LCD>::bg;
