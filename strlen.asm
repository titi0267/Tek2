BITS 64
SECTION .text
GLOBAL strlen

strlen:
        XOR     RAX, RAX

loop:
        CMP     BYTE [RDI + RAX], 0
        JE     end
        INC     RAX
        JMP     loop

end:
        RET
