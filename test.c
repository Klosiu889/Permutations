#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>

// Ten plik zawiera przykład użycia funkcji:
int inverse_permutation(size_t n, int *p);

int main () {
	int arr[] = {0, 1, 2, 3, 4};
	int arr2[] = {1, -2, 3, -4};
	int arr3[] = {1, 2, 3, 1};

	int res = inverse_permutation(5, arr);
	printf("%d\n", res);
	res = inverse_permutation(4, arr2);
	printf("%d\n", res);
	res = inverse_permutation(4, arr3);
	printf("%d\n", res);
	return 0;
}
