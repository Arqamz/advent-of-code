#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include "../Utils/util.h"

#define MAX_SIZE 1001

using namespace std;

int calculate_difference(const vector<int>& array1, const vector<int>& array2) {
    int difference = 0;
    int count = array1.size();

    for (int i = 0; i < count; i++) {
        difference += abs(array1[i] - array2[i]);
    }

    return difference;
}

int calculate_similarity(const vector<int>& array1, const vector<int>& array2) {
    unordered_map<int, int> hashmap;
    int similarity = 0;

    for (int i = 0; i < array2.size(); i++) {
        hashmap[array2[i]]++;
    }

    for (int i = 0; i < array1.size(); i++) {
        similarity += array1[i] * hashmap[array1[i]];
    }

    return similarity;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    Timer timer;
    timer.start_timer();

    vector<int> data = read_input_file<int>(argv[1]);
    
    vector<int> array1, array2;
    for (size_t i = 0; i < data.size(); i += 2) {
        array1.push_back(data[i]);
        array2.push_back(data[i + 1]);
    }

    sort(array1.begin(), array1.end());
    sort(array2.begin(), array2.end());

    // Part 1: Calculate difference
    Timer part1Timer;
    part1Timer.start_timer();
    int difference = calculate_difference(array1, array2);
    part1Timer.stop_timer();
    cout << "Part 1 -> The difference is: " << difference << endl;
    part1Timer.print_duration("part 1");

    // Part 2: Calculate similarity
    Timer part2Timer;
    part2Timer.start_timer();
    int similarity = calculate_similarity(array1, array2);
    part2Timer.stop_timer();
    cout << "Part 2 -> The similarity is: " << similarity << endl;
    part2Timer.print_duration("part 2");

    timer.stop_timer();
    timer.print_duration();

    return 0;
}
