;Name: David Zaydenberg
;ID: 319323721
;There is not possible way to have more than one number like this
%include "io.inc"

section .data
matrix: dd 12, 150, 78, -34, 67, 100, -4, 52, 1, 200, 56, 61
size: dd 12
amount: dd 0 ;Found
N: dd 3      ;Rows
M: dd 4      ;Cols

msg1: db "The number is: ",0
msg2: db "No such number!",0

section .bss
numbers: resd 1   ;1 number can only be in a matrix
arraysize: resd 1 ;Total size(num of values*4)
rowsize: resd 1   

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    call check_matrix
    call print_value
    xor eax, eax
    ret
;--------------Check_Matrix--------------;
check_matrix:
    enter 0,0                  
    pusha
    mov ebx,[size]             ;Holds num of values array
    shl ebx,2                  ;Get whole array size(num of values*4)
    mov [arraysize],ebx        ;Save it
    shr ebx,2                  ;Return the amount of values
    mov edx,[M]                ;Max Cols
    shl ebx,2                  ;values*4 = size of whole array
    shl edx,2                  ;Get row size(cols*4)
    mov [rowsize],edx          ;save rowsize
    shr edx,2                  ;return to max cols
    xor edi,edi                ;Rows
    xor esi,esi                ;Cols
    xor ecx,ecx                ;index for numbers found array
find_numbers:
    cmp edi,ebx                ;compare rows
    je end_find_numbers
    cmp esi,edx                ;compare cols
    je equal_cols
    push dword[matrix+edi+esi*4];Push current value into the stack
    push edi                   ;Push current row
    push esi                   ;Push current col
    call check_row
    cmp eax,1                  ;Check if returned number is 1(valid),0(invalid)
    jne next_number
    push dword[matrix+edi+esi*4];Push current value into the stack
    push edi                   ;Push current row
    push esi                   ;Push current col
    call check_col
    cmp eax,1                  ;Check if returned number is 1(valid),0(invalid)
    je both_valid              ;If we found a number we skip the whole row
next_number:
    inc esi                 
    jmp find_numbers
end_next_number:
both_valid:
    mov eax,[matrix+edi+esi*4] ;Get the number
    mov [numbers + ecx*4],eax  ;and move it to numbers array
    inc ecx                    ;Save that we found the nubmer!
    jmp end_find_numbers       ;We don't need to search anymore because there can be only one
end_both_valid:
equal_cols:
    mov esi,[rowsize]          ;Get saved size of row
    add edi,esi                ;Next row
    xor esi,esi                ;Reset cols
    jmp find_numbers
end_equal_cols:
end_find_numbers:
    mov [amount],ecx           ;save the amount if we found or not
    popa
    leave
    ret
end_check_matrix:
;--------------Check_Row--------------;
check_row:
    enter 4,0
    pusha
    mov eax,[ebp+16]           ;Value we search
    mov edi,[ebp+12]           ;row number
    mov esi,[M]                ;Num of cols
    xor edx,edx                ;Cols index
find_num_in_row:
    cmp edx,esi
    je found_num_in_row
    mov ebx,[matrix+edi+edx*4]
    cmp eax,ebx
    jl failed_row
    inc edx                    ;next col
    jmp find_num_in_row
found_num_in_row:
    mov dword[ebp-4],1
    jmp end_find_num_in_row
end_found_num_in_row:
failed_row:
    mov dword[ebp-4],0
end_failed_row:
end_find_num_in_row:
    popa
    mov eax,[ebp-4]
    leave
    ret 12
end_check_row:
;--------------Check_Col--------------;
check_col:
    enter 4,0
    pusha
    mov eax,[ebp+16]           ;Value we search
    mov edi,[ebp+8]            ;Col number
    xor ecx,ecx                ;Curr row
    mov esi,[rowsize]          ;Get rowsize
    mov edx,[arraysize]        ;Get Array size
find_num_in_col:
    cmp ecx,edx                ;compare current row with last row size
    je found_num_in_col
    mov ebx,[matrix+ecx+edi*4]
    cmp eax,ebx
    jg failed_col
    add ecx,esi                ;next row
    jmp find_num_in_col
found_num_in_col:
    mov dword[ebp-4],1
    jmp end_failed_col
end_found_num_in_col:
failed_col:
    mov dword[ebp-4],0
end_failed_col:
end_find_num_in_col:  
    popa
    mov eax,[ebp-4]
    leave
    ret 12
end_check_col:
;--------------print_value--------------;
print_value:
    enter 0,0
    pusha
    mov ebx,[amount] ;amount of numbers found
    cmp ebx,0
    jne end_empty
empty:
    PRINT_STRING msg2
    jmp if_empty
end_empty:
    PRINT_STRING msg1
    PRINT_DEC 4,[numbers]
if_empty:
    popa
    leave
    ret
end_print_value:
;----------------END------------------;