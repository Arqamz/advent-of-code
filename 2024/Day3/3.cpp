#include <iostream>
#include <string>
#include <regex>
#include "../Utils/util.h"

using namespace std;

int compute_mul(const string& instruction) {
    static const regex mul_regex(R"(mul\((\d+),(\d+)\))");
    smatch match;
    if (regex_match(instruction, match, mul_regex)) {
        int x = stoi(match[1]);
        int y = stoi(match[2]);
        return x * y;
    }
    return 0;
}

int extract_and_compute(const string& input, bool enable_mul = true) {
    static const regex instruction_regex(R"((mul\(\d+,\d+\)))");
    smatch match;
    int result = 0;

    auto begin = input.cbegin();
    while (regex_search(begin, input.cend(), match, instruction_regex)) {
        if (enable_mul) {
            result += compute_mul(match.str());
        }
        begin = match.suffix().first;
    }
    return result;
}

int extract_and_compute_enabled_only(const string& input) {
    static const regex instruction_regex(R"((do\(\)|don't\(\)|mul\(\d+,\d+\)))");
    bool enable_mul = true;
    int total = 0;

    auto begin = input.cbegin();
    auto end = input.cend();
    smatch match;

    while (regex_search(begin, end, match, instruction_regex)) {
        string instruction = match.str();
        if (instruction == "do()") {
            enable_mul = true;
        } else if (instruction == "don't()") {
            enable_mul = false;
        } else if (instruction.find("mul(") == 0) {
            total += compute_mul(instruction) * enable_mul;
        }
        begin = match.suffix().first;
    }
    return total;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    Timer overall_timer;
    overall_timer.start_timer();

    string memory_input = read_entire_file(argv[1]);

    Timer part1_timer;
    part1_timer.start_timer();
    int part1_result = extract_and_compute(memory_input);
    part1_timer.stop_timer();

    Timer part2_timer;
    part2_timer.start_timer();
    int part2_result = extract_and_compute_enabled_only(memory_input);
    part2_timer.stop_timer();

    cout << "Part 1 -> Sum of all valid multiplications: " << part1_result << endl;
    part1_timer.print_duration("Part 1");

    cout << "Part 2 -> Sum of all enabled multiplications: " << part2_result << endl;
    part2_timer.print_duration("Part 2");

    overall_timer.stop_timer();
    overall_timer.print_duration();

    return 0;
}
