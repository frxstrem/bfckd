# bfckd

**bfckd** is a simple Brainfuck interpreter, written in C++.

## Building bfckd (with GCC)

Build **bfckd** with the command <code>g++ -o bfckd bfckd.cpp *options*</code>.

Possible build options include:

 * <code>-DTAPE_SIZE=*N*</code>: Brainfuck tape wraps around after *N* bytes.
 * <code>-DDEBUG_ENABLE=*S*</code>: Enable (`-DDEBUG_ENABLE=1`) or disable (`-DDEBUG_ENABLE=0`) the debug character `#`.
 * <code>-DDEBUG_WIDTH=*N*</code>: The debug character displays *N* extra cells before and after the current cell.

## Running bfckd

bfckd expects a Brainfuck program, followed by an exclamation mark (`!`) and then the program's input:

    ,[.[-],]!Hello World

This runs the program `,[.[-],]` with the input `Hello World`. The program runs immediately after `!` is read, and does
not depend on input being immediately ready.

The tape is a wrapping tape: after some set number of cells (65536 by default), the tape repeats. Each cell is 8 bits
wide, and can contain any integer in the range 0-255. By default, all cells are initialized to 0.

The program accepts unmatched `[` and `]`:

 * If a `[` is encountered with no matching `]`, the loop will only run once (at most).
 * If a `]` is encountered with no matching `[`, the program will skip to the first instruction.

The input operator `,` will read exactly one byte from standard input, and put it in the current cell. If there is no data
available, it will wait indefinitely until data becomes available. If an end-of-file is encountered, the cell is
left unchanged. (It is therefore recommended that a cell is cleared with `[-]` before reading or set to some known value,
so that input can be properly distinguished from end-of-file.)
