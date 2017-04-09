.text        
.globl main 
.type main, @function

main:

    pushq   %rbp 
    movq    %rsp, %rbp 
    subq    $104, %rsp 

    movq    $2, %rax
    movq    %rax, -8(%rbp)
    movq   $2, -16(%rbp)
    movq    -8(%rbp), %rax 
    cmp    -16(%rbp), %rax 
    setl   %al  
    movzbq %al, %rax 
    movq    %rax, -48(%rbp) 
    jne blocELSE_0
blocIF_0:
    movq   $86, -56(%rbp)
    mov    -56(%rbp), %edi
    call   putchar
    jmp blocAfter_0
blocELSE_0:
    movq   $70, -64(%rbp)
    mov    -64(%rbp), %edi
    call   putchar
blocAfter_0:
    movq   $1, -72(%rbp)
    movq    -8(%rbp), %rax 
    cmp    -72(%rbp), %rax 
    setl   %al  
    movzbq %al, %rax 
    movq    %rax, -80(%rbp) 
    jne blocELSE_1
blocIF_1:
    movq   $86, -88(%rbp)
    mov    -88(%rbp), %edi
    call   putchar
    jmp blocAfter_1
blocELSE_1:
    movq   $70, -96(%rbp)
    mov    -96(%rbp), %edi
    call   putchar
blocAfter_1:
    movq   $3, -104(%rbp)
    movq    -8(%rbp), %rax 
    cmp    -104(%rbp), %rax 
    setl   %al  
    movzbq %al, %rax 
    movq    %rax, -24(%rbp) 
    jne blocELSE_2
blocIF_2:
    movq   $86, -32(%rbp)
    mov    -32(%rbp), %edi
    call   putchar
    jmp blocAfter_2
blocELSE_2:
    movq   $70, -40(%rbp)
    mov    -40(%rbp), %edi
    call   putchar
blocAfter_2:

    leave
    ret


