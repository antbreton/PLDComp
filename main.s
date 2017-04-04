.text        
.global main 

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

>>>>>>> 947642f6b50c953e652003e23a43887e9c22b91a

