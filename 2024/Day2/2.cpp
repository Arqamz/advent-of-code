#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include "../Utils/util.h"

using namespace std;

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

    Timer timer;
    timer.start_timer();

    vector<vector<int>> reports = read_multiline_input_file<int>(argv[1]);

    int safe_count_part1 = 0, safe_count_part2 = 0;

    for (const auto& report : reports) {
        if (is_safe(report)) {
            ++safe_count_part1;
            ++safe_count_part2;
        } else if (can_be_safe_with_removal(report)) {
            ++safe_count_part2;
        }
    }

    cout << "Part 1 -> Safe reports: " << safe_count_part1 << endl;
    cout << "Part 2 -> Safe reports (with Problem Dampener): " << safe_count_part2 << endl;

    timer.stop_timer();
    timer.print_duration();

    return 0;
}
