BITS 64
SECTION .text
GLOBAL strrchr
extern strlen

strrchr:
        CALL    strlen WRT ..plt
        MOV     RCX, RAX

revers_mov:
        CMP     RCX, 0
        JE      fail
        CMP     SIL, BYTE[RDI + RCX]
        JE      found
        DEC     RCX
        JMP     revers_mov

found:
        LEA     RAX, [RDI + RCX]
        JMP     end

fail:
        MOV     RAX, 0

end:
        RET