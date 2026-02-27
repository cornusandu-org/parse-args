#include "parseargs/parseargs.hpp"
#include "defs.hpp"
#include <cstring>
#include <cstdlib>
#include <cstdint>

template<>
void Argument<int>::parse(const char* data) {
    this->data = atoi(data);
}

template<>
void Argument<int>::free_data() {
    return;
}

template<>
Argument<int>::Argument(const Argument<int> &other) : Argument(other.name, other.required) {
    this->data = other.data;
}


template<>
void Argument<char*>::parse(const char* data) {
    uint64_t lenght = strlen(data);
    this->data = (char*)malloc(lenght + 1);
    memcpy(this->data, data, lenght + 1);
}

template<>
void Argument<char*>::free_data() {
    free(this->data);
    this->data = nullptr;
}

template<>
Argument<char*>::Argument(const Argument<char*> &other) : Argument(other.name, other.required) {
    uint64_t lenght = strlen(other.data);
    this->data = (char*) malloc(lenght + 1);
    memcpy(this->data, other.data, lenght + 1);
}

template class Argument<int>;
template class Argument<char*>;


FILENAME(argument.cpp);
LICENSE(MIT License);
LICENSE_TEXT(MIT License, argument);
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
