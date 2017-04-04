
.text        
.global main 

main_bb:

    pushq   %rbp 
    movq    %rsp, %rbp 
    movq   $107, 0(%rbp)
    call   0(%rbp)

    leave
    ret



