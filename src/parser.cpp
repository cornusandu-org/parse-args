#include "parseargs/parseargs.hpp"
#include "defs.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#define BUG_ON(condition, msg, ...) do { \
    if (condition) { \
        fprintf(stderr, msg " Unrecoverable.\n", __VA_ARGS__); \
        abort(); \
    } \
} while (0)

#if PARSEARGS_ATTEMPT_RECOVERY == 0

#define RECOVER_BUG_ON(condition, action, msg, ...)        \
do {                                                       \
    if (condition) {                                      \
        fprintf(stderr, msg " Recoverable.\n",             \
                ##__VA_ARGS__);                            \
        abort();                                          \
    }                                                      \
} while (0)

#else

#define RECOVER_BUG_ON(condition, action, msg, ...)        \
do {                                                       \
    if (condition) {                                      \
        fprintf(stderr, msg " Recoverable.\n",             \
                ##__VA_ARGS__);                            \
        action;                                           \
    }                                                      \
} while (0)

#endif

void ArgParser::parse_args(int argc, const char** argv) {
    if (argv == NULL) {
        fprintf(stderr, "Recieved NULL argv. Unrecoverable.\n");
        abort();
    }
    RECOVER_BUG_ON(argc == 0, return, "Recieved NULL argc (Are you sure you are passing it correctly?).");

    for (int i = 1; i < argc; i++) {
        const char* arg = argv[i];
        if (arg[0] == '-') {
            const char* name;
            if (arg[1] == '-')
                name = arg + 2;
            else
                name = arg + 1;
            
            for (BaseArgument *argument : this->arguments) {
                if (strcmp(argument->name, name) != 0)
                    continue;
                if (argument->req_parsing == FALSE) {
                    argument->parse(name);
                } else {
                    RECOVER_BUG_ON(i + 1 >= argc, ;, "Missing value for argument %s.", name);
                    const char* value = argv[i + 1];
                    argument->parse(value);
                    i++;
                }
            }
        } else {
            RECOVER_BUG_ON(1, ;, "Recieved positional argument (currently unsupported).");
        }
    }

    for (BaseArgument *arg : this->arguments) {
        if (arg->required == TRUE && arg->_was_parsed != TRUE) {
            BUG_ON(arg->_was_parsed == FLAG_UNKNOWN, "Required argument %s is in invalid state.", arg->name);
            BUG_ON(arg->_was_parsed == FALSE, "Required argument %s recieved no value.", arg->name);
        }
    }
}

void* ArgParser::get_arg(const char* name) {
    if (name == NULL) return NULL;

    for (BaseArgument* arg : this->arguments) {
        if (strcmp(arg->name, name) == 0) {
            return arg->get_data();
        }
    }

    return NULL;
}

FILENAME(parser.cpp);
LICENSE(MIT License);
LICENSE_TEXT(MIT License, parser);
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
