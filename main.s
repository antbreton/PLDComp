.text        
.globl main 
.type main, @function

main:

    pushq   %rbp 
    movq    %rsp, %rbp 
    subq    $120, %rsp 

    movq    $2, %rax
    movq    %rax, -8(%rbp)
    movq   $2, -16(%rbp)
    movq    -8(%rbp), %rax 
    cmp    -16(%rbp), %rax 
    setl   %al  
    movzbq %al, %rax 
    movq    %rax, -64(%rbp) 
    cmpq    $1, -64(%rbp) 
    jne blocELSE_0
blocIF_0:
    movq   $86, -72(%rbp)
    mov    -72(%rbp), %edi
    call   putchar
    jmp blocAfter_0
blocELSE_0:
    movq   $70, -80(%rbp)
    mov    -80(%rbp), %edi
    call   putchar
blocAfter_0:
    movq   $1, -96(%rbp)
    movq    -88(%rbp), %rax 
    cmp    -96(%rbp), %rax 
    setl   %al  
    movzbq %al, %rax 
    movq    %rax, -104(%rbp) 
    cmpq    $1, -104(%rbp) 
    jne blocELSE_1
blocIF_1:
    movq   $86, -112(%rbp)
    mov    -112(%rbp), %edi
    call   putchar
    jmp blocAfter_1
blocELSE_1:
    movq   $70, -120(%rbp)
    mov    -120(%rbp), %edi
    call   putchar
blocAfter_1:
    movq   $3, -32(%rbp)
    movq    -24(%rbp), %rax 
    cmp    -32(%rbp), %rax 
    setl   %al  
    movzbq %al, %rax 
    movq    %rax, -40(%rbp) 
    cmpq    $1, -40(%rbp) 
    jne blocELSE_2
blocIF_2:
    movq   $86, -48(%rbp)
    mov    -48(%rbp), %edi
    call   putchar
    jmp blocAfter_2
blocELSE_2:
    movq   $70, -56(%rbp)
    mov    -56(%rbp), %edi
    call   putchar
blocAfter_2:

    leave
    ret


