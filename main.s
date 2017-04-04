.text        
.global main 

fonction1_bb:

    pushq   %rbp 
    movq    %rsp, %rbp 
    subq    $0, %rsp 


    leave
    ret

main_bb:

    pushq   %rbp 
    movq    %rsp, %rbp 
    subq    $0, %rsp 


    leave
    ret


