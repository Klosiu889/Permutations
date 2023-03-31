global inverse_permutation

section .text

inverse_permutation:
	mov rax, rdi
	test rax, rax
	js .bad_result
	mov rdx, 0
.loop_negative:
	cmp word [rsi + rdx * 4 + 0], 0 
	js .bad_result
	inc rdx
	cmp rdi, rdx
	jne .loop_negative
	mov rdx, 0
.loop_permutation:
	mov ecx, [rsi + rdx * 4 + 0]
	test ecx, ecx
	jns .positive
	not ecx
	mov eax, [rsi + rcx * 4 + 0]
	not ecx
	jmp .negative
.positive:
	mov eax, [rsi + rcx * 4 + 0]
.negative:
	test eax, eax
	js .bad_result
	not rax
	mov [rsi + rcx * 4 + 0], eax
	inc rdx
	cmp rdi, rdx
	jne .loop_permutation
	
	
	jmp .good_result

.good_result:
	mov rax, 1
	ret

.bad_result:
	mov rax, 0
	ret
