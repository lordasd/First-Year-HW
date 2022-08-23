;Name: David Zaydenberg
%include "io.inc"

section .data
menu: db "        Menu    ",10,0
menu1: db "1) New String",10,0
menu2: db "2) Insert String",10,0
menu3: db "3) Replace String",10,0
menu4: db "4) Erase String",10,0
menu5: db "5) Find Substring",10,0
menu6: db "6) Exit",10,0
msg1: db "Enter a new string: ",0
msg2: db 10,"Enter string to insert: ",0
msg3: db 10,"Enter string to replace: ",0
msg4: db 10,"Enter location: ",0
msg5: db 10,"How many characters?: ",0
msg6: db 10,"Enter string to find: ",0
msg7: db 10," was found ",0
msg8: db " times",10,0
msg9: db 10,"The string is: ",0

section .bss
string: resb 1000
sec_str: resb 1000
thrd_str: resb 1000

section .text
global CMAIN
CMAIN:
;----------------Main_Menu-----------------;
menu_loop:
    PRINT_STRING menu
    PRINT_STRING menu1
    PRINT_STRING menu2
    PRINT_STRING menu3
    PRINT_STRING menu4
    PRINT_STRING menu5
    PRINT_STRING menu6
    GET_UDEC 4,eax
    cmp eax,2
    je insert_str_call
    cmp eax,3
    je replace_str_call
    cmp eax,4
    je erase_str_call
    cmp eax,5
    je find_sub_str_call
    cmp eax,6
    je end_menu_loop
new_str_call:
    call new_str
    jmp menu_loop
end_new_str_call:
insert_str_call:
    call insert_str
    jmp menu_loop
end_insert_str_call:
replace_str_call:
    call replace_str
    jmp menu_loop
end_replace_str_call:
erase_str_call:
    call erase_str
    jmp menu_loop
end_erase_str_call:
find_sub_str_call:
    call find_sub_str
    jmp menu_loop
end_find_sub_str_call:
end_menu_loop:
    xor eax, eax
    ret
;----------------New_Str----------------;   
new_str:
    Enter 0,0
    pusha
    PRINT_STRING msg1
    GET_STRING string,100
    PRINT_STRING string
    popa
    leave
    ret
end_new_str:
;----------------Insert_Str----------------;
insert_str: 
    Enter 0,0
    pusha
    PRINT_STRING msg2
    GET_STRING sec_str,100
    PRINT_STRING sec_str
    PRINT_STRING msg4
    GET_UDEC 4,eax        ;Index to insert into string
    PRINT_UDEC 4,eax
    NEWLINE
    mov esi,string
    add esi,eax           ;Get the index to save the rest in thrd_str
    mov edi,thrd_str
    mov ebx,eax           ;save index before changes
store_end_str:
    cmp dword[esi],0
    je end_store_end_str
    lodsb
    stosb
    jmp store_end_str
end_store_end_str:
    mov edi,string
    mov esi,sec_str
    mov eax,ebx
    add edi,eax           ;Index to start insertion
insert_new_str:
    cmp dword[esi+1],0
    je end_insert_new_str
    lodsb
    stosb
    jmp insert_new_str
end_insert_new_str:
    mov dword[esi],0      ;Remove the \n for the middle added string 
    mov esi,thrd_str      ;Get the leftover to add to string
insert_leftover:
    cmp dword[esi],0
    je end_insert_leftover
    lodsb
    stosb
    jmp insert_leftover
end_insert_leftover:
    mov dword[edi],0           ;End the string with \0
    PRINT_STRING string
    popa
    leave
    ret
end_insert_str:    
;----------------Replace_Str----------------;
replace_str:
    Enter 0,0
    pusha
    PRINT_STRING msg3
    GET_STRING sec_str,100
    PRINT_STRING sec_str
    PRINT_STRING msg4
    GET_UDEC 4,ecx        ;Index to start from
    PRINT_UDEC 4,ecx
    NEWLINE
    cld
    mov esi,sec_str
    mov edi,string
    add edi,ecx
replace_loop:
    movsb
    cmp dword[esi+1],0
    jne replace_loop
end_replace_loop:
    PRINT_STRING string
    popa
    leave
    ret
end_replace_str:    
;----------------Erase_Str----------------;
erase_str:
    Enter 0,0
    pusha
    PRINT_STRING msg4
    GET_UDEC 4,ecx     ;Location/index
    PRINT_UDEC 4,ecx
    PRINT_STRING msg5
    GET_UDEC 4,eax     ;Length to remove
    PRINT_UDEC 4,eax
    NEWLINE
    mov edx,ecx
    add edx,eax        ;location+length
    mov esi,string
    add esi,edx        ;Get the location of the end of removal
    mov edi,sec_str
    cld
transfer_loop:
    cmp dword[esi],0
    je end_transfer_loop
    lodsb              ;load string into al
    stosb              ;store al into string
    jmp transfer_loop
end_transfer_loop:
    mov edi,string
    mov esi,sec_str
    add edi,ecx        ;Get the index to start fill
load_str:
    cmp dword[esi],0
    je end_load_str
    lodsb              ;load string into al
    stosb              ;store al into string
    jmp load_str
end_load_str:
    mov dword[edi],0   ;Make an end to the string
    PRINT_STRING string
    popa
    leave
    ret
end_erase_str:
;----------------Find_Sub_Str----------------; 
find_sub_str:
    Enter 0,0
    pusha
    PRINT_STRING msg6
    GET_STRING sec_str,100
    xor ecx,ecx
    mov esi,sec_str
    cld
find_sub_len:
    lodsb
    cmp al,10            ;End the length at "enter"
    je end_find_sub_len
    inc ecx
    jmp find_sub_len
end_find_sub_len:
    xor eax,eax          ;amount of appearance
    mov edi,string
    mov ebx,ecx          ;save the length
    cld
check_eq_loop:
    cmp dword[edi],10    ;check end of string
    je end_check_eq_loop
    mov ecx,ebx          ;reset the length of the sub_str
    mov esi,sec_str      ;reset the index of the sub_str
    repe cmpsb
    jne check_eq_loop
    inc eax              ;Found appearance
    jmp check_eq_loop
end_check_eq_loop:
    PRINT_STRING sec_str
    PRINT_STRING msg7
    PRINT_UDEC 4,eax
    PRINT_STRING msg8
    popa
    leave
    ret
end_find_sub_str:    
;--------------------End-------------------;