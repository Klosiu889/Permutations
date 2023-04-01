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
bool debug = false;

void check_flags(int argc, char **argv) {
    switch (argc) {
        case 1:
            break;
        case 2:
            if (strcmp(argv[1], "-debug") == 0) {
                debug = true;
            } else if (strcmp(argv[1], "-color=false") == 0) {
                RED = "";
                GREEN = "";
                RESET = "";
            } else {
                printf("Unknown flag");
                exit(1);
            }
        case 3:
            if (strcmp(argv[1], "-debug") == 0 ||
                strcmp(argv[2], "-debug") == 0) {
                debug = true;
            } else if (strcmp(argv[1], "-color=false") == 0 ||
                       strcmp(argv[2], "-color=false") == 0) {
                RED = "";
                GREEN = "";
                RESET = "";
            } else {
                printf("Unknown flag");
                exit(1);
            }
            break;
        default:
            printf("Too many flags");
            exit(1);
    }
}

void write_array(size_t n, int *arr) {
    printf("[");
    for (size_t i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i != n - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void run_test(size_t n, int *arr, bool expected, char *name) {
    int *arr_copy = (int *) malloc(n * sizeof(int));
    //if (n < (sizen > 0) memcpy(arr_copy, arr, n * sizeof(int));

    bool result = inverse_permutation(n, arr);

    bool result_array = true;
    /*for (size_t i = 0; i < n && result; i++) {
        if (arr_copy[arr[i]] != i) {
            result_array = false;
            break;
        }
    }*/

    if (result == expected && result_array) {
        printf("%sOK   %s", GREEN, RESET);
    } else {
        printf("%sERROR%s", RED, RESET);
        if (debug && result) {
            void write_array(size_t n, int *arr) {
                printf("[");
                for (size_t i = 0; i < n; i++) {
                    printf("%d", arr[i]);
                    if (i != n - 1) {
                        printf(", ");
                    }
                }
                printf("]\n");
            }
        }
        tests_failed++;
    }
    printf("    %s\n", name);
}

int main(int argc, char **argv) {
    check_flags(argc, argv);

    int empty_arr[] = {};
    int consecutive_numbers_array[] = {0, 1, 2, 3, 4};
    int negative_numbers[] = {1, -2, 3, -4};
    int too_big_numbers[] = {1, 2, 3, 4};
    int too_big_numbers2[] = {1, 2, 3, 5};
    int duplicate_numbers[] = {1, 2, 3, 1};
    int duplicate_numbers2[] = {0, 0, 1, 2};
    int correct_permutation[] = {3, 1, 5, 0, 2, 4};
    int correct_permutation2[] = {3, 1, 5, 0, 2, 4, 6};
    int correct_permutation3[] = {64, 62, 56, 61, 7, 25, 34, 43, 30, 42, 45, 60,
                                  16, 46, 29, 8, 11, 18, 32, 57, 12, 44, 52, 21,
                                  36, 66, 24, 48, 5, 27, 59, 51, 20, 2, 22, 38,
                                  14, 23, 41, 4, 33, 35, 3, 47, 13, 54, 55, 15,
                                  39, 58, 50, 1, 17, 40, 53, 9, 28, 49, 63, 10,
                                  6, 0, 31, 19, 26, 65, 37};


    printf("Running tests...\n");

    run_test((uint64_t) INT32_MAX + 2, empty_arr, false, "Size to big");
    run_test(0, empty_arr, false, "Empty array");
    run_test(-1, empty_arr, false, "Negative size");
    run_test(4, negative_numbers, false, "Negative numbers");
    run_test(4, too_big_numbers, false, "Too big numbers");
    run_test(4, too_big_numbers2, false, "Too big numbers 2");
    run_test(5, consecutive_numbers_array, true, "Consecutive numbers 0 to 4");
    run_test(6, correct_permutation, true, "Correct permutation");
    run_test(4, duplicate_numbers, false, "Duplicate numbers");
    run_test(4, duplicate_numbers2, false, "Duplicate numbers 2");
    run_test(7, correct_permutation2, true, "Correct permutation 2");
    run_test(67, correct_permutation3, true, "Correct permutation 3");

    if (tests_failed > 0) {
        printf("%sTests failed%s: %d\n", RED, RESET, tests_failed);
        exit(1);
    } else {
        printf("%sAll tests passed!%s\n", GREEN, RESET);
    }

    return 0;
}