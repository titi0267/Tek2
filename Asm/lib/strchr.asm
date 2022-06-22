BITS 64
SECTION .text
GLOBAL strchr

strchr:
        XOR     RAX, RAX
        XOR     RCX, RCX

loop:
        CMP     BYTE[RDI + RCX], 0
        JE      str_end
        CMP     BYTE[RDI + RCX], SIL
        JE      found
        INC     RCX
        JMP     loop

str_end:
        XOR     RAX, RAX
        JMP     end

found:
        LEA    RAX, [RDI + RCX]

end:
        RET
