BITS 64
SECTION .text
GLOBAL memcpy

memcpy:
        XOR     RAX, RAX
        MOV     RAX, RDI

loop:
        CMP     RDX, RCX
        JE      end
        MOV     R8B, BYTE[RSI + RCX]
        MOV     BYTE[RAX + RCX], R8B
        INC     RCX
        JMP     loop

end:
        RET
