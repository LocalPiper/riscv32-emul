    .text
    .globl _start

_start:
    li a0, 42         # Load 10 into a0
    li a1, 32         # Load 32 into a1
    add a2, a0, a1    # a2 = a0 + a1
    j .              # infinite loop (halt)

