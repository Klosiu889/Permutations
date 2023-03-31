#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

// Ten plik zawiera przykład użycia funkcji:
bool inverse_permutation(size_t n, int *p);

int tests_failed = 0;
char *RED = "\033[0;31m";
char *GREEN = "\033[0;32m";
char *RESET = "\033[0m";

void run_test(size_t n, int *arr, bool expected, char *name) {
    bool result = inverse_permutation(n, arr);
    if (result == expected) {
        printf("%sOK%s", GREEN, RESET);
    } else {
        printf("%sERROR%s", RED, RESET);
        tests_failed++;
    }
    printf("    %s\n", name);
}

int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], "-color=false") == 0) {
        RED = "";
        GREEN = "";
        RESET = "";
    }

    int empty_arr[] = {};
    int consecutive_numbers_array[] = {0, 1, 2, 3, 4};
    int negative_numbers[] = {1, -2, 3, -4};
    int too_big_numbers[] = {1, 2, 3, 5};
    int duplicate_numbers[] = {1, 2, 3, 1};
    int duplicate_numbers2[] = {0, 0, 1, 2};
    int correct_permutation[] = {3, 1, 5, 0, 2, 4};

    printf("Running tests...\n");

    run_test((uint64_t) INT32_MAX + 2, empty_arr, false, "Size to big");
    run_test(0, empty_arr, false, "Empty array");
    run_test(-1, empty_arr, false, "Negative size");
    run_test(4, negative_numbers, false, "Negative numbers");
    run_test(5, consecutive_numbers_array, true, "Consecutive numbers 0 to 4");
    run_test(6, correct_permutation, true, "Correct permutation");
    run_test(4, duplicate_numbers, false, "Duplicate numbers");
    run_test(4, duplicate_numbers2, false, "Duplicate numbers 2");
    run_test(4, too_big_numbers, false, "Too big numbers");

    if (tests_failed > 0) {
        printf("%sTests failed%s: %d\n", RED, RESET, tests_failed);
        exit(1);
    } else {
        printf("%sAll tests passed!%s\n", GREEN, RESET);
    }

    return 0;
}
