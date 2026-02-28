# parse-args
A low-level low-latency C++ argument parser.

## Standards
Please note that this library doesn't necessarily follow modern C++ standards, and uses things like:
* `void*` instead of templates in certain places
* `char*` instead of std::string
* manual memory management instead of smart pointers
* ...

The goal is not following modern C++ standards, but providing a C-like, low-latency, low-level library for passing arguments that can be easily connected to a C project with minimal glue code.

## Example usage
An example usage of parseargs is:
```cpp
#include "parseargs/parseargs.hpp"

#include <cstdio>

void setup_argparse(ArgParser& parser) {
    static Argument<int> arg("val", true);
    parser.push_arg(arg);
}

int main(int argc, const char** argv) {
    ArgParser parser;
    setup_argparse(parser);

    parser.parse_args(argc, argv);
    
    int value = *(int*)parser.get_arg("val");

    printf("%d\n", value);
}
```

## Default argument types
The default argument types are `Argument<int>` (integers) and `Argument<char*>` (strings).

## Defining custom argument types
You can define custom argument types the same way the library does in `argument.cpp`:
```cpp
template<>
void Argument<int>::parse(const char* data) {
    this->_was_parsed = TRUE;
    this->data = atoi(data);
}

template<>
void Argument<char*>::parse(const char* data) {
    this->_was_parsed = TRUE;
    uint64_t lenght = strlen(data);
    this->data = (char*)malloc(lenght + 1);
    memcpy(this->data, data, lenght + 1);
}

template class Argument<int>;
template class Argument<char*>;
```

While the library is OOP-based, there is no need for creating a new class.

When creating a custom argument type, you will need to implement the following functions:
* `void Argument<T>::parse(const char* data)`: recieves the string containing the value, converts it to the appropriate data type and stores the data
* `void Argument<T>::free_data()`: free any heap-allocated data (if any); this shouldnt free() the `name` variable
* `Argument<int>::Argument(const Argument<int> &other)`: the copy operator. you can find an example implementation for this in `argument.cpp`

You may create a custom class if you'd like, but we advise against doing so as you'd also have to implement:
* `CustomArgument(const char* name, flag_t required)`
* `CustomArgument(const CustomArgument<T> &other)`
* `~CustomArgument() override` (`free_data()` would no longer be called automatically)
* `void* CustomArgument::get_data()`

If you create a custom class for any reason, it *has* to inherit from `BaseArgument`.

## Build arguments
Build both the library and the calling files with `-DPARSEARGS_ATTEMPT_RECOVERY 1` to be more leniant with user errors.

## Benchmarks
During unit testing, parse-args takes an average of 6-9 microseconds per testcase.

Run 1:
```
=> Test passed: 1/1 arguments (5 µs)          
=> Test passed: 0/0 arguments (0 µs)          
=> Test passed: 0/1 arguments (expect abort) (15 µs)   
```

Run 2:
```
=> Test passed: 1/1 arguments (7 µs)          
=> Test passed: 0/0 arguments (0 µs)          
=> Test passed: 0/1 arguments (expect abort) (15 µs) 
```

Run 3:
```
=> Test passed: 1/1 arguments (4 µs)          
=> Test passed: 0/0 arguments (0 µs)          
=> Test passed: 0/1 arguments (expect abort) (14 µs)  
```

The average execution time is `(5 + 15 + 7 + 15 + 4 + 14) / 9 = 7`.
