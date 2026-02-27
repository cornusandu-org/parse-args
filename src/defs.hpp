#define SLASH /
#define COMMENT SLASH*

#define ENDCOMMENT *SLASH

#define CONCAT_(a, b) a##b
#define CONCAT(a, b) CONCAT_(a, b)

#define FILENAME(x) \
        asm(".section .rodata\n" \
        ".ascii \"Filename: " #x "\"\n" \
        ".byte 0\n" \
        ".previous");

#define LICENSE(x) \
        asm(".section .rodata\n" \
        ".ascii \"License: " #x "\"\n" \
        ".byte 0\n" \
        ".previous");

#define COPYRIGHT(author, year) \
        asm(".section .rodata\n" \
        ".byte 0xA9\n" \
        ".ascii \" Copyright " #author ", " #year "\"\n" \
        ".byte 0\n" \
        ".previous");

#define LICENSE_TEXT(x, file) extern "C" const char* CONCAT(license_, file)() {return #x;}; \
static const char* (*volatile keep_license)(void) = CONCAT(license_, file)

#undef SLASH
#undef COMMENT


#define autocr(...) LICENSE(MIT License); \
COPYRIGHT(cornusandu, 2026);


// MIT License
// 
// Copyright (c) 2026 cornusandu
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
