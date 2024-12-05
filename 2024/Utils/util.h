#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <unordered_map>
#include <chrono>
#include <string>

struct Timer {
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;

    void start_timer();
    void stop_timer();
    void print_duration(const std::string& part = "total");
};

template <typename T>
void print_vector(const std::vector<T>& vec);

#endif