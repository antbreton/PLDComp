.text        
.globl main 

main_bb:

    pushq   %rbp 
    movq    %rsp, %rbp 
    subq    $16, %rsp 
    WMEM
    movq    $2, %rax
    movq    %rax, -8(%rbp)
    WMEM
    movq    , %rax
    movq    %rax, -16(%rbp)

    leave
    ret


