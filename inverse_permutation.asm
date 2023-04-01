global inverse_permutation

section .text

inverse_permutation:
	mov rax, rdi
	dec rax
	test rax, rax
	js .bad_result
	js .bad_result
	xor rdx, rdx
.loop_negative:
	test [rsi + rdx * 4 + 0], [rsi + rdx * 4 + 0]
	js .bad_result
	cmp edi, [rsi + rdx * 4 + 0]
	jle .bad_result
	inc rdx
	cmp rdi, rdx
	jne .loop_negative
	xor rdx, rdx
.loop_permutation:
	mov ecx, [rsi + rdx * 4 + 0]
	test ecx, ecx
	jns .not_checked
	not ecx
.not_checked:
	mov eax, [rsi + rcx * 4 + 0]
	test eax, eax
	js .bad_permutation
	not eax
	mov [rsi + rcx * 4 + 0], eax
	inc rdx
	cmp rdi, rdx
	jne .loop_permutation
	xor rdx, rdx
.loop_inverse_permutation:
    mov eax, [rsi + rdx * 4 + 0]
    test eax, eax
    jns .step
    not eax
    mov r8d, edx
    mov ecx, [rsi + rax * 4 + 0]
.reverse_cycle:
    test ecx, ecx
    jns .step
    mov [rsi + rax * 4 + 0], r8d
    mov r8d, eax
    not ecx
    mov eax, ecx
    mov ecx, [rsi + rax * 4 + 0]
    jmp .reverse_cycle
.step:
    inc rdx
    cmp rdi, rdx
    jne .loop_inverse_permutation
    jmp .good_result
.bad_permutation:
    xor rdx, rdx
.loop_reverse:
    mov eax, [rsi + rdx * 4 + 0]
    test eax, eax
    jns .positive3
    not eax
    mov [rsi + rdx * 4 + 0], eax
.positive3:
    inc rdx
    cmp rdi, rdx
    jne .loop_reverse
    jmp .bad_result
.good_result:
	mov eax, 1
	ret
.bad_result:
	mov eax, 0
	ret