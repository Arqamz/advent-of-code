public static int computeSmallestStrategicValue(int[] depotValues, int m) {
    int size = depotValues.length;
    int[][] Mat = new int[size][size];

    // Fill Mat array with initial values
    for (int i = 0; i < size; i++) {
        Mat[i][i] = 0;
    }

    // Compute Mat array using dynamic programming
    for (int i = 1; i < size; i++) {
        for (int j = 0; j < size - i; j++) {
            Mat[j][j + i] = Mat[j + 1][j + i] + Mat[j][j + i - 1] + (depotValues[j] * depotValues[j + i]) - Mat[j + 1][j + i - 1];
        }
    }

    // Return the smallest strategic value after considering attacks
    return Mat[0][size - 1];
}