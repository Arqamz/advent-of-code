#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "../Utils/util.h"

using namespace std;

vector<string> readGrid(const string& filename) {
    vector<string> grid;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        grid.push_back(line);
    }
    return grid;
}


bool matches(const vector<string>& grid, const string& word, int row, int col, int dRow, int dCol) {
    int numRows = grid.size();
    int numCols = grid[0].size();
    int wordLen = word.length();

    for (int i = 0; i < wordLen; i++) {
        int newRow = row + i * dRow;
        int newCol = col + i * dCol;

        if (newRow < 0 || newRow >= numRows || newCol < 0 || newCol >= numCols || grid[newRow][newCol] != word[i]) {
            return false;
        }
    }
    return true;
}

int countWordOccurrences(const vector<string>& grid, const string& word) {
    int count = 0;
    int numRows = grid.size();
    int numCols = grid[0].size();
    vector<pair<int, int>> directions = {
        {0, 1},  // Right
        {0, -1}, // Left
        {1, 0},  // Down
        {-1, 0}, // Up
        {1, 1},  // Diagonal Down-Right
        {-1, -1},// Diagonal Up-Left
        {1, -1}, // Diagonal Down-Left
        {-1, 1}  // Diagonal Up-Right
    };

    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            for (const auto& dir : directions) {
                if (matches(grid, word, row, col, dir.first, dir.second)) {
                    count++;
                }
            }
        }
    }
    return count;
}

bool isXMAS(const vector<string>& grid, int row, int col) {
    int numRows = grid.size();
    int numCols = grid[0].size();

    char topLeft = grid[row - 1][col - 1];
    char topRight = grid[row - 1][col + 1];
    char bottomLeft = grid[row + 1][col - 1];
    char bottomRight = grid[row + 1][col + 1];

    bool crissValid = (topLeft == 'M' && bottomRight == 'S') || (topLeft == 'S' && bottomRight == 'M');
    bool crossValid = (topRight == 'M' && bottomLeft == 'S') || (topRight == 'S' && bottomLeft == 'M');

    return crissValid && crossValid;
}

int countXMAS(const vector<string>& grid) {
    int count = 0;
    int numRows = grid.size();
    int numCols = grid[0].size();

    for (int row = 1; row < numRows - 1; row++) {
        for (int col = 1; col < numCols - 1; col++) {
            if (grid[row][col] == 'A' && isXMAS(grid, row, col)) {
                count++;
            }
        }
    }
    return count;
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
    
    vector<string> grid = readGrid(argv[1]);
    string word = "XMAS";

    if (grid.empty()) {
        cerr << "Error: Grid is empty or file could not be read." << endl;
        return 1;
    }

    part1_timer.start_timer();
    int totalOccurrences = countWordOccurrences(grid, word);
    part1_timer.stop_timer();

    cout << "Total occurrences of '" << word << "': " << totalOccurrences << endl;
    part1_timer.print_duration("Part 1");

    part2_timer.start_timer();
    int totalXMAS = countXMAS(grid);
    part2_timer.stop_timer();

    cout << "Total X-MAS patterns: " << totalXMAS << endl;
    part2_timer.print_duration("Part 2");

    overall_timer.stop_timer();
    overall_timer.print_duration();

    return 0;
}
