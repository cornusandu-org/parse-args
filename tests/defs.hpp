#pragma once

#include <cstdio>
#include <cstdlib>
#include <chrono>

extern int test_successes;
extern int test_fails;
extern char test_tofail;

#if defined(_WIN32)
#  define NULL_DEVICE "NUL"
#else
#  define NULL_DEVICE "/dev/null"
#endif

static FILE *saved_stderr = NULL;

void suppress_err_begin(void) {
    fflush(stderr);

    saved_stderr = stderr;

    freopen(NULL_DEVICE, "w", stderr);
}

void suppress_stderr_end(void) {
    fflush(stderr);

    if (saved_stderr) {
        freopen(NULL_DEVICE, "w", stderr);
        stderr = saved_stderr;
        saved_stderr = NULL;
    }
}


#define ASSERT(condition) do { \
    if (!(condition)) { \
        return 1; \
    } \
} while(0)

#define ADD_TEST(name, ...) do { \
    printf("=> Running test: %s", name); \
    auto start = std::chrono::high_resolution_clock::now(); \
    int result = [](){__VA_ARGS__; return 0;}(); \
    auto end = std::chrono::high_resolution_clock::now(); \
    auto dt = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); \
    if (result == 1) { \
        printf("\r=> Test failed: %s (%lli µs)         \n", name, dt); \
        test_fails++; \
        test_tofail = 1; \
    } else { \
        printf("\r=> Test passed: %s (%lli µs)          \n", name, dt); \
        test_successes++; \
    } \
} while(0)

#define END() return 0




static std::chrono::_V2::system_clock::time_point all_tests_start;

#define BEGIN_TESTS() do { \
    printf("\n--- Running Unit Tests ---\n\n\n"); \
    all_tests_start = std::chrono::high_resolution_clock::now(); \
    test_tofail = 0; \
    test_successes = 0; \
    test_fails = 0; \
} while(0)

#define END_TESTS() do { \
    auto end = std::chrono::high_resolution_clock::now(); \
    auto dt = std::chrono::duration_cast<std::chrono::microseconds>(end - all_tests_start).count(); \
    auto dt2 = std::chrono::duration_cast<std::chrono::milliseconds>(end - all_tests_start).count(); \
    printf("\n\n\nFinished running tests in %lli µs (%lli ms).\n", dt, dt2); \
    if (test_tofail == 1) exit(1); \
    else exit(0); \
} while(0)




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