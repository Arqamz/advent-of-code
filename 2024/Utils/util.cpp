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

string read_entire_file(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Failed to open file " << filename << endl;
        return "";
    }

    stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

template <typename T>
vector<T> read_pairs_from_file(const string& filename) {
    ifstream file(filename);
    vector<T> result;
    T num1, num2;

    if (!file) {
        cerr << "Failed to open file " << filename << endl;
        return result;
    }

    while (file >> num1 >> num2) {
        result.push_back(num1);
        result.push_back(num2);
    }

    file.close();
    return result;
}

template <typename T>
vector<vector<T>> read_multiline_input_file(const string& filename) {
    ifstream file(filename);
    vector<vector<T>> result;

    if (!file) {
        cerr << "Failed to open file " << filename << endl;
        return result;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        vector<T> report;
        T num;
        while (ss >> num) {
            report.push_back(num);
        }
        result.push_back(report);
    }

    file.close();
    return result;
}

template <typename T>
void print_vector(const vector<T>& vec) {
    for (const auto& v : vec) {
        cout << v << " ";
    }
    cout << endl;
}

// Template instantiation
template vector<int> read_pairs_from_file<int>(const string&);
template vector<vector<int>> read_multiline_input_file<int>(const string&);
template void print_vector<int>(const vector<int>&);