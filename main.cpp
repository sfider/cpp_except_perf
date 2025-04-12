#include <cassert>
#include <chrono>
#include <format>
#include <iostream>

#if THROW_EXCEPTIONS || CATCH_EXCEPTIONS
    #include <stdexcept>
#endif

namespace {
    int fibonacci(int i) {
        if (i <= 1) [[unlikely]] {
#if THROW_EXCEPTIONS
            if (i < 0) {
                throw std::runtime_error{"Negative number"};
            }
#else
            assert(i >= 0);
#endif

            if (i == 0)
                return 0;
            return 1;
        }

        return fibonacci(i - 1) + fibonacci(i - 2);
    }
}

int main() {
    auto start_time = std::chrono::high_resolution_clock::now();

    int result {0};
    for (int i = 0; i < 45; i++) {
#if CATCH_EXCEPTIONS
        try
#endif
        {
            result += fibonacci(i);
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
