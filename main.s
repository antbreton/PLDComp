.text        
.global main 

main:

    pushq   %rbp 
    movq    %rsp, %rbp 
    subq    $16, %rsp 

    leave
    ret


