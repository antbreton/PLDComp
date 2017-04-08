.text        
.globl main 
.type main, @function

main:

    pushq   %rbp 
    movq    %rsp, %rbp 
    subq    $40, %rsp 

    movq    $2, %rax
    movq    %rax, -8(%rbp)
    movq   $2, -16(%rbp)
    movq    -8(%rbp), %rax 
    xor    -16(%rbp), %rax
    cmpq   $0, %rax 
    sete   %al 
    movzbq %al, %rax 
    movq    %rax, -24(%rbp) 
    cmpq    $1, -24(%rbp) 
    je      blocIF_main 
    jmp     blocAfter_main 
 
 
blocIF_main:
    movq   $86, -32(%rbp)
    mov    -32(%rbp), %edi
    call   putchar
    movq   $10, -40(%rbp)
    mov    -40(%rbp), %edi
    call   putchar
    jmp     blocAfter_main 
 
blocAfter_main:

    leave
    ret

