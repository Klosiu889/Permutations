global inverse_permutation

section .text

inverse_permutation:                        ; n zawarte w rdi, tablica zawarta w rsi, wynik w rax
	    mov     rax, rdi
	    dec     rax                         ; zmniejszenie n o pozwoli na sprawdzenie czy n jest nieujemne
	                                        ; i nie większe od INT_MAX32 + 1
	    test    rax, rax
	    js      .bad_result
	    xor     rdx, rdx                    ; przygotowanie licznika pętli
.loop_negative:                             ; pętla sprawdzająca czy wartości w tablicy są nieujemne i mniejsze od n
        mov     eax, [rsi + rdx * 4 + 0]
	    test    eax, eax
	    js      .bad_result                 ; jeśli wartość jest ujemna to zakończ funkcję
	    cmp     edi, eax
	    jle     .bad_result                 ; jeśli wartość jest większa lub równa n to zakończ funkcję
	    inc     rdx
	    cmp     rdi, rdx
	    jne     .loop_negative
	    xor     rdx, rdx                    ; przygotowanie licznika pętli
.loop_permutation:                          ; pętla sprawdzająca czy tablica jest permutacją
                                            ; sprawdzone elementy oznaczamy jako ujemne
	    mov     ecx, [rsi + rdx * 4 + 0]
	    test    ecx, ecx
	    jns     .not_checked
	    not     ecx
.not_checked:
	    mov     eax, [rsi + rcx * 4 + 0]
	    test    eax, eax
	    js      .bad_permutation            ; dwie wartości wskazują w to samo miejsce, nie jest to permutacja
	    not     eax
	    mov     [rsi + rcx * 4 + 0], eax
	    inc     rdx
	    cmp     rdi, rdx
	    jne     .loop_permutation
	    xor     rdx, rdx                    ; przygotowanie licznika pętli
.loop_inverse_permutation:                  ; pętla odwracająca permutację, oznacza elementy odwiedzone jako dodatnie
        mov     eax, [rsi + rdx * 4 + 0]
        test    eax, eax
        jns     .step                       ; jeśli wartość jest dodatnia to przejdź do następnego elementu
        not     eax                         ; zapamiętujemy i w r8d, p[i] w eax oraz p[p[i]] w ecx
        mov     r8d, edx
        mov     ecx, [rsi + rax * 4 + 0]
.reverse_cycle:                             ; pętla odwracająca cykl
        test    ecx, ecx
        jns     .step                       ; p[p[i]] jest odwiedzone, przejdź do następnego elementu
        mov     [rsi + rax * 4 + 0], r8d    ; p[p[i]] = i
        mov     r8d, eax                    ; zamieniamy i = p[i], p[i] = p[p[i]], p[p[i]] = p[p[p[i]]]
        not     ecx
        mov     eax, ecx
        mov     ecx, [rsi + rax * 4 + 0]
        jmp     .reverse_cycle
.step:                                      ; przejście do następnego elementu głównej pętli
        inc     rdx
        cmp     rdi, rdx
        jne     .loop_inverse_permutation
        jmp     .good_result
.bad_permutation:                           ; niepoprawna permutacja, odwracamy spowrotem na dodatnie
        xor     rdx, rdx                    ; przygotowanie licznika pętli
.loop_reverse:
        mov     eax, [rsi + rdx * 4 + 0]
        test    eax, eax
        jns     .positive
        not     eax                         ; jeśli wartość jest ujemna to zamień na dodatnią
        mov     [rsi + rdx * 4 + 0], eax
.positive:                                  ; liczba była dodatnia, przejście do następnego elementu
        inc     rdx
        cmp     rdi, rdx
        jne     .loop_reverse
        jmp     .bad_result
.good_result: ; poprawne zakończenie funkcji
	    mov     eax, 0x1
	    ret
.bad_result: ; niepoprawne zakończenie funkcji
	    mov     eax, 0x0
	    ret