#pragma once

#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <cstdio>


#ifndef PARSEARGS_ATTEMPT_RECOVERY
#define PARSEARGS_ATTEMPT_RECOVERY 0
#endif


using flag_t = unsigned char;

#define TRUE ((flag_t)1)
#define FALSE ((flag_t)0)
#define FLAG_UNKNOWN ((flag_t)2)

class BaseArgument {
    public:
    char* name = NULL;
    flag_t required = 1;
    flag_t req_parsing = FLAG_UNKNOWN;
    flag_t _was_parsed = FALSE;
    virtual ~BaseArgument() = default;
    virtual void parse(const char* data) = 0;
    virtual void* get_data() = 0;
};

template <typename T>
class Argument : public BaseArgument {
    public:
        inline Argument(const char* name, flag_t required) {
            if (name == NULL) {
                fprintf(stderr, "Error: Recieved NULL pointer for argument name. Unrecoverable.\n");
            }
            uint64_t lenght = strlen(name);
            this->name = (char*) malloc(lenght + 1);
            memcpy(this->name, name, lenght + 1);
            this->required = required;
            this->data = NULL;
        }

        Argument(const Argument<T> &other);
    
        inline ~Argument() override {
            if (this->name == nullptr)
                return;
            free(this->name);
            this->name = nullptr;
            free_data();
        }

        T data;

    void parse(const char* data) override;
    inline void* get_data() {
        return &this->data;
    }
    private:
        void free_data();
};

template<>
void Argument<int>::parse(const char* data);
template<>
Argument<int>::Argument(const Argument<int> &other);
template<>
void Argument<int>::free_data();

template<>
void Argument<char*>::parse(const char* data);
template<>
Argument<char*>::Argument(const Argument<char*> &other);
template<>
void Argument<char*>::free_data();

extern template class Argument<int>;
extern template class Argument<char*>;


#include <vector>

class ArgParser {
    public:
        ArgParser() = default;
        inline const std::vector<BaseArgument*>& get_args() {
            return arguments;
        }
        inline void push_arg(BaseArgument &arg) {
            arguments.push_back(&arg);
        }
        void parse_args(int argc, const char** argv);
        void* get_arg(const char* value);
    private:
        std::vector<BaseArgument*> arguments;
};



namespace parseargs_meta {
    extern int version;
    extern const char* repo;
    extern const char* make_an_issue;

    inline const char license[] = "MIT License";
}



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
