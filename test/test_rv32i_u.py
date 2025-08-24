def test_lui(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        lui a0, 0x12345
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert regs["a0"] == 0x12345000


def test_auipc(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        auipc a1, 0x1
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert regs["a1"] == 0x1000


def test_lui_addi(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        lui a2, 0x12345
        addi a2, a2, 0x678
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert regs["a2"] == 0x12345678
