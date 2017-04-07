.text        
.global main 

main:

    pushq   %rbp 
    movq    %rsp, %rbp 
    subq    $72, %rsp 
main:
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
    movq   $71, %rdi
    call   putchar
blocIF:
    jmp blocAfter
    movq   $86, %rdi
    call   putchar
blocELSE:
    movq   $70, %rdi
    call   putchar
blocAfter:

    leave
    ret


