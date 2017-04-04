.text        
.global main 

main_bb:

    pushq   %rbp 
    movq    %rsp, %rbp 
    LDCONST
    movl   $107, %edi
    CALL
    call   putchar

    leave
    ret


