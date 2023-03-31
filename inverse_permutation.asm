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
	js .bad_result
	not eax
	mov [rsi + rcx * 4 + 0], eax
	inc rdx
	cmp rdi, rdx
	jne .loop_permutation
	xor rdx, rdx
.loop_inverse_permutation:
	mov eax, [rsi + rdx * 4 + 0]
.loop_inverse_permutation_2:
    not eax
    cmp eax, edx
    je .step
    mov ecx, [rsi + rax * 4 + 0]
    mov [rsi + rax * 4 + 0], eax
    ;mov eax, ecx
    ;jne .loop_inverse_permutation_2
.step:
    mov [rsi + rdx * 4 + 0], eax
    inc rdx
    cmp rdi, rdx
    jne .loop_inverse_permutation

 	jmp .good_result

.good_result:
	mov rax, 1
	ret

.bad_result:
	mov rax, 0
	ret