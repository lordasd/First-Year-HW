Program takes input of a numbers(until 0) and
calculates the amount of turned of bits(1) it has
and saves the number with the most bits turned on(1)
and prints the number, amount of turned on bits(1) and the index.
Porgram also prints how many even and negative number there are.
%include "io.inc"

section .data
msg1 db "Enter a number: ",0
msg2 db "The number is: ",0
msg3 db 10,"Number of bits = ",0
msg4 db 10,"Even Numbers = ",0
msg5 db 10,"Negative numbers = ",0

section .bss
max_bit_number resd 1

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    xor edx,edx ;Amount of bits
    xor edi,edi ;Amount of even numbers
    xor esi,esi ;Amount of negative numbers
    call input_numbers
    call print_results
    xor eax, eax
    ret
;-------------Input_numbers---------------;
input_numbers:
input_loop:
    PRINT_STRING msg1
    GET_DEC 4,eax
    PRINT_DEC 4,eax
    NEWLINE
    cmp eax,0
    je end_input_loop
    ;-----Call for task checks---;
    call check_even
    call check_negative
    call check_num_of_bits
    ;----------------------------;
    jmp input_loop
end_input_loop:
    ret
end_input_numbers:
;-------------Check_num_of_bits-----------;
check_num_of_bits:
    mov ecx,32 ;for 32bit rotation
    xor ebx,ebx ;bit(1)count
count_bits:
    rol eax,1 ;rotate left and save carry
    adc ebx,0 ;count all the carries(bits of eax)
    loop count_bits
end_count_bits:
    cmp ebx,edx ;If bigger, save new number
    jb end_bigger
bigger:
    mov [max_bit_number],eax ;Save the number with most bits
    mov edx,ebx ;Save the number of bits
end_bigger:
    ret
end_check_num_of_bits:
;-------------Check_Even------------------;
check_even:
    mov ebx,eax
    and ebx,0x1 ;if and = 0, num is even
    jnz end_even
even:
    inc edi
end_even:
    ret
end_check_even:   
;-------------Check_Negative--------------;
check_negative:
    test eax,eax ;just tests(AND operation) for sign flag
    jns end_negative
negative:
    inc esi
end_negative:
    ret
end_check_negative:
;------------Print_Results----------------;
print_results:
    PRINT_STRING msg2
    mov ebx,[max_bit_number];take out the number to print
    PRINT_DEC 4,ebx
    PRINT_STRING msg3
    PRINT_UDEC 4,edx
    PRINT_STRING msg4
    PRINT_UDEC 4,edi
    PRINT_STRING msg5
    PRINT_UDEC 4,esi
    ret
end_print_results:
;-----------------END---------------------;
