global enablePaging
global loadPageDirectory
enablePaging:
mov eax, cr0
or eax, 0x80000000 
mov cr0, eax
ret

jmp end

loadPageDirectory:
pop eax
mov cr3, eax
ret


end: