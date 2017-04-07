.text        
.global main 

main:

    pushq   %rbp 
    movq    %rsp, %rbp 
    subq    $56, %rsp 
    movq    $2, %rax
    movq    %rax, -8(%rbp)
    movq   $2, %rdi
    movq    -8(%rbp), %rax 
    xor    -16(%rbp), %rax
    cmpq   $0, %rax 
    sete   %al 
    movzbq %al, %rax 
    movq    %rax, -24(%rbp) 
    jne blocELSE
blocIF:
    movq   $86, %rdi
    call   putchar
    movq   $10, %rdi
    call   putchar
    jmp blocAfter
blocAfter:
blocELSE:
blocAfter:

    leave
    ret


