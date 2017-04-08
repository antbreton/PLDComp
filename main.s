.text        
.global main 

main:

    pushq   %rbp 
    movq    %rsp, %rbp 
    subq    $72, %rsp 
    movq    $2, %rax
    movq    %rax, -8(%rbp)
    movq   $1, %rdi
    movq    -16(%rbp), %rax 
    xor    -8(%rbp), %rax
    cmpq   $0, %rax 
    sete   %al 
    movzbl %al, %rax 
    movq    %rax, -24(%rbp) 
    jne blocELSE
blocIF:
    movq   $86, %rdi
    call   putchar
    jmp blocAfter
blocELSE:
    movq   $70, %rdi
    call   putchar
blocAfter:
    movq   $10, %rdi
    call   putchar

    leave
    ret


