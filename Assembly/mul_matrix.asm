;Name: David Zaydenberg
;ID: 319323721
%include "io.inc"

section .data
msg1: db "Enter number of rows of A: ",0
msg2: db 10,"Enter number of columns of A: ",0
msg3: db 10,"Enter number of rows of B: ",0
msg4: db 10,"Enter number of columns of B: ",0
msg5: db 10,"Enter ",0
msg6: db " numbers for A: ",0
msg7: db " numbers for B: ",0
msg8: db 10,"The matrix C is:",10,0
msg9: db 10,"Wrong input! Please try again.",10,0

section .bss
matrixA: resd 1000 ;mxn
sizeofArow: resd 1 ;Size of row A
matrixB: resd 1000 ;kxl
sizeofBrow: resd 1 ;Size of row B
currBrow: resd 1   ;Current size of B row
matrixC: resd 1000 ;mxl
sizeofC: resd 1    ;Size of C
m: resd 1     ;Rows A
n: resd 1     ;Cols A
k: resd 1     ;Rows B
l: resd 1     ;Cols B

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    call input_matrix_size
    call input_matrix_A
    call input_matrix_B
    call multiply_matrices
    call print_result_matrix
    xor eax, eax
    ret
    
;----------input_matrix_size---------;
input_matrix_size:
    PRINT_STRING msg1
    GET_UDEC 4,[m]
    PRINT_UDEC 4,[m]
    PRINT_STRING msg2
    GET_UDEC 4,eax
    PRINT_UDEC 4,eax
    mov [n],eax
    PRINT_STRING msg3
    GET_UDEC 4,ebx
    PRINT_UDEC 4,ebx
    mov [k],ebx
    PRINT_STRING msg4
    GET_UDEC 4,[l]
    PRINT_UDEC 4,[l]
A_B_rowcol_check:
    cmp eax,ebx ;Compare n&k (They have to be the same)
    je end_A_B_rowcol_check
    PRINT_STRING msg9
    jmp input_matrix_size
end_A_B_rowcol_check:
    ret
end_input_matrix_size:
;----------input_matrix_A------------;
input_matrix_A:
    mov eax,[n]
    shl eax,2   ;Get size of B row
    mov [sizeofArow],eax
    mov eax,[m] ;Rows A
    mov edi,[n] ;Cols A
    mul edi     ;Amount of numbers in matrix
    xor esi,esi ;Rows
    xor edx,edx ;Cols
    PRINT_STRING msg5
    PRINT_DEC 4,eax
    PRINT_STRING msg6
    shl eax,2   ;eax(num of values in marix)*4 bytes = last place
input_loop_A:
    cmp esi,eax ;Rows comparison
    je end_input_loop_A
    cmp edx,edi ;Column comparison
    jne end_cols_equal_A
cols_equal_A:
    shl edx,2   ;increase rows, multiply by 4(double)for next row
    add esi,edx ;add esi the location of the new row
    xor edx,edx ;reset columns
    NEWLINE
    jmp input_loop_A
end_cols_equal_A:    
    GET_DEC 4,ebx
    PRINT_DEC 4,ebx
    PRINT_CHAR " "
    mov [matrixA + esi + edx*4],ebx
    inc edx
    jmp input_loop_A
end_input_loop_A:
    ret
end_input_matrix_A:    
;----------input_matrix_B------------;
input_matrix_B:
    mov eax,[l]
    shl eax,2   ;Get size of B row
    mov [sizeofBrow],eax
    mov eax,[k] ;Rows A
    mov edi,[l] ;Cols A
    mul edi     ;Amount of numbers in matrix
    xor esi,esi ;Rows
    xor edx,edx ;Cols
    PRINT_STRING msg5
    PRINT_DEC 4,eax
    PRINT_STRING msg7
    shl eax,2   ;eax(num of values in marix)*4 bytes = last place
input_loop_B:
    cmp esi,eax ;Rows comparison
    je end_input_loop_B
    cmp edx,edi ;Column comparison
    jne end_cols_equal_B
cols_equal_B:
    shl edx,2   ;increase rows, multiply by 4(double)for next row
    add esi,edx ;add esi the location of the new row
    xor edx,edx ;reset columns
    NEWLINE
    jmp input_loop_B
end_cols_equal_B:
    GET_DEC 4,ebx
    PRINT_DEC 4,ebx
    PRINT_CHAR " "    
    mov [matrixB + esi + edx*4],ebx
    inc edx
    jmp input_loop_B
end_input_loop_B:
    ret
end_input_matrix_B:    
;---------multiply_matrices----------;
multiply_matrices:
    mov esi,[m] ;Max Rows
    mov edi,[l] ;Max columns
    xor ecx,ecx ;Rows
    xor ebx,ebx ;Columns
    mov eax,esi
    mul edi     ;num of values in matrixC
    mov esi,eax
    shl esi,2   ;result of esi*edi*4 bytes
    mov [sizeofC],esi ;esi holds last place of matrix
    xor eax,eax
outer_loop:
    cmp ecx,esi ;Row comparison
    je end_outer_loop
    cmp ebx,edi ;Column comparison
    je col_c_equal
inner_loop:
    push eax    ;Row for A
    push ebx    ;Col for B
    call calc_mat_cell
end_inner_loop:
    mov [matrixC + ecx + ebx*4],edx ;Result
    inc ebx
    jmp outer_loop
col_c_equal:
    shl ebx,2   ;ebx*4 to get the full row
    add ecx,ebx ;ecx = next row.
    xor ebx,ebx ;reset cols
    mov edx,[sizeofArow]
    add eax,edx ;next row for matrix A
    jmp outer_loop
end_col_c_equal:
end_outer_loop:    
    ret
end_multiply_matrices:
;------------Clac_Mat_Cell-----------;
calc_mat_cell:
    enter 4,0       ;Save result
    pusha
    xor eax,eax     ;result
    xor ecx,ecx     ;current col A
    xor edx,edx     ;current row B
    mov ebx,[ebp+12];Current row A
    mov edi,[ebp+8] ;Current Col B
    mov [ebp-4],eax
calc:
    mov esi,[n]     ;Col max A    
    cmp ecx,esi
    je end_calc
    mov eax,[matrixA + ebx + ecx*4]
    mov esi,[matrixB + edx + edi*4]
    mov [currBrow],edx ;Save current row before it resets
    mul esi         ;Get result
    mov edx,[currBrow]
    mov esi,[ebp-4] ;pull out result
    add eax,esi     ;sum the current res with the total res
    mov [ebp-4],eax
    inc ecx
    mov esi,[sizeofBrow]
    add edx,esi ;Next row to B
    jmp calc
end_calc:
    popa
    mov edx,[ebp-4]
    leave
    ret 8
end_calc_mat_cell:
;--------print_result_matrix---------;
print_result_matrix:
    mov ecx,[sizeofC] ;Rows
    mov edi,[l] ;Cols
    xor esi,esi ;Rows
    xor edx,edx ;Cols
    PRINT_STRING msg8
print_cols:
    cmp esi,ecx ;Rows comparison
    je end_print_cols
    cmp edx,edi ;Columns comparison
    jne end_cols_equal
cols_equal:
    shl edx,2   ;size of row
    add esi,edx ;increase rows    
    xor edx,edx ;reset columns
    NEWLINE
    jmp print_cols
end_cols_equal:
    PRINT_DEC 4,[matrixC + esi + edx*4]
    PRINT_CHAR ' ';Print space
    inc edx     ;Increase column index
    jmp print_cols
end_print_cols:
    ret
end_print_result_matrix:
;----------------END-----------------;