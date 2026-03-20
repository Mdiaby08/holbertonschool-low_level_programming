section .data
    msg db "Hello, World", 10
    len equ $ - msg

section .text
    global _start

_start:
    mov rax, 1          ; syscall: write
    mov rdi, 1          ; file descriptor: stdout
    mov rsi, msg        ; address of message
    mov rdx, len        ; length of message
    syscall             ; perform write

    mov rax, 60         ; syscall: exit
    xor rdi, rdi        ; exit code 0
    syscall
