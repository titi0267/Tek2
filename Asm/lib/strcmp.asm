BITS 64
SECTION .text
GLOBAL strcmp

strcmp:
        XOR     RAX, RAX
        XOR     RCX, RCX

loop:
        MOV     AL, BYTE[RDI + RCX]
        MOV     AH, BYTE[RSI + RCX]
        CMP     BYTE[RDI + RCX], 0
        JE      compare_ptr
        CMP     BYTE[RSI + RCX], 0
        JE      compare_ptr
        CMP     AL, AH
        JNE     compare_ptr
        INC     RCX
        JMP     loop

compare_ptr:
        SUB     AL, AH
        MOV     AH, 0
        MOVSX   RAX, AL

end:
        RET
