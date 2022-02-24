BITS 64
SECTION .text
GLOBAL strcasecmp

strcasecmp:
        XOR     RAX, RAX
        XOR     RCX, RCX
        XOR     R10, R10
        XOR     R11, R11

loop:
        MOV     R11B, BYTE[RDI + RCX]
        MOV     R10B, BYTE[RSI + RCX]
        JMP     is_letter

continue_loop:
        CMP     R11B, R10B
        JNE     bf_end
        CMP     BYTE[RDI + RCX], 0
        JE      bf_end
        CMP     BYTE[RSI + RCX], 0
        JE      bf_end
        INC     RCX
        JMP     loop

found_maj_al:
        ADD     R11B, 32
        JMP     continue_loop

found_maj_R10B:
        ADD     R10B, 32
        JMP     continue_loop

is_letter:
        CMP     R11B, 65
        JL      continue_loop
        CMP     R10B, 65
        JL      continue_loop
        CMP     R11B, 90
        JLE     found_maj_al
        CMP     R10B, 90
        JLE     found_maj_R10B

bf_end:
        SUB     R11B, R10B
        MOVSX   RAX, R11B
        JMP     end

end:
        RET
