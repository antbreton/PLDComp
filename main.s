.text        
.globl aaaa 
.type aaaa, @function

aaaa:

    pushq   %rbp 
    movq    %rsp, %rbp 
    mov    %rdi, -16(%rbp) 
    mov    %rsi, -8(%rbp) 


    leave
    ret


