BITS 64
SECTION .text
GLOBAL strstr

strstr:
        XOR     RAX, RAX
        XOR     R11, R11
        XOR     R10, R10
        XOR     R8, R8
        XOR     RDX, RDX
        XOR     RCX, RCX

loop:
        CMP     BYTE[RDI + RCX], 0
        JE      end
        MOV     R8B, BYTE[RDI + RCX]
        CMP     R8B, BYTE[RSI]
        JE      sec_loop
        JMP     end_loop

sec_loop:
        MOV     RAX, RDI
        ADD     RAX, RCX
        MOV     R11, RCX
        ADD     R11, RDX
        MOV     R10B, BYTE[RSI + RDX]
        CMP     BYTE[RSI + RDX], 0
        JE      end
        CMP     R10B, BYTE[RDI + R11]
        JNE     res_rdx
        INC     RDX
        JMP     sec_loop

res_rdx:
        XOR     RDX, RDX
        JMP     end_loop

end_loop:
        INC     RCX
        JMP     loop

end:
        RET