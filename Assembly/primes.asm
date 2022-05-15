;Name: David Zaydenberg
%include "io.inc"

section .data
msg1 db "Enter first number: ",0
msg2 db 10,"Enter second number: ",0
msg3 db 10,"The prime numbers = ",0
msg4 db 10,"Count = ",0

section .bss
lower resd 1
upper resd 1

section .text
global CMAIN
CMAIN:
    xor ecx,ecx
input:
    PRINT_STRING msg1
    GET_DEC 4,eax
    PRINT_DEC 4,eax
    mov [lower],eax
    PRINT_STRING msg2
    GET_DEC 4,eax
    PRINT_DEC 4,eax
    inc eax ;increse so it will count the last number
            ;and print it if it's a prime number.
    mov [upper],eax
    PRINT_STRING msg3
end_input:
    mov esi,eax ;save upper
    mov edi,[lower] ;save lower
next_num:
    cmp edi,esi ;lower vs upper
    jz finish
    mov ebx,2 ;starting divisible number
prime_calc_loop:
    cmp ebx,edi ;check all nums between 2-edi(lower)
    jz found
    xor edx,edx ;clear remainder
    mov eax,edi ;move for div
    div ebx
    cmp edx,0
    jnz found_one ;found divisible num.
    inc edi ;found divisible num, so continue
    jmp next_num
found_one: ;
    inc ebx ;divisible number (2->num)
    jmp prime_calc_loop          
end_found_one:    
found: 
    PRINT_DEC 4,edi
    PRINT_CHAR ' '
    inc dword[lower]
    inc edi ;the lower number
    inc ecx ;amount of primes
    jmp next_num
end_found:
finish:
    PRINT_STRING msg4
    PRINT_UDEC 4,ecx
    xor eax, eax
    ret
