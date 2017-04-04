
.text        
.global main 

main_bb:

    pushq   %rbp 
    movq    %rsp, %rbp 
<<<<<<< HEAD
    subq    $0, %rsp 

movq $0, -0(%rbp)
movq $0, -0(%rbp)
movq $0, -0(%rbp)
    movq   $105, -0(%rbp)
    movq    0(%rbp), %rax
    movq    %rax, -0(%rbp)
    movq   $107, -0(%rbp)
    movq    0(%rbp), %rax
    movq    %rax, -0(%rbp)
=======
    movq   $107, 0(%rbp)
    call   0(%rbp)
>>>>>>> 356ed6db7f8acab2dba9a5a0958150c62ece2946

    leave
    ret



