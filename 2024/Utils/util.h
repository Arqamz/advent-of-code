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

std::string read_entire_file(const std::string& filename);

template <typename T>
std::vector<T> read_pairs_from_file(const std::string& filename);

template <typename T>
std::vector<std::vector<T>> read_multiline_input_file(const std::string& filename);

template <typename T>
void print_vector(const std::vector<T>& vec);

#endif