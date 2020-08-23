// Demo of the Intel HEX parser/decoder.

#include <jee.h>
#include <jee/text-ihex.h>

UartDev< PinA<9>, PinA<10> > console;

int printf(const char* fmt, ...) {
    va_list ap; va_start(ap, fmt); veprintf(console.putc, fmt, ap); va_end(ap);
    return 0;
}

static void testIntelHex (const char* s) {
    printf("<%s>\n", s);

    IntelHex<32> hex;
    if (*s++ == ':')
        hex.init();

    while (*s)
        if (hex.parse(*s++)) {
            printf("check %3d count %2d len %2d state %d type %d addr $%04x\n",
                hex.check, hex.count, hex.len, hex.state, hex.type, hex.addr);
            if (hex.state == hex.CHKSUM) {
                printf("\t  ");
                for (int i = 0; i < hex.len; ++i)
                    printf("%02x", hex.data[i]);
                printf("\n");
            }
            if (*s)
                printf("not fully parsed: %s\n", s);
            return;
        }

    printf("huh?");
}

int main () {
    testIntelHex(":020000040800F2");
    testIntelHex(":100000008C030020A34D0000B7470000B747000055");
    testIntelHex(":104F70001C00002024000020180000200800002051");
    testIntelHex(":044F8000BA4E000025");
    testIntelHex(":0400000508000000EF");
    testIntelHex(":00000001FF");

    return 0;
}

// output:
//
//  <:020000040800F2>
//  check   0 count 14 len  2 state 6 type 4 addr $0000
//            0800
//  <:100000008C030020A34D0000B7470000B747000055>
//  check   0 count 42 len 16 state 6 type 0 addr $0000
//            8C030020A34D0000B7470000B7470000
//  <:104F70001C00002024000020180000200800002051>
//  check   0 count 42 len 16 state 6 type 0 addr $4F70
//            1C000020240000201800002008000020
//  <:044F8000BA4E000025>
//  check   0 count 18 len  4 state 6 type 0 addr $4F80
//            BA4E0000
//  <:0400000508000000EF>
//  check   0 count 18 len  4 state 6 type 5 addr $0000
//            08000000
//  <:00000001FF>
//  check   0 count 10 len  0 state 6 type 1 addr $0000
//  
