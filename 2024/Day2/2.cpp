#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include "../Utils/util.h"

using namespace std;

vector<vector<int>> read_multiline_input_file(const string& filename) {
    ifstream file(filename);
    vector<vector<int>> result;

    if (!file) {
        cerr << "Failed to open file " << filename << endl;
        return result;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        vector<int> report;
        int num;
        while (ss >> num) {
            report.push_back(num);
        }
        result.push_back(report);
    }

    file.close();
    return result;
}

bool is_safe(const vector<int>& report) {
    if (report.size() < 2) return true;
    bool increasing = false;
    bool decreasing = false;

    for (size_t i = 1; i < report.size(); ++i) {
        int diff = report[i] - report[i - 1];

        if ((abs(diff) > 3) || (abs(diff) < 1)) return false;

        if (diff > 0) {
            increasing = true;
        } else if (diff < 0) {
            decreasing = true;
        }
    }
    return !(increasing && decreasing);
}

bool can_be_safe_with_removal(const vector<int>& report) {
    if (report.size() < 3) return true;

    for (size_t i = 0; i < report.size(); ++i) {
        vector<int> modified_report = report;
        modified_report.erase(modified_report.begin() + i);

        if (is_safe(modified_report)) return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    Timer overall_timer;
    overall_timer.start_timer();

    Timer part1_timer;
    Timer part2_timer;

    vector<vector<int>> reports = read_multiline_input_file(argv[1]);

    part1_timer.start_timer();
    part2_timer.start_timer();

    int safe_count_part1 = 0, safe_count_part2 = 0;

    for (const auto& report : reports) {
        part1_timer.start_timer();
        if (is_safe(report)) {
            ++safe_count_part1;
            part1_timer.stop_timer();
            ++safe_count_part2;
        } else if (can_be_safe_with_removal(report)) {
            ++safe_count_part2;
        }
    }

    part1_timer.stop_timer();
    part2_timer.stop_timer();

    cout << "Part 1 -> Safe reports: " << safe_count_part1 << endl;
    part1_timer.print_duration("Part 1");

    cout << "Part 2 -> Safe reports (with Problem Dampener): " << safe_count_part2 << endl;
    part2_timer.print_duration("Part 2");

    overall_timer.stop_timer();
    overall_timer.print_duration();

    return 0;
}
