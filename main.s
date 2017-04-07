.text        
.globl main 
.type main, @function

main:

    pushq   %rbp 
    movq    %rsp, %rbp 
    subq    $72, %rsp 
    mov    %rdi, -8(%rbp) 
    mov    %rsi, -16(%rbp) 

    movq    $6, %rax
    movq    %rax, -24(%rbp)
    movq    $10, %rax
    movq    %rax, -32(%rbp)
    movq    -32(%rbp), %rax
    subq    -24(%rbp), %rax
    movq    %rax, -48(%rbp)
    movq    -48(%rbp), %rax
    movq    %rax, -40(%rbp)
    movq    $4, %rax
    movq    %rax, -8(%rbp)
    movq    $6, %rax
    movq    %rax, -8(%rbp)
    movq    -40(%rbp), %rax
    addq    -8(%rbp), %rax
    movq    %rax, -72(%rbp)
    movq    -72(%rbp), %rax
    movq    %rax, -16(%rbp)

    leave
    ret


