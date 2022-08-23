;Program takes input of a character(A-Z) else will return, error
;until valid input, and print a triangle that goes from A-'input char'
;Name: David Zaydenberg
%include "io.inc"

section .data
inputmsg: db "Enter a character: ",0
errormsg: db 10,"Error: Wrong input",10,0
outputmsg: db 10,"The triangle is:",10,0

section .text
global CMAIN
CMAIN:
    mov ecx, 1          ;amount of prints(adding 2 each time)
Input: 
    PRINT_STRING inputmsg
    GET_CHAR eax
check_if_valid:
    cmp eax,90
    jg error            ;Error if greater than 90
    cmp eax, 65
    jl error            ;Error if less than 65
    jmp end_error
error:
    PRINT_STRING errormsg
    jmp Input           ;Jump to input again
end_error:    
end_check_if_valid:
    mov ebx, eax        ;save char
    sub eax, 64         ;Get the distance from A-1
    dec eax             ;spaces should be rows-1
    mov esi, eax        ;insert spaces
    mov eax, 'A'
end_input:
    PRINT_STRING outputmsg
print_loop_outer:
    cmp eax, ebx        ;If the starting character > than last
    jg end_print_loop_outer
    mov edi, esi
inner_space_loop:
    cmp edi, 0
    jz end_inner_space_loop
    PRINT_CHAR ' '
    dec edi
    jmp inner_space_loop
end_inner_space_loop:
    mov edi, ecx        ;prepare amount of prints
inner_print_loop:
    PRINT_CHAR eax
    dec edi             ;decrese amount of prints
    cmp edi,0
    jnz inner_print_loop
end_inner_print_loop:
    add ecx, 2          ;increse amount of char prints
    inc eax             ;increse the char
    dec esi
    NEWLINE
    jmp print_loop_outer
end_print_loop_outer:
    xor eax, eax
    ret
