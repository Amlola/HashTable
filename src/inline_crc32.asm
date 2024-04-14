global FuncCrc32

section .text

FuncCrc32:
        movzx edx, BYTE [rdi]
        mov eax, -1
        test dl, dl
        je .return
.cycle:
        inc rdi
        crc32 eax, dl
        movzx edx, BYTE [rdi]
        test dl, dl
        jne .cycle
.return:
        ret
    