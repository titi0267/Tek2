BITS 64
SECTION .text
GLOBAL memcpy

memcpy:
        XOR     RAX, RAX
        XOR     RCX, RCX
        MOV     RAX, RDI

loop:
        CMP     RDX, RCX
        JE      end
        CMP     BYTE[RSI], 0
        JE      end
        MOV     AH, BYTE[RSI]
        MOV     BYTE[RDI], AH
        INC     RCX
        INC     RDI
        INC     RSI
        JMP     loop

end:
        RET
