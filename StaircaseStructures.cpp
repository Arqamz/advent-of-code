// Each type of structure should consist of 2 or more stages. Each stage consists of a natural number of blocks. No two
// stages are allowed to be at the same height. Each stage must be lower in height than the previous one. All stages must
// contain at least one block. The height of a stage is defined by the number of blocks that make up that stage.
// For example, when N = 3, you have only 1 choice of how to build the structure, with the first stage having a height of 2
// and the second step having a height of 1 as follows:
// □
// □□
// 21
// When N = 4, you still only have 1 structure choice:
// □
// □
// □□
// 31
// But when N = 5, there are two ways you can build a structure from the given blocks.
// The two staircases can have heights (4, 1) or (3, 2), as shown below:
// □
// □
// □
// □□
// 41
// □
// □□
// □□
// 32
// Write a program that takes a positive integer n and returns the number of different number of
// structures that can be built from exactly n blocks, where 3 ≤ n ≤ 200.

// n^3 solution below

#include <iostream>
#include <vector>

using namespace std;

int countStaircaseStructures(int n, int prevHeight, vector<vector<int>>& memo) {
    if (n == 0) {
        return 1;
    }

    if (memo[n][prevHeight] != -1) {
        return memo[n][prevHeight];
    }

    int totalWays = 0;

    for (int height = 1; height <= n && height < prevHeight; height++) {
        totalWays += countStaircaseStructures(n - height, height, memo);
    }

    memo[n][prevHeight] = totalWays;

    return totalWays;
}

int countStaircaseStructures(int n) {
    vector<vector<int>> memo(n + 1, vector<int>(n + 2, -1));
    return countStaircaseStructures(n, n + 1, memo) - 1;
}

int main() {
    // Example usage:
    cout << countStaircaseStructures(200) << endl;
    return 0;
}

