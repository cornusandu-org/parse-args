#include "defs.hpp"
#include "../parseargs/parseargs.hpp"

#include "../src/defs.hpp"

int test_successes;
int test_fails;
char test_tofail;

int aborted = 0;

extern "C" void abort() {
    aborted = 1;
    return;
}

void tests() {
    ADD_TEST("1/1 arguments", {
        int argc = 3;
        const char* argv[] = {"./bin", "--val", "3"};
        ArgParser parser;
        Argument<int> arg1 = Argument<int>("val", true);
        parser.push_arg(arg1);
        parser.parse_args(argc, argv);
        int val = *(int*)parser.get_arg("val");
        ASSERT(val == 3);
    });
    
    ADD_TEST("0/0 arguments", {
        int argc = 1;
        const char* argv[] = {"./bin"};
        ArgParser parser;
        parser.parse_args(argc, argv);
        int *v = (int*)parser.get_arg("testval");
        ASSERT(v == NULL);
    });

    ADD_TEST("0/1 arguments (expect abort)", {
        aborted = 0;
        int argc = 1;
        const char* argv[] = {"./bin"};
        Argument<int> arg = Argument<int>("value", true);
        ArgParser parser;
        parser.push_arg(arg);
        suppress_err_begin();
        parser.parse_args(argc, argv);
        suppress_stderr_end();
        ASSERT(aborted == 1);
    });
}

int main() {
    BEGIN_TESTS();
    tests();
    END_TESTS();
}

FILE(run_tests);
COPYRIGHT(cornusandu, 2026);
LICENSE(MIT License);
LICENSE_TEXT(MIT License);



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