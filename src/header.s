    ; ROM header
    .org 0x0000
    .global start

rst_00:
    di
    jp start
