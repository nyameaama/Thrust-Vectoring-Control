// Intel hex parser, the template argument specifies maximum data bytes.
// see https://en.wikipedia.org/wiki/Intel_HEX

template< int MAX >
struct IntelHex {
    enum { START, RECLEN, OFFSET, OFFSET2, RECTYP, DATA, CHKSUM };

    void init () {
        state = START;
        count = check = 0;
    }

    // return true when the parse is done, with check == 0 if no errors
    // else if state == 6, it's a checksum error, all data has been read
    bool parse (int c) {
        int pos;

        if ('0' <= c && c <= '9')
            c -= '0';
        else if ('A' <= c && c <= 'F')
            c -= 'A' - 10;
        else {
            check = 1;
            return true;
        }

        value = (value<<4) | c;
        if (++count & 1)
            return false;
        check += value;

        switch (++state) {
            case RECLEN:  len = value;
                          break;
            case OFFSET:
            case OFFSET2: addr = value;
                          break;
            case RECTYP:  type = value;
                          if (len == 0)
                              ++state; // no DATA
                          break;
            case DATA:    pos = count/2 - 5;
                          if (pos < MAX)
                              data[pos] = value;
                          if (pos + 1 < len)
                              --state; // more DATA
                          break;
            default:      check = 1;
                          // fall through
            case CHKSUM:  return true;
        }

        return false;
    }

    uint16_t value;
    uint16_t count;
    uint16_t addr;
    uint8_t check;
    uint8_t len;
    uint8_t state;
    uint8_t type;
    uint8_t data [MAX];
};
