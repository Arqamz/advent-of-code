// Abdullah is a freedom fighter, fighting against the occupant forces. As a part of his fighting strategy, his primary target
// is the destruction of railroads.
// In this problem, the task is to assist Abdullah to make best use of his limited resources. He has some information
// available from intelligence wing of his organization. First, the rail line is completely linear which means that there are
// no branches, no spurs. Next, the Intelligence wing has assigned a Strategic Importance to each depot which is an integer
// from 1 to 5. Moreover, a depot is of no use on its own, it only has value if it is connected to other depots. The Strategic
// Value of the entire railroad is calculated by adding up the products of the Strategic Values for every pair of depots that
// are connected, directly or indirectly, by the rail line. Consider the following railroad:
// 4 - 5 - 1 - 2
// The strategic value of above railroad is computed as: 4*5 + 4*1 + 4*2 + 5*1 + 5*2 + 1*2 = 49.
// Now, suppose that Abdullah only has enough resources for one attack. He cannot attack the depots themselves because
// they are too well defended. He must attack the rail line between depots, in the middle of the desert. Consider what
// would happen if Abdullah attacked this rail line right in the middle:
// 4 - 5 X 1 - 2
// The Strategic Value of the remaining railroad is 4*5 + 1*2 = 22. But, suppose Abdullah attacks between the 4 and 5
// depots:
// 4 X 5 - 1 - 2
// The Strategic Value of the remaining railroad is 5*1 + 5*2 + 1*2 = 17. This is the Abdullah's best option.
// Given a description of a railroad and the number of attacks that Abdullah can perform, figure out the smallest Strategic
// Value that he can achieve for that railroad.
// Input
// There will be several data sets. Each data set will begin with a line with two integers, n and m. n is the number of depots
// on the railroad (1≤n≤1000), and m is the number of attacks Abdullah has resources for (0≤m<n). On the next line will be
// n integers, each from 1 to 5, indicating the Strategic Value of each depot in order. End of input will be marked by a line
// with n=0 and m=0, which should not be processed.
// Output
// For each data set, output a single integer, indicating the smallest Strategic Value for the railroad that Abdullah can
// achieve with his attacks. Output each integer in its own line.
// Sample Input
// 4 1
// 4 5 1 2
// 4 2
// 4 5 1 2

// 4

// 0 0
// Sample Output
// 17
// 2

#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const int MAX_DEPOTS = 1001;
const int MAX_CUTS = 11;
const int INF = 1e9;

int strategicValues[MAX_DEPOTS][MAX_CUTS];
bool isComputed[MAX_DEPOTS][MAX_CUTS];
int depots[MAX_DEPOTS];
int depotCount;
int productSums[MAX_DEPOTS][MAX_DEPOTS]; // Stores precalculated sums of products

void precalculateProductSums() {
    for (int i = 1; i < depotCount; ++i) {
        for (int j = 0; j < depotCount - i; ++j) {
            productSums[j][j + i] = productSums[j + 1][j + i] + productSums[j][j + i - 1] + (depots[j] * depots[j + i]) - productSums[j + 1][j + i - 1];
        }
    }
    for(int i=0;i<depotCount;i++){
        for(int j=0;j<depotCount;j++){
            cout << productSums[i][j] << " ";
        }
        cout << "\n";
    }
}


int minStrategicValue(int start, int remainingCuts) {
    if (start >= depotCount - 1) return 0;
    if (isComputed[start][remainingCuts]) return strategicValues[start][remainingCuts];
    
    int sum = productSums[start][depotCount - 1];

    if (remainingCuts == 0) {
        strategicValues[start][remainingCuts] = sum;
        isComputed[start][remainingCuts] = true;
        return sum;
    }

    int minValue = sum;
    for (int cut = start; cut < depotCount - 1; ++cut) {
        int currentCutSum = productSums[start][cut];
        if (cut + 1 < depotCount && remainingCuts > 0) {
            int restMin = minStrategicValue(cut + 1, remainingCuts - 1);
            minValue = min(minValue, currentCutSum + restMin);
        }
    }

    strategicValues[start][remainingCuts] = minValue;
    isComputed[start][remainingCuts] = true;
    return minValue;
}

int main() {
    int cutsAllowed;
    while (true) {
        cin >> depotCount >> cutsAllowed;
        if (depotCount == 0 && cutsAllowed == 0) break;

        for (int i = 0; i < depotCount; i++) {
            cin >> depots[i];
        }

        precalculateProductSums();
        memset(isComputed, 0, sizeof(isComputed));
        cout << minStrategicValue(0, cutsAllowed) << endl;
    }
    return 0;
}
