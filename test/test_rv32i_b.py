from utils import to_signed32


def test_beq(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        li a0, 20
        li a1, 20
        beq a0, a1, target
        addi a2, zero, 1
        j .
    target:
        addi a2, zero, 2
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert regs["a0"] == 20
    assert regs["a1"] == 20
    assert regs["a2"] == 2


def test_bne(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        li a0, 20
        li a1, 21
        bne a0, a1, target
        addi a2, zero, 1
        j .
    target:
        addi a2, zero, 2
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert regs["a0"] == 20
    assert regs["a1"] == 21
    assert regs["a2"] == 2


def test_blt(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        li a0, 20
        li a1, 21
        blt a0, a1, target
        addi a2, zero, 1
        j .
    target:
        addi a2, zero, 2
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert regs["a0"] == 20
    assert regs["a1"] == 21
    assert regs["a2"] == 2


def test_bge(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        li a0, 20
        li a1, 21
        bge a0, a1, target
        addi a2, zero, 1
        j .
    target:
        addi a2, zero, 2
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert regs["a0"] == 20
    assert regs["a1"] == 21
    assert regs["a2"] == 1


def test_bltu(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        li a0, 20
        li a1, -21
        bltu a0, a1, target
        addi a2, zero, 1
        j .
    target:
        addi a2, zero, 2
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert regs["a0"] == 20
    assert to_signed32(regs["a1"]) == -21
    assert regs["a2"] == 2


def test_bgeu(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        li a0, 20
        li a1, -21
        bgeu a0, a1, target
        addi a2, zero, 1
        j .
    target:
        addi a2, zero, 2
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert regs["a0"] == 20
    assert to_signed32(regs["a1"]) == -21
    assert regs["a2"] == 1
