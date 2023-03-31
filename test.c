#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>

// Ten plik zawiera przykład użycia funkcji:
bool inverse_permutation(size_t n, int *p);

int tests_failed = 0;

void run_test(int *arr, size_t n, int expected, char* name) {
    printf("Test %s:    ", name);
    bool result = inverse_permutation(n, arr);
    if (result == expected) {
        printf("OK\n");
    } else {
        printf("ERROR: expected %d, got %d\n", expected, result);
        tests_failed++;
    }
}

int main () {
	int arr[] = {0, 1, 2, 3, 4};
	int arr2[] = {1, -2, 3, -4};
	int arr3[] = {1, 2, 3, 1};
    int arr4[] = {0, 0, 1, 2};
    int arr5[] = {3, 1, 5, 0, 2, 4};

    printf("Running tests...\n");

    run_test(arr, -1, false, "Negative size");
    run_test(arr, 5, true, "Consecutive numbers 0 to 4");
    run_test(arr2, 4, false, "Negative numbers");
    run_test(arr3, 4, false, "Duplicate numbers");
    run_test(arr4, 4, false, "Duplicate numbers 2");
    run_test(arr5, 6, true, "Non-consecutive numbers 0 to 5");

    if (tests_failed > 0) printf("Tests failed: %d\n", tests_failed);
    else printf("All tests passed!\n");

	return 0;
}
