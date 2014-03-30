/**
 * bfckd -- A Brainfuck implementation.
 *
 * Version 1.0 (March 30, 2014)
 *
 * Written by Fredrik Østrem <frx.apps@gmail.com>
 *
 * -------------------------------------------------------------------------------
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Fredrik Østrem
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Tape size (tape wraps around after this many cells)
#ifndef TAPE_SIZE
#define TAPE_SIZE 65536
#endif

// Enable debug symbol ('#')
#ifndef DEBUG_ENABLE
#define DEBUG_ENABLE 0
#endif

// Width of cell range to display when debugging
#ifndef DEBUG_WIDTH
#define DEBUG_WIDTH 2
#endif

typedef unsigned char bf_word;

int main() {
    std::vector<char> code;
    std::vector<bf_word> tape(TAPE_SIZE, 0);
    std::stack<size_t> loop_stack;

    // Read Brainfuck code until '!' is found
    char ch;
    while(cin >> ch && ch != '!') {
        if(ch == '+' || ch == '-' || ch == '<' || ch == '>' || ch == '[' || ch == ']' || ch == '.' || ch == ',' || ch == '#')
            code.push_back(ch);
    }

    // Run Brainfuck code
    int ptr = 0;
    cin >> noskipws;
    for(size_t pc = 0; pc < code.size(); pc++) {
        switch(code[pc]) {
            case '+':
                tape[ptr]++;
                break;

            case '-':
                tape[ptr]--;
                break;

            case '>':
                ptr = (ptr + 1) % TAPE_SIZE;
                break;

            case '<':
                ptr = (ptr + TAPE_SIZE - 1) % TAPE_SIZE;
                break;

            case '[':
                if(tape[ptr]) {
                    loop_stack.push(pc);
                } else {
                    int cc = 1;
                    while(cc > 0 && ++pc < code.size()) {
                        if(code[pc] == '[')
                            cc++;
                        else if(code[pc] == ']')
                            cc--;
                    }
                }
                break;

            case ']':
                if(tape[ptr]) {
                    if(loop_stack.empty())
                        pc = 0;
                    else
                        pc = loop_stack.top();
                } else {
                    loop_stack.pop();
                }
                break;

            case '.':
                cout << (char)tape[ptr];
                break;

            case ',':
                {
                    char tmp;
                    if(cin >> tmp)
                        tape[ptr] = tmp;
                }
                break;

#if DEBUG_ENABLE
            case '#':
                for(int i = DEBUG_WIDTH; i > 0; i--)
                    cerr << (int)tape[(ptr + TAPE_SIZE - i) % TAPE_SIZE] << " ";
                cerr << "[ " << (int)tape[ptr] << " ] ";
                for(int i = 1; i <= DEBUG_WIDTH; i++)
                    cerr << (int)tape[(ptr + i) % TAPE_SIZE] << " ";
                break;
#endif
        }
    }
}
