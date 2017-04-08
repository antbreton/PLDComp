.text        
.globl main 
.type main, @function

main:

    pushq   %rbp 
    movq    %rsp, %rbp 
    subq    $48, %rsp 

    movq    $2, %rax
    movq    %rax, -8(%rbp)
    movq   $6, -16(%rbp)
    movq    -8(%rbp), %rax 
    xor    -16(%rbp), %rax
    cmpq   $0, %rax 
    sete   %al 
    movzbq %al, %rax 
    movq    %rax, -24(%rbp) 
    jne blocELSE
blocIF:
    movq   $86, -32(%rbp)
    mov    -32(%rbp), %edi
    call   putchar
    movq   $10, -40(%rbp)
    mov    -40(%rbp), %edi
    call   putchar
    jmp blocAfter
blocELSE:
    movq   $88, -48(%rbp)
    mov    -48(%rbp), %edi
    call   putchar
blocAfter:

    leave
    ret


