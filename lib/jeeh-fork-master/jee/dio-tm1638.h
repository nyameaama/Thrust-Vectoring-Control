// Driver for the TM1638 led / 7-segment / keyboard controller.
// see https://jeelabs.org/ref/TM1638.pdf

// N and M are used to slow down the STB and CLK pins, 5/20 are ok for 72 MHz
template< typename STB, typename CLK, typename DIO, int N =5, int M =20 >
struct TM1638 {
    TM1638 () {
        stb = 1;
        stb.mode(Pinmode::out_od);
        clk.mode(Pinmode::out_od);
        dio.mode(Pinmode::out_od);
    }

    static void out (int v) {
        for (int i = 0; i < 8; ++i) {
            dio = v & 1;
            clk = 1;
            v >>= 1;
            clk = 0;
        }
    }

    static void send (uint8_t const* buf) {
        stb = 0;
        out(0x88);
        stb = 1;
        stb = 0;
        out(0xC0);
        for (int i = 0; i < 8; ++i) {
            out(buf[i]);
            out(0);
        }
        stb = 1;
    }

    static uint32_t receive () {
        stb = 0;
        out(0x42);
        dio = 1;
        uint32_t r = 0;
        for (int i = 0; i < 32; ++i) {
            clk = 1;
            r <<= 1;
            clk = 0;
            r |= dio;
        }
        stb = 1;
        return r;
    }

    static SlowPin<STB,N> stb;
    static SlowPin<CLK,M> clk;
    static DIO dio;
};

template< typename STB, typename CLK, typename DIO, int N, int M >
SlowPin<STB,N> TM1638<STB,CLK,DIO,N,M>::stb;

template< typename STB, typename CLK, typename DIO, int N, int M >
SlowPin<CLK,M> TM1638<STB,CLK,DIO,N,M>::clk;

template< typename STB, typename CLK, typename DIO, int N, int M >
DIO TM1638<STB,CLK,DIO,N,M>::dio;
