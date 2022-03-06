BITS 64
SECTION .text
GLOBAL strcasecmp

strcasecmp:
        XOR     RAX, RAX
        XOR     RCX, RCX
        XOR     RDX, RDX
        XOR     R10, R10
        XOR     R11, R11

loop:
        MOV     R11B, BYTE[RDI + RCX]
        MOV     R10B, BYTE[RSI + RDX]
        JMP     is_letter

continue_loop:
        CMP     R11B, R10B
        JNE     bf_end
        CMP     BYTE[RDI + RCX], 0
        JE      stop_inc_rcx
        INC     RCX

cmp_rsi:
        CMP     BYTE[RSI + RDX], 0
        JE      stop_inc_rdx
        INC     RDX
        JMP     loop

stop_inc_rcx:
        CMP     BYTE[RSI + RDX], 0
        JE      bf_end
        JMP     cmp_rsi

stop_inc_rdx:
        CMP     BYTE[RDI + RCX], 0
        JE      bf_end
        JMP     loop


found_maj_al:
        ADD     R11B, 32
        JMP     is_letter_sec

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

is_letter_sec:
        CMP     R10B, 90
        JLE     found_maj_R10B
        JMP     continue_loop

end_str:
        

bf_end:
        SUB     R11B, R10B
        MOVSX   RAX, R11B
        JMP     end

end:
        RET
