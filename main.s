.text        
.globl main 
.type main, @function

main:

    pushq   %rbp 
    movq    %rsp, %rbp 
    subq    $16, %rsp 
    movq    $2, %rax
    movq    %rax, -8(%rbp)
    movq    f, %rax
    movq    %rax, -16(%rbp)

    leave
    ret


