;Program takes input of whole negative and positive numbers
;until 0, negates the negative numbers and sums them up.
;Name: David Zaydenberg
%include "io.inc"

section .data
    msg1 db "Enter a number: ",0
    msg2 db "You entered ",0
    msg3 db " numbers.",10,0
    msg4 db "The sum is: ",0
 
section .text
global CMAIN
CMAIN:
    xor edx,edx   ;Compare to 0
    xor ecx,ecx   ;Counter
    xor ebx,ebx   ;Sum of numbers
input_loop:
    GET_DEC 4,eax ;Input
    cmp eax,edx   ;If 0 end loop
    jz end_input
    js negative   ;If negative
after_convert:
    add ebx,eax   ;Sum each input
    inc ecx       ;increase num of inputs
    jmp input_loop
negative:
    neg eax       ;Make Possitive
    jmp after_convert ;Continue
end_input:
    PRINT_STRING msg2
    PRINT_DEC 4,ecx ;Print counter
    PRINT_STRING msg3
    NEWLINE
    PRINT_STRING msg4
    PRINT_DEC 4,ebx ;Print total sum
    xor eax, eax
    ret
