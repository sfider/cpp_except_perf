#include <cassert>
#include <chrono>
#include <format>
#include <iostream>

#if THROW_EXCEPTIONS || CATCH_EXCEPTIONS
    #include <stdexcept>
#endif

namespace {
    std::tuple<int, int> fibonacci(int i) {
        if (i <= 1) [[unlikely]] {
#if THROW_EXCEPTIONS
            if (i < 0) {
                throw std::runtime_error{"Negative number"};
            }
#else
            assert(i >= 0);
#endif
            return std::make_tuple(i, i - 1);
        }
        auto a = fibonacci(i - 1);
        auto b = fibonacci(std::get<1>(a));
        return std::make_tuple(std::get<0>(a) + std::get<0>(b), i - 1);
    }
}

int main(int argc, char* argv[]) {
    auto start_time = std::chrono::high_resolution_clock::now();

    int cnt = argc > 1 ? std::atoi(argv[1]) : 45;

    int result {0};
    for (int i = 0; i < cnt; i++) {
#if CATCH_EXCEPTIONS
        try
#endif
        {
            result += std::get<0>(fibonacci(i));
        }
#if CATCH_EXCEPTIONS
        catch (const std::exception &) {
            std::cout << "caught exception\n";
        }
#endif
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration {end_time - start_time};
    std::cout << std::format("test took {:.4f}ms", duration.count(), result);
}
