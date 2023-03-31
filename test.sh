gcc -c -Wall -Wextra -std=c17 -O2 -o test.o test.c
gcc -z noexecstack -o test test.o inverse_permutation.o
