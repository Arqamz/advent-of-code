#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>

#define MAX_SIZE 1001

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}



int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    int array1[MAX_SIZE];
    int array2[MAX_SIZE];
    int num1, num2;
    int count = 0;

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    while (fscanf(file, "%d %d", &num1, &num2) == 2) {
        array1[count] = num1;
        array2[count] = num2;
        count++;
    }

    fclose(file);

    qsort(array1, count, sizeof(int), compare);
    qsort(array2, count, sizeof(int), compare);

    int difference = 0;

    for (int i = 0; i<count; i++){
        difference += abs(array1[i] - array2[i]);
    }

    printf("The difference is: %d\n", difference);

    std::unordered_map<int, int> hashmap;

    for (int i = 0; i < count; i++) {
        hashmap[array2[i]]++;
    }

    int similiarity = 0;

    for (int i = 0; i < count; i++) {
        similiarity += array1[i] * hashmap[array1[i]];
    }

    printf("The similiarity is: %d\n", similiarity);

    return 0;
}