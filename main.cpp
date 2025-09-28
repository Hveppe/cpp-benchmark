#include <iostream>
#include <chrono>

#include "test/test.h"

template<typename func>
void benchmark(func algoritmen) {
    auto startTime = std::chrono::high_resolution_clock::now();
    algoritmen(5, 7990271, "hej med dig din fede luder");
    auto endTime = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = endTime - startTime;
    std::cout << "Time passed: " << duration.count() << " ms" << std::endl;
}

int main() {
    benchmark(EncryptRSA);
}