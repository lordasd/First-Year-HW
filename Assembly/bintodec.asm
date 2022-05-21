;Name: David Zaydenberg
;ID: 319323721
%include "io.inc"

section .data
msg1 db "Enter a number: ",0
msg2 db 10,"Bad number! try again.",10,0
msg3 db 10,"The decimal value is: ",0

section .text
global CMAIN
CMAIN:
    mov ecx,10  ;Division number
;-----------Input_Binary-----------;
input_binary:
    PRINT_STRING msg1
    GET_UDEC 4,eax
    PRINT_UDEC 4,eax
end_input_binary:
;----------Convert_to_dec----------;
convert_to_dec:
    xor ebx,ebx ;Decimal result
    mov edi,1   ;Mask
division_loop:
    cmp eax,0   ;Check if inputnum got to 0
    jz end_division_loop
    xor edx,edx ;Remainder reset
    div ecx     ;edx:eax/ecx
remainder_check:
    cmp edx,1
    jbe end_wrong_input ;If edx(remainder)is valid(>1)jump
wrong_input:
    PRINT_STRING msg2
    jmp input_binary
end_wrong_input:
    jne finish_round ;If edx(remainder)is 0 jump back
    or ebx,edi    ;If remainder is 1
finish_round:
    shl edi,1
    jmp division_loop
end_division_loop:    
end_remainder_check:
end_convert_to_dec:
;---------Print_Dec_Value---------;
print_dec_value:
    PRINT_STRING msg3
    PRINT_UDEC 4,ebx
    ret
end_print_dec_value: