.text        
.global main 

main_bb:

    pushq   %rbp 
    movq    %rsp, %rbp 
    subq    $16, %rsp 
    LDCONST
    movq   $105, %edi
    WMEM
    movq    -0(%rbp), %rax
    movq    %rax, -8(%rbp)
    LDCONST
    movq   $107, %edi
    WMEM
    movq    -0(%rbp), %rax
    movq    %rax, -8(%rbp)
    LDCONST
    movq   $106, %edi
    WMEM
    movq    -0(%rbp), %rax
    movq    %rax, -16(%rbp)

    leave
    ret


