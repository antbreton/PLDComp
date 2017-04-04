.text        
.global main 

main_bb:

    pushq   %rbp 
    movq    %rsp, %rbp 
    LDCONST
    movq   $107, %edi
    CALL
    call   putchar

    leave
    ret


