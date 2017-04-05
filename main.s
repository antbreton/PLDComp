.text        
.global main 

main:

    pushq   %rbp 
    movq    %rsp, %rbp 
    subq    $16, %rsp 
    movq    $2, %rax
    movq    %rax, -8(%rbp)
    movl   $1, %edi
    movq    -8(%rbp), %rax
    addq    %edi, %rax
    movq    %rax, -0(%rbp)
    movq    -8(%rbp), %rax
    movq    %rax, -16(%rbp)

    leave
    ret


