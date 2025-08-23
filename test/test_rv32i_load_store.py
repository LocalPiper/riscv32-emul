from utils import to_signed32


def test_lb_sb(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        li a0, -42
        li a1, 20
        sb a0, 0(a1)
        lb a2, 0(a1)
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert to_signed32(regs["a0"]) == -42
    assert regs["a1"] == 20
    assert to_signed32(regs["a2"]) == -42


def test_lh_sh(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        li a0, -42
        li a1, 20
        sh a0, 0(a1)
        lh a2, 0(a1)
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert to_signed32(regs["a0"]) == -42
    assert regs["a1"] == 20
    assert to_signed32(regs["a2"]) == -42


def test_lw_sw(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        li a0, -42
        li a1, 20
        sw a0, 0(a1)
        lw a2, 0(a1)
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert to_signed32(regs["a0"]) == -42
    assert regs["a1"] == 20
    assert to_signed32(regs["a2"]) == -42


def test_lbu_sb(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        li a0, -42
        li a1, 20
        sb a0, 0(a1)
        lbu a2, 0(a1)
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert to_signed32(regs["a0"]) == -42
    assert regs["a1"] == 20
    assert regs["a2"] == 214


def test_lhu_sb(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        li a0, -42
        li a1, 20
        sh a0, 0(a1)
        lhu a2, 0(a1)
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert to_signed32(regs["a0"]) == -42
    assert regs["a1"] == 20
    assert regs["a2"] == 65494


def test_lh_misaligned(compile_asm, run_emulator_fail):
    asm = """
        .section .text
        .globl _start
    _start:
        li a0, -42
        li a1, 20
        sh a0, 0(a1)
        lh a2, 1(a1)
        j .
    """
    binary = compile_asm(asm)
    code, _, error = run_emulator_fail(binary)

    assert code == 1
    assert "Misaligned load (lh)" in error


def test_lw_misaligned(compile_asm, run_emulator_fail):
    asm = """
        .section .text
        .globl _start
    _start:
        li a0, -42
        li a1, 20
        sw a0, 0(a1)
        lw a2, 3(a1)
        j .
    """
    binary = compile_asm(asm)
    code, _, error = run_emulator_fail(binary)

    assert code == 1
    assert "Misaligned load (lw)" in error


def test_sh_misaligned(compile_asm, run_emulator_fail):
    asm = """
        .section .text
        .globl _start
    _start:
        li a0, -42
        li a1, 20
        sh a0, 1(a1)
        lh a2, 2(a1)
        j .
    """
    binary = compile_asm(asm)
    code, _, error = run_emulator_fail(binary)

    assert code == 1
    assert "Misaligned store (sh)" in error


def test_sw_misaligned(compile_asm, run_emulator_fail):
    asm = """
        .section .text
        .globl _start
    _start:
        li a0, -42
        li a1, 20
        sw a0, 3(a1)
        lw a2, 4(a1)
        j .
    """
    binary = compile_asm(asm)
    code, _, error = run_emulator_fail(binary)

    assert code == 1
    assert "Misaligned store (sw)" in error
