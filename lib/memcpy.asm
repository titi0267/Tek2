BITS 64
SECTION .text
GLOBAL memcpy

memcpy:
        XOR     RCX, RCX

loop:
        CMP     RDX, RCX
        JE      end
        MOV     AH, BYTE[RSI]
        MOV     BYTE[RDI], AH
        INC     RCX
        INC     RDI
        INC     RSI
        JMP     loop

end:
        RET
