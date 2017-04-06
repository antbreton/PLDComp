.text        
.global main 

main:

    pushq   %rbp 
    movq    %rsp, %rbp 
    subq    $56, %rsp 
    movq   $1, %rdi
    movq   $2, %rdi
    movq    -8(%rbp), %rax 
    xor    -16(%rbp), %rax
    cmpq   $0, %rax 
    sete   %al 
    movzbl %al, %rax 
    movq    %rax, -24(%rbp) 
    movq   $86, %rdi
    call   putchar
    movq   $70, %rdi
    call   putchar

    leave
    ret


