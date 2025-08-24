def test_jal(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        li a0, 10
        li a1, 5
    loop:
        beq a1, zero, endLoop
        add a2, a2, a0
        addi a1, a1, -1
        j loop
    endLoop:
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert regs["a0"] == 10
    assert regs["a1"] == 0
    assert regs["a2"] == 50
