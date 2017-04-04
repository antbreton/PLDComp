.text        
.global main 

main:

    pushq   %rbp 
    movq    %rsp, %rbp 
    subq    $24, %rsp 
    movq    $79, %rax
    movq    %rax, -8(%rbp)
    movq    -8(%rbp), %rax
    movq    %rax, -16(%rbp)
    movq    $75, %rax
    movq    %rax, -24(%rbp)
    movq    $110, %rax
    movq    %rax, -8(%rbp)
    call   putchar
    call   putchar
    call   putchar

    leave
    ret


