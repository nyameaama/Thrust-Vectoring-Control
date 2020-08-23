// Example of how to write to built-in flash memory.

#include <jee.h>

UartDev< PinA<9>, PinA<10> > console;

int printf(const char* fmt, ...) {
    va_list ap; va_start(ap, fmt); veprintf(console.putc, fmt, ap); va_end(ap);
    return 0;
}

Flash mem;

int main () {
    // use a flash page well above the current code, i.e. @ 64K
    uint32_t* testAddr = (uint32_t*) 0x00010000;

    uint32_t x = testAddr[0], y = testAddr[1];
    printf("before %08x %08x\n", x, y);

    mem.erasePage(testAddr);

    printf("erased %08x %08x\n", testAddr[0], testAddr[1]);

    mem.write32(testAddr, x+1);
    mem.write32(testAddr+1, y-1);

    printf(" after %08x %08x\n", testAddr[0], testAddr[1]);

    return 0;
}

// sample output:
//
//  before 01234567 FEDCBA98
//  erased FFFFFFFF FFFFFFFF
//   after 01234568 FEDCBA97
