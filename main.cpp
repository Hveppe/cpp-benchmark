#include <algorithm>
#include <iostream>
#include <chrono>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <random>
#include <string>
#include <cstdlib>
#include <atomic>

#include "RSA.h"

// Global atomic counter for heap allocations
std::atomic<size_t> totalAllocatedBytes(0);

void* operator new(std::size_t sz) {
    totalAllocatedBytes += sz;
    return malloc(sz);
}

void operator delete(void* ptr) noexcept {
    free(ptr);
}

long double average(const std::vector<long double>& data) {
    if (data.empty()) return 0.0;

    long double sum = 0.0;
    for (auto x : data) {
       sum += x; 
    } 
    return sum / data.size();
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

void exportToCSV(std::vector<long double> x, std::vector<long double> y, std::string name, int size) {
    std::ofstream file("data.csv");
    file << name << "," << size << "\n";
    for(size_t i = 0; i < x.size(); ++i) {
        file << x[i] << "," << y[i] << "\n";
    }
}

template<typename func>
void benchmark(func algoritmen, int maxLength, int repetitions = 1000) {
    std::vector<long double> times;
    std::vector<long double> memorys;
    
    for(int length = 0; length < maxLength; length++) {
        size_t maxMemoryBytes = 0;
        std::vector<long double> iterationTimes;
        std::string text = generateRandomString(length);

        for(int i = 0; i < repetitions; i++) {
            totalAllocatedBytes = 0;
            auto startTime = std::chrono::steady_clock::now();
            algoritmen(5, 7990271, text);
            auto endTime = std::chrono::steady_clock::now();

            if (totalAllocatedBytes > maxMemoryBytes) {
                maxMemoryBytes = totalAllocatedBytes;
            }
                
            std::chrono::duration<long double, std::milli> duration = endTime - startTime;
            if (duration.count() > 0.0 && duration.count() < 1000.0) { // filter absurd spikes
                iterationTimes.push_back(duration.count());
            } 
        }
        times.push_back(average(iterationTimes));
        memorys.push_back(static_cast<long double>(maxMemoryBytes / 1024.0));
    }
    exportToCSV(times, memorys, "RSA Encrypt", maxLength);
    system("python3 plot.py");
}

int main() {
    benchmark(encryptRSA, 300);
}