;Program is taking numbers until 0 and finds the highets
;summed digits of a number and prints out the number,
;sum of sigits and the index.
;Name: David Zaydenberg
%include "io.inc"

section .data
msg1: db "Enter a number: ",10,0
msg2: db "The number is ",0
msg3: db 10,"The sum is ",0
msg4: db 10,"The location is ",0

section .bss
max_number: resd 1
max_sum: resd 1
location: resd 1

section .text
global CMAIN
CMAIN:
    mov dword[max_number],0   ;Set 0 all vars
    mov dword[max_sum],0
    mov dword[location],0
    mov ebx,10                ;num will be divided by 10
    mov esi,1                 ;index
input_loop:
    PRINT_STRING msg1
    GET_DEC 4,eax             ;input of the number
    cmp eax,0
    jz end_input_loop
    mov edi, eax              ;save the num before changes
    xor ecx,ecx               ;sum of digits reset
sum:
    xor edx,edx               ;contain the remainder
    div ebx                   ;edx:eax / ebx = eax whole num, edx remainder
    add ecx,edx
    cmp eax,0                 ;if eax came to an end
    jnz sum                   ;if eax isn't zero
end_sum:
    cmp ecx,[max_sum]         ;Compare if bigger than biggest saved
    jl smaller                ;if not bigger
bigger:
    mov [max_number], edi
    mov [max_sum], ecx
    mov [location], esi
    inc esi                   ;next index
    jmp input_loop
end_bigger:
smaller:
    inc esi                   ;next index
    jmp input_loop
end_smaller:
end_input_loop:
print:
    PRINT_STRING msg2
    PRINT_UDEC 4,[max_number]
    PRINT_STRING msg3
    PRINT_UDEC 4,[max_sum]
    PRINT_STRING msg4
    PRINT_UDEC 4,[location]
    NEWLINE
end_print:
    xor eax, eax
    ret
