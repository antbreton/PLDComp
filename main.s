.text        
.global main 

main:

    pushq   %rbp 
    movq    %rsp, %rbp 
    subq    $56, %rsp 
    movq    $99, %rax
    movq    %rax, -8(%rbp)
    movl   $101, -24(%rbp)
    call   putchar
    movl   $122, -40(%rbp)
    call   putchar
    movq    -56(%rbp), %rax
    movq    -8(%rbp), %rdi
    movq    %rdi, (%rax)
    call   putchar

    leave
    ret


