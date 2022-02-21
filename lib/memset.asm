BITS 64
SECTION .text
GLOBAL memset

;void *memset(void *s, int c, size_t n)
;{
;    int i = 0;
;
;    while(i <= n) {
;        s[i] = c;
;        i++;
;    }
;    return (s);
;}

memset:
        XOR     RAX, RAX
        MOV     RAX, RDI

loop:
        CMP     RDX, RCX
        JE      end
        MOV     BYTE[RAX + RCX], SIL
        INC     RCX
        JMP     loop

end:
        RET
