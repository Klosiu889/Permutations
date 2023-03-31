nasm -f elf64 -w+all -w+error -o inverse_permutation.o inverse_permutation.asm
gcc -c -Wall -Wextra -std=c17 -O2 -o test.o test.c
gcc -z noexecstack -o test test.o inverse_permutation.o

