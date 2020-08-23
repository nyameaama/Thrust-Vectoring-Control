/*
    This is a very very basic command parser. Just enough to recognise a few
    different commands, and pass up to 10 numeric arguments to them.

    The parser is given input characters as they come in, the return value is
    either 0 if more input is needed, or the first character of the command.
    For single-char commands (any ASCII char greater than '$'), just dispatch
    as needed - for longer command names, the rest of the command will need to
    be read in and looked-up separately, i.e. somewhere outside this parser.

    Commands are of the form:
        command
        number whitespace command
        number whitespace number whitespace command
        (etc... up to 10 numbers)
    Whitespace is anything with an ASCII value of 0x20 or less, incl newlines.

    Numbers are normally in base-10, or in base-16 when preceded by a "$".

    The last argument is in args[argc-1], argc will be 0 if there are no args.

    The '?' command is a special case: it doesn't clear the stack for next use.
    See below for an example how it can be used to show the values on the stack
    without clearing it. Here is a usage example, including output:

        1 2 3 ?     <- input
         1 2 3      <- printed out
        4 ?         <- input
         1 2 3 4    <- printed out
        command     <- input, this command will receive the 4 args

    Commands are immediate (no <return> needed), and there's no line editing.

    The '#' character will clear the argument stack.
*/

struct Command {
    int args [10];
    int8_t argc = 0;
    char state = 0;

    char parse (int c) {
        if (state > 2) {
            argc = 0;
            state = 0;
        }

        if (c <= ' ')
            return state = 0;

        switch (state) {
            case 0:  // any
                if (c == '#') {
                    argc = 0;
                    return 0;
                }
                if (c == '$') {
                    args[argc++] = 0;
                    state = 1;
                    return 0;
                }
                if ('0' <= c && c <= '9') {
                    args[argc++] = c - '0';
                    state = 2;
                    return 0;
                }
                if (c == '?')
                    return '?'; // don't reset state to clear stack
                if (c > '$')
                    return state = c; // any other char is (start of) a command
                break;
            case 1:  // hex
                if ('0' <= c && c <= '9') {
                    args[argc-1] = args[argc-1]<<4 | (c-'0');
                    return 0;
                }
                if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'f')) {
                    args[argc-1] = args[argc-1]<<4 | ((c+9)&15);
                    return 0;
                }
                break;
            case 2:  // dec
                if ('0' <= c && c <= '9') {
                    args[argc-1] = args[argc-1]*10 + (c-'0');
                    return 0;
                }
                break;
        }

        return state = '!';
    }
};
