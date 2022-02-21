BITS 64
SECTION .text
GLOBAL strchr

strchr:
        XOR     RAX, RAX

loop:
        CMP     BYTE[RDI, RAX], 0
        JE      fail
        MOVSX   EDX, BYTE[RDI + RAX]
        CMP     EDX, ESI
        JE      first_occ
        INC     RAX
        INC     RCX
        JMP     loop

fail:
        MOV     RAX, 0
        JMP     end

first_occ:
        CMP     BYTE[RDI + RCX], 0
        JE      end
        MOVSX   EDX, BYTE[RDI + RCX]
        INC     RCX
        JMP     first_occ

end:
        RET