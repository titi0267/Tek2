BITS 64
SECTION .text
GLOBAL memset

memset:
        XOR     RAX, RAX
        XOR     RCX, RCX
        MOV     RAX, RDI

loop:
        CMP     RDX, RCX
        JE      end
        MOV     BYTE[RAX + RCX], SIL
        INC     RCX
        JMP     loop

end:
        RET
