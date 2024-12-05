#include "util.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void Timer::start_timer() {
    start = chrono::steady_clock::now();
}

void Timer::stop_timer() {
    end = chrono::steady_clock::now();
}

void Timer::print_duration(const string& part) {
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    long long nanoseconds = duration.count();

    string label = (part == "total") ? "Total execution time" : "Execution time for " + part;

    if (nanoseconds < 1000) {
        cout << label << ": " << nanoseconds << "ns" << endl;
    } 
    else if (nanoseconds < 1000000) {
        double microseconds = nanoseconds / 1000.0;
        cout << label << ": " << microseconds << "us" << endl;
    } 
    else if (nanoseconds < 1000000000) {
        double milliseconds = nanoseconds / 1000000.0;
        cout << label << ": " << milliseconds << "ms" << endl;
    } 
    else {
        double seconds = nanoseconds / 1000000000.0;
        cout << label << ": " << seconds << "s" << endl;
    }
}

template <typename T>
void print_vector(const vector<T>& vec) {
    for (const auto& v : vec) {
        cout << v << " ";
    }
    cout << endl;
}