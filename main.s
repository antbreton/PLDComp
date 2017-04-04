.text        
.global main 

main:

    pushq   %rbp 
    movq    %rsp, %rbp 
    movl   $101, %edi
    call   putchar
    movl   $122, %edi
    call   putchar

    leave
    ret


