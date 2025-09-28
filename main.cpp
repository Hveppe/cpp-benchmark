#include <iostream>
#include <chrono>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <random>
#include <string>

#include "test/test.h"

long getMemoryUsageKB() {
    std::ifstream statm("/proc/self/statm");
    long size = 0, resident = 0;
    statm >> size >> resident;
    return resident * sysconf(_SC_PAGESIZE) / 1024;
}

std::string generateRandomString(size_t length) {
    const std::string chars =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";

    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dist(0, chars.size() - 1);

    std::string result;
    for (size_t i = 0; i < length; ++i) {
        result += chars[dist(gen)];
    }
    return result;
}

template<typename func>
void benchmark(func algoritmen, int maxLength, int repetitions = 1000) {
    std::vector<long double> times;
    std::vector<long double> memorys;
    
    for(int length = 0; length < maxLength; length++) {
        long double time = 0.0;
        long double maxMemoryKB = 0.0;
        
        for(int i = 0; i < repetitions; i++) {
            std::string text = generateRandomString(length); 

            auto startMemory = getMemoryUsageKB();
            auto startTime = std::chrono::high_resolution_clock::now();
            algoritmen(5, 7990271, text);
            auto endTime = std::chrono::high_resolution_clock::now();
            auto endMemory = getMemoryUsageKB();

            std::chrono::duration<double, std::milli> duration = endTime - startTime;
            time += duration.count();

            long deltaMemory = endMemory - startMemory;
            if(deltaMemory > maxMemoryKB) {
                maxMemoryKB = deltaMemory;
            } 
        }
        times.push_back(time / repetitions);
        memorys.push_back(maxMemoryKB);
    }

    for(int i = 0; i < maxLength; i++) {
        std::cout << "Averge time passed: " << times[i] << " ms" << " over " << repetitions << " repetitions" << std::endl;
        std::cout << "Averge memory used: " << memorys[i] << " kb" << " over " << repetitions << " repetitions" << std::endl;
    }
}

int main() {
    benchmark(EncryptRSA, 100);
}