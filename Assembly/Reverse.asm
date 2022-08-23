;Name: David Zaydenberg
;Program prints inputed string reversed 
%include "io.inc"

section .data
    msg1 db "Enter a string:",10,0
    msg2 db "The reversed string is: ",0

section .bss
    string resb 100

section .text
global CMAIN
CMAIN:
    PRINT_STRING msg1     ;Print the first message
    GET_STRING string,99  ;Input
    xor edi,edi           ;reset edi(counter for the string)
    mov esi,-1            ;Compare with edi counter when printing
find_end_of_string:
    inc edi 
    cmp byte[string+edi],0 ;When we get to the end of the string
    jnz find_end_of_string 
end_find:
    PRINT_STRING msg2     ;Print the second message
    dec edi               ;Decrese index by 1 because it stand on NULL
reverse:
    mov al,byte[string+edi] ;Move the char to al to print
    PRINT_CHAR al
    dec edi               ;Go down in the array
    cmp esi,edi           ;if -1 = -1 finish
    jnz reverse
end_reverse:
    xor eax, eax
    ret
