.text        
.globl main 
.type main, @function

main:

    pushq   %rbp 
    movq    %rsp, %rbp 
    subq    $32, %rsp 
    movq    $2, %rax
    movq    %rax, -8(%rbp)
    movl   $1, -24(%rbp)
    movq    -8(%rbp), %rax
    addq    -24(%rbp), %rax
    movq    %rax, -32(%rbp)
    movq    -32(%rbp), %rax
    movq    %rax, -16(%rbp)

    leave
    ret


