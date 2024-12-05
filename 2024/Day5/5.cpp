#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <set>
#include <algorithm>
#include "../Utils/util.h"

using namespace std;

void parseInput(const string& filename, unordered_map<int, set<int>>& rules, vector<vector<int>>& updates) {
    ifstream file(filename);
    string line;
    bool readingUpdates = false;

    while (getline(file, line)) {
        if (line.empty()) {
            readingUpdates = true;
            continue;
        }

        if (!readingUpdates) {
            size_t delimiter = line.find('|');
            int x = stoi(line.substr(0, delimiter));
            int y = stoi(line.substr(delimiter + 1));
            rules[x].insert(y);
        } else {
            stringstream ss(line);
            string token;
            vector<int> update;
            while (getline(ss, token, ',')) {
                update.push_back(stoi(token));
            }
            updates.push_back(update);
        }
    }
}

bool isCorrectOrder(const vector<int>& update, const unordered_map<int, set<int>>& rules) {
    for (size_t i = 0; i < update.size(); ++i) {
        for (size_t j = i + 1; j < update.size(); ++j) {
            int x = update[i];
            int y = update[j];
            if (rules.count(x) && rules.at(x).count(y)) {
                continue;
            }
            if (rules.count(y) && rules.at(y).count(x)) {
                return false;
            }
        }
    }
    return true;
}

vector<int> reorderUpdate(const vector<int>& update, const unordered_map<int, set<int>>& rules) {
    vector<int> orderedUpdate = update;
    sort(orderedUpdate.begin(), orderedUpdate.end(), [&](int a, int b) {
        if (rules.count(a) && rules.at(a).count(b)) return true;
        if (rules.count(b) && rules.at(b).count(a)) return false;
        return false;
    });
    return orderedUpdate;
}


int getMiddlePage(const vector<int>& update) {
    return update[update.size() / 2];
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    unordered_map<int, set<int>> rules;
    vector<vector<int>> updates;

    Timer overall_timer;
    overall_timer.start_timer();

    parseInput(argv[1], rules, updates);

    Timer part1_timer;
    Timer part2_timer;
    
    part1_timer.start_timer();
    part2_timer.start_timer();

    int middleSum = 0;
    int middleSumIncorrect = 0;
    for (const auto& update : updates) {
        if (isCorrectOrder(update, rules)) {
            part1_timer.start_timer();
            middleSum += getMiddlePage(update);
            part1_timer.stop_timer();
        } else {
            part2_timer.start_timer();
            vector<int> reorderedUpdate = reorderUpdate(update, rules);
            middleSumIncorrect += getMiddlePage(reorderedUpdate);
            part2_timer.stop_timer();
        }
    }
    part1_timer.stop_timer();
    part2_timer.stop_timer();

    cout << "Sum of middle pages for correctly ordered updates: " << middleSum << endl;
    part1_timer.print_duration("Part 1");

    cout << "Sum of middle pages for incorrectly ordered updates: " << middleSumIncorrect << endl;
    part2_timer.print_duration("Part 2");

    overall_timer.stop_timer();
    overall_timer.print_duration();

    return 0;
}
