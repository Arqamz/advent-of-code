#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <fstream>
#include "../Utils/util.h"

#define MAX_SIZE 1001

using namespace std;

vector<int> read_pairs_from_file(const string& filename) {
    ifstream file(filename);
    vector<int> result;
    int num1, num2;

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

    Timer overall_timer;
    overall_timer.start_timer();

    Timer part1Timer;
    Timer part2Timer;

    vector<int> data = read_pairs_from_file(argv[1]);
    
    vector<int> array1, array2;
    for (size_t i = 0; i < data.size(); i += 2) {
        array1.push_back(data[i]);
        array2.push_back(data[i + 1]);
    }

    sort(array1.begin(), array1.end());
    sort(array2.begin(), array2.end());
    part1Timer.start_timer();

    int difference = calculate_difference(array1, array2);

    part1Timer.stop_timer();

    cout << "Part 1 -> The difference is: " << difference << endl;

    part1Timer.print_duration("part 1");

    part2Timer.start_timer();

    int similarity = calculate_similarity(array1, array2);

    part2Timer.stop_timer();

    cout << "Part 2 -> The similarity is: " << similarity << endl;

    part2Timer.print_duration("part 2");

    overall_timer.stop_timer();
    overall_timer.print_duration();

    return 0;
}
