.text        
.global main 

main_bb:

    pushq   %rbp 
    movq    %rsp, %rbp 
    subq    $24, %rsp 
    WMEM
    movq    O, %rax
    movq    %rax, -8(%rbp)
    WMEM
    movq    -8(%rbp), %rax
    movq    %rax, -16(%rbp)
    WMEM
    movq    K, %rax
    movq    %rax, -24(%rbp)
    WMEM
    movq    n, %rax
    movq    %rax, -8(%rbp)
    CALL
    call   putchar
    CALL
    call   putchar
    CALL
    call   putchar

    leave
    ret


