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
char* RED = "\033[0;31m";
char* GREEN = "\033[0;32m";
char* RESET = "\033[0m";

void run_test(size_t n, int* arr, int expected, char* name) {
    printf("Test %s:\n", name);
    bool result = inverse_permutation(n, arr);
    if (result == expected) {
        printf("%sOK%s\n", GREEN, RESET);
    } else {
        printf("%sERROR%s: expected %d, got %d\n", RED, RESET, expected, result);
        tests_failed++;
    }
}

int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], "-color=false") == 0) {
        RED = "";
        GREEN = "";
        RESET = "";
    }

    int arr0[] = {};
    int arr1[] = {0, 1, 2, 3, 4};
    int arr2[] = {1, -2, 3, -4};
    int arr3[] = {1, 2, 3, 1};
    int arr4[] = {0, 0, 1, 2};
    int arr5[] = {3, 1, 5, 0, 2, 4};

    printf("Running tests...\n");

    run_test((uint64_t) INT32_MAX + 2, arr0, false, "Size to big");
    run_test(0, arr0, false, "Empty array");
    run_test(-1, arr0, false, "Negative size");
    run_test(5, arr1, true, "Consecutive numbers 0 to 4");
    run_test(4, arr2, false, "Negative numbers");
    run_test(4, arr3, false, "Duplicate numbers");
    run_test(4, arr4, true, "Duplicate numbers 2");
    run_test(6, arr5, true, "Non-consecutive numbers 0 to 5");

    if (tests_failed > 0) {
        printf("%sTests failed%s: %d\n", RED, RESET, tests_failed);
        assert(false);
    } else {
        printf("%sAll tests passed!%s\n", GREEN, RESET);
    }

    return 0;
}
