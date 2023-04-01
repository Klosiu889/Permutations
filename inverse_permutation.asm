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
	cmp word [rsi + rdx * 4 + 0], 0
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
.make_positive:
    mov eax, [rsi + rdx * 4 + 0]
    not eax
    mov [rsi + rdx * 4 + 0], eax
    inc rdx
    cmp rdi, rdx
    jne .make_positive
	xor rdx, rdx
.loop_inverse_permutation:
	mov eax, [rsi + rdx * 4 + 0]
    cmp eax, edx
    je .step
    cmp [rsi + rax * 4 + 0], edx
    je .step
    mov ecx, edx
    mov r9d, eax
.permutation_cycle:
    mov r8d, eax
    mov eax, [rsi + rax * 4 + 0]
    mov [rsi + rcx * 4 + 0], eax
    mov ecx, r8d
    cmp r9d, ecx
    jne .permutation_cycle
    mov [rsi + rcx * 4 + 0], r9d
.step:
    mov [rsi + rdx * 4 + 0], eax
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