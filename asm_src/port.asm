global insw
global outsw

insw:
    pushl   %edi
    movl    8(%esp), %edx  # port
    movl    12(%esp), %edi # addr
    movl    16(%esp), %ecx # count

    xorl    %eax, %eax
.insw_startLoop:
    cmpl    %eax, %ecx
    je      .insw_end

    insw

    incl    %eax
    jmp     .insw_startLoop

.insw_end:
    popl    %edi
    ret

outsw:
    pushl   %esi
    movl    8(%esp), %edx  # port
    movl    12(%esp), %esi # addr
    movl    16(%esp), %ecx # count

    xorl    %eax, %eax
.outsw_startLoop:
    cmpl    %eax, %ecx
    je      .outsw_end

    outsw

    incl    %eax
    jmp     .outsw_startLoop

.outsw_end:
    popl    %esi
    ret
