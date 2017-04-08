.text        
.globl main 
.type main, @function

main:

    pushq   %rbp 
    movq    %rsp, %rbp 
    subq    $56, %rsp 

    movq    $2, %rax
    movq    %rax, -8(%rbp)
    movl   $2, -16(%rbp)
    movq    -8(%rbp), %rax 
    xor    -16(%rbp), %rax
    cmpq   $0, %rax 
    sete   %al 
    movzbl %al, %rax 
    movq    %rax, -24(%rbp) 
    jne blocELSE
blocIF:
    movl   $86, -32(%rbp)
    mov    -32(%rbp), %edi
    call   putchar
    movl   $10, -40(%rbp)
    mov    -40(%rbp), %edi
    call   putchar
    jmp blocAfter
blocELSE:
    movl   $88, -48(%rbp)
    mov    -48(%rbp), %edi
    call   putchar
blocAfter:
    movl   $90, -56(%rbp)
    mov    -56(%rbp), %edi
    call   putchar

    leave
    ret


