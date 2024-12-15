    .equ MMU_PAGE0, 0xf0
    .equ MMU_PAGE1, 0xf1
    .equ MMU_PAGE2, 0xf2
    .equ MMU_PAGE3, 0xf3
    .global _crt_entry
    
    .global start
start:
    ld a, 32 ; Physical address 0x80000, start of internal SRAM
    out (MMU_PAGE1), a ; Map to 0x4000

    ld hl, 0x8000
    ld sp, hl

    jp _crt_entry
    ret
