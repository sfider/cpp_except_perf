## About

This is a micro-benchmark to test C++ exceptions influence on performance. It borrows from a medium post: [The true cost of C++ exceptions](https://mmomtchev.medium.com/the-true-cost-of-c-exceptions-7be7614b5d84).

The project has four configurations for four test scenarios:
1. 00_NoExcept: exceptions disabled in the compiler options
2. 01_FullExcept: exceptions used with both throwing and catching
3. 02_ThrowExcept: exceptions thrown, but not caught
4. 03_CatchExcept: exceptions caught, but not thrown

All configurations are based on the default Release configuration provided by cmake.

No exceptions are actually thrown in any of the scenarios. The aim is to test the influence of exceptions on a codebase that doesn't really excpect them to be thrown.

## Results

After making sure that there was no tail recursion and loop unrolling opportunities, the results got much more consistant:

#### MSVC (VS 17.13.6):
1. 00_NoExpect: ~9600s
2. 01_FullExpect: ~9170ms
3. 02_ThrowExpect: ~9700ms
4. 03_CatchExpect: ~9600ms

#### Clang (19.1.1):
1. 00_NoExpect: ~9600ms
2. 01_FullExpect: ~9250ms
3. 02_ThrowExpect: ~9250ms
4. 03_CatchExpect: ~9600ms

My expectation was that the code with exceptions disabled would be the most performant, as the ancient tribal knowledge would suggest.

However, the tests seem to point to the conclusion, that the presence of exceptions doesn't make much of a difference in this simple case.

## Configure

For 'ninja' build with the default compiler (MSVC for me) use:
```sh
cmake --preset=ninja
```

For 'ninja' build with Clang use:
```sh
cmake --preset=ninja-clang
```

## Build

To build all configurations use:
```sh
cmake --build build --config 00_NoExcept
cmake --build build --config 01_FullExcept
cmake --build build --config 02_ThrowExcept
cmake --build build --config 03_CatchExcept
```

## Test

To run all configurations use:
```sh
./build/00_NoExcept/cpp_except_perf.exe
./build/01_FullExcept/cpp_except_perf.exe
./build/02_ThrowExcept/cpp_except_perf.exe
./build/03_CatchExcept/cpp_except_perf.exe
```

## Build & Test

To automatically build and test all configurations use:
```sh
./build_and_test.bat
```
