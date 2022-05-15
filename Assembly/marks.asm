;Name: David Zaydenberg
;ID: 319323721
%include "io.inc"

section .data
msg1 db "Enter student name: ",0
msg2 db "Enter mark for algebra: ",0
msg3 db "Enter percent for algebra: ",0
msg4 db "Enter mark for chemistry: ",0
msg5 db "Enter percent for chemistry: ",0
msg6 db "Enter mark for computers: ",0
msg7 db "Enter percent for computers: ",0
msg8 db " grade is ",0
msg9 db "Error! The sum of percent not equal 100.Please try again!",10,0

section .bss
studname resb 10
name_len resb 1

section .text
global CMAIN
CMAIN:
    xor eax,eax ;Set 0 to all registers
    xor ebx,ebx
    xor ecx,ecx
    xor edi,edi
    xor esi,esi
Input: ;Input and output name, grades and percentage
    PRINT_STRING msg1
    GET_STRING studname,10
    mov ebx,10
loop_name_enter_finder: ;Find the index of "10"(enter) to insert 0 instead
    mov al,[studname+ecx]
    movzx eax,al
    cmp eax,ebx
    jz end_loop_name_enter_finder
    inc ecx
    jmp loop_name_enter_finder
end_loop_name_enter_finder: ;Save the length for the second print
    mov byte[studname+ecx],0
    xor ebx,ebx
    PRINT_STRING [studname]
    NEWLINE
fail_restart: ;If the percent sum incorrect, restart from here
    PRINT_STRING msg2
    GET_UDEC 4,eax
    PRINT_UDEC 4,eax
    NEWLINE
    PRINT_STRING msg3
    GET_UDEC 4,ecx
    PRINT_UDEC 4,ecx
    NEWLINE
    add edi,ecx ;edi = sum of percents(for validity check)
    mul ecx     ;eax = eax * ecx (mark*percent)
    add esi,eax ;esi = sum of marks
    
    PRINT_STRING msg4
    GET_UDEC 4,eax
    PRINT_UDEC 4,eax
    NEWLINE
    PRINT_STRING msg5
    GET_UDEC 4,ecx
    PRINT_UDEC 4,ecx
    NEWLINE
    add edi,ecx ;edi = sum of percents(for validity check)
    mul ecx     ;eax = eax * ecx (mark*percent)
    add esi,eax ;esi = sum of marks
    
    PRINT_STRING msg6
    GET_UDEC 4,eax
    PRINT_UDEC 4,eax
    NEWLINE
    PRINT_STRING msg7
    GET_UDEC 4,ecx
    PRINT_UDEC 4,ecx
    NEWLINE
    add edi,ecx ;edi = sum of percents(for validity check)
    mul ecx     ;eax = eax * ecx (mark*percent)
    add esi,eax ;esi = sum of marks
end_Input:
Valid_percent_check: ;if sum of percents is 100 continue, else restart
    cmp edi,100
    je end_error
end_valid_percent_check:
error:
    PRINT_STRING msg9
    jmp fail_restart
end_error:
    PRINT_STRING studname
    PRINT_STRING msg8
avg_calc: ;divide the sum of marks by 100
    mov eax,esi
    mov esi,100
    div esi
end_avg_calc:
    PRINT_UDEC 4,eax ;Print res before the dot
    PRINT_CHAR "."
    PRINT_UDEC 4,edx ;Print res after the dot(2 nums)
    xor eax, eax
    ret