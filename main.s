.text        
.global main 

main_bb:

    pushq   %rbp 
    movq    %rsp, %rbp 
    subq    $8, %rsp 
    LDCONST
    movq   $2, %edi
    WMEM
    movq    -0(%rbp), %rax
    movq    %rax, -8(%rbp)

    leave
    ret


