format ELF64

public _start
public _syscall
public write
public exit

extrn main

section '.text' executable
_syscall:
        mov r10, rcx
        syscall
        ret

write:
        mov eax, 1
        jmp _syscall

exit:
        mov eax, 60
        jmp _syscall

_start:
        xor rbp, rbp
        pop rdi
        mov rsi, rsp
        mov rdi, 0
        mov rsi, 0
        call main

        mov edi, eax
        mov eax, 60
        syscall
