BITS 64
SECTION .text
GLOBAL memmove

memmove:
        XOR     RCX, RCX
        XOR     RAX, RAX

loop:
        CMP     RCX, RDX
        JE      copy
        MOV     AL, BYTE[RSI + RCX]
        PUSH    RAX
        INC     RCX
        JMP     loop

copy:
        CMP     RCX, 0
        JE      bf_end
        DEC     RCX
        POP     RAX
        MOV     BYTE[RDI + RCX], AL
        JMP     copy

bf_end:
        MOV     RAX, RDI

end:
        RET

