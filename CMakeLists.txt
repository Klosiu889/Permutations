cmake_minimum_required(VERSION 3.18)
project(Permutacja)

set(CMAKE_CXX_STANDARD 14)

enable_language(ASM_NASM)
if (CMAKE_ASM_NASM_COMPILER_LOADED)
    set(CAN_USE_ASSEMBLER TRUE)
    set(Test inverse_permutation.asm test.c)
endif (CMAKE_ASM_NASM_COMPILER_LOADED)

add_executable(test ${Test})