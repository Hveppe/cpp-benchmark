#include <iostream>
#include <chrono>
#include <fstream>
#include <unistd.h>

#include "test/test.h"

long getMemoryUsageKB() {
    std::ifstream statm("/proc/self/statm");
    long size = 0, resident = 0;
    statm >> size >> resident;
    return resident * sysconf(_SC_PAGESIZE) / 1024;
}
   

template<typename func>
void benchmark(func algoritmen) {
    auto startMemory = getMemoryUsageKB();
    auto startTime = std::chrono::high_resolution_clock::now();
    algoritmen();
    auto endTime = std::chrono::high_resolution_clock::now();
    auto endMemory = getMemoryUsageKB();

    std::chrono::duration<double, std::milli> duration = endTime - startTime;
    double memory = endMemory - startMemory; 

    std::cout << "Time passed: " << duration.count() << " ms" << std::endl;
    std::cout << "Memory used: " << memory << " kb" << std::endl;
}

int main() {
    benchmark(EncryptRSA);
}