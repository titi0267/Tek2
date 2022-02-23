BITS 64
SECTION .text
GLOBAL strcmp

strcmp:
        XOR     RAX, RAX

loop:
        CMP     BYTE[RDI], 0
        JE      ret_neg
        CMP     BYTE[RSI], 0
        JE      ret_pos
        MOV     AL, BYTE[RDI]
        MOV     AH, BYTE[RSI]
        CMP     AH, AL
        JNE     compare_ptr
        INC     RSI
        INC     RDI
        JMP     loop

compare_ptr:
        CMP     AL, AH
        JL      ret_neg
        CMP     AL, AH
        JG      ret_pos

ret_neg:
        CMP     BYTE[RSI], 0
        JE      ret_zero
        MOV     RAX, -1
        JMP     end

ret_pos:
        CMP     BYTE[RDI], 0
        JE      ret_zero
        MOV     RAX, 1
        JMP     end

ret_zero:
        MOV     RAX, 0

end:
        RET
