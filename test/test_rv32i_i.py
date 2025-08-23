from utils import to_signed32


def test_addi(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        addi a1, a0, 42
        addi a2, a1, -44
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert regs["a0"] == 0
    assert regs["a1"] == 42
    assert to_signed32(regs["a2"]) == -2


def test_xori(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        addi a1, a0, 42
        xori a2, a1, 42
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert regs["a0"] == 0
    assert regs["a1"] == 42
    assert regs["a2"] == 0


def test_ori(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        addi a1, a0, 8
        ori a2, a1, 7
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert regs["a0"] == 0
    assert regs["a1"] == 8
    assert regs["a2"] == 15


def test_andi(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        addi a1, a0, 8
        andi a2, a1, 7
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert regs["a0"] == 0
    assert regs["a1"] == 8
    assert regs["a2"] == 0


def test_slli(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        addi a1, a0, 8
        slli a2, a1, 2
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert regs["a0"] == 0
    assert regs["a1"] == 8
    assert regs["a2"] == 32


def test_srli(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        addi a1, a0, 8
        srli a2, a1, 2
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert regs["a0"] == 0
    assert regs["a1"] == 8
    assert regs["a2"] == 2


def test_srai(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        addi a1, a0, -8
        srai a2, a1, 2
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert regs["a0"] == 0
    assert to_signed32(regs["a1"]) == -8
    assert to_signed32(regs["a2"]) == -2


def test_slti(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        addi a1, a0, -8
        slti a2, a1, -16
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert regs["a0"] == 0
    assert to_signed32(regs["a1"]) == -8
    assert regs["a2"] == 0


def test_sltiu(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        addi a1, a0, -8
        sltiu a2, a1, -16
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert regs["a0"] == 0
    assert to_signed32(regs["a1"]) == -8
    assert regs["a2"] == 0
