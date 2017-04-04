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

>>>>>>> 903b5334776443f66bb7d90c59bcc04996ccdf3e

