.text        
.global main 

main_bb:

    pushq   %rbp 
    movq    %rsp, %rbp 
    subq    $0, %rsp 

movq $0, -0(%rbp)
movq $0, -0(%rbp)
    movq   $107, 0(%rbp)
    call   putchar

    leave
    ret


