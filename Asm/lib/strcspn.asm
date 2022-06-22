BITS 64
SECTION .text
GLOBAL strcspn

strcspn:
        XOR     RAX, RAX
        XOR     R8, R8
        XOR     RDX, RDX
        XOR     RCX, RCX

loop:
        CMP     BYTE[RDI + RCX], 0
        JE      fail
        JMP     sec_loop

sec_loop:
        MOV     RAX, RCX
        CMP     BYTE[RSI + RDX], 0
        JE      inc_rdx
        MOV     R8B, BYTE[RSI + RDX]
        CMP     R8B, BYTE[RDI + RCX]
        JE      end
        INC     RDX
        JMP     sec_loop

inc_rdx:
        INC     RCX
        XOR     RDX, RDX
        JMP     loop

fail:
        MOV     RAX, 0

end:
    RET
