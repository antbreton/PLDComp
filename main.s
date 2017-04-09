.text        
.globl main 
.type main, @function

main:

    pushq   %rbp 
    movq    %rsp, %rbp 
    subq    $8, %rsp 

    movq    $105, %rax
    movq    %rax, -8(%rbp)
    mov    -8(%rbp), %edi
    call   putchar

    leave
    ret


