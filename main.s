.text        
.globl main 
.type main, @function

main:

    pushq   %rbp 
    movq    %rsp, %rbp 
    subq    $24, %rsp 

    movq    $5, %rax
    movq    %rax, -8(%rbp)
    movq   $1, -16(%rbp)
    movq    -16(%rbp), %rax
    addq    -8(%rbp), %rax
    movq    %rax, -24(%rbp)
    movq    -24(%rbp), %rax
    movq    %rax, -8(%rbp)
    mov    -8(%rbp), %edi
    call   putchar

    leave
    ret


