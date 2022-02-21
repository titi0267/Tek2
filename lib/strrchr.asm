BITS 64
SECTION .text
GLOBAL strrchr
extern strlen

.strrchr:
        CALL    strlen WRT ..plt
        MOV     RCX, RAX

.rev_str:
        CMP     RCX, 0
        JE      .fail
        MOVSX   EDX, BYTE[RDI + RCX]
        CMP     EDX, ESI
        JE      .founded
        DEC     RCX
        JMP     .rev_str

.founded:
        XOR     EDX, EDX

.final:
        MOVSX   EDX, BYTE[RDI + RCX]
        CMP     BYTE[RDI + RAX], 0
        JE      .end
        JMP     .final

.fail:
        MOV     RAX, 0

.end:
        RET