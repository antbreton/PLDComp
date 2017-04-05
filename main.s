.text        
.global main 

main:

    pushq   %rbp 
    movq    %rsp, %rbp 
    subq    $168, %rsp 
    movq    $77, %rax
    movq    %rax, -8(%rbp)
    movq   $1, %rdi
    movq    %rdi, %rax
    addq    -8(%rbp), %rax
    movq    %rax, -120(%rbp)
    movq   $1, %rdi
    movq    -120(%rbp), %rax
    addq    %rdi, %rax
    movq    %rax, -136(%rbp)
    movq    -136(%rbp), %rax
    movq    %rax, -16(%rbp)
    movq   $4, %rdi
    movq    -16(%rbp), %rax
    subq    %rdi, %rax
    movq    %rax, -160(%rbp)
    movq    -160(%rbp), %rax
    movq    %rax, -144(%rbp)
    movq    $10, %rax
    movq    %rax, -168(%rbp)
    movq    $9, %rax
    movq    %rax, -24(%rbp)
    movq    -40(%rbp), %rax
    movq    -24(%rbp), %rdi
    movq    %rdi, %rax
    call   putchar
    movq    -56(%rbp), %rax
    movq    -16(%rbp), %rdi
    movq    %rdi, %rax
    call   putchar
    movq   $32, %rdi
    call   putchar
    movq    -88(%rbp), %rax
    movq    -144(%rbp), %rdi
    movq    %rdi, %rax
    call   putchar
    movq    -112(%rbp), %rax
    movq    -168(%rbp), %rdi
    movq    %rdi, %rax
    call   putchar

    leave
    ret


