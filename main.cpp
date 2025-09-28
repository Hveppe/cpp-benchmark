#include <iostream>
#include <chrono>
#include <fstream>
#include <unistd.h>
#include <vector>

#include "test/test.h"

long getMemoryUsageKB() {
    std::ifstream statm("/proc/self/statm");
    long size = 0, resident = 0;
    statm >> size >> resident;
    return resident * sysconf(_SC_PAGESIZE) / 1024;
}
   

template<typename func>
void benchmark(func algoritmen, int repetitions = 1000) {
    long double time = 0.0;
    long double maxMemoryKB = 0.0;
    
    for(int i = 0; i < repetitions; i++) {
        auto startMemory = getMemoryUsageKB();
        auto startTime = std::chrono::high_resolution_clock::now();
        algoritmen(5, 7990271, "hej med dig luder");
        auto endTime = std::chrono::high_resolution_clock::now();
        auto endMemory = getMemoryUsageKB();

        std::chrono::duration<double, std::milli> duration = endTime - startTime;
        time += duration.count();

        long deltaMemory = endMemory - startMemory;
        if(deltaMemory > maxMemoryKB) {
            maxMemoryKB = deltaMemory;
        } 
    }
    
    std::cout << "Averge time passed: " << time/repetitions << " ms" << " over " << repetitions << " repetitions" << std::endl;
    std::cout << "Averge memory used: " << maxMemoryKB<< " kb" << " over " << repetitions << " repetitions" << std::endl;
}

int main() {
    benchmark(EncryptRSA);
}