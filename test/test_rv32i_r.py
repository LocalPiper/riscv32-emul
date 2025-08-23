from utils import to_signed32


def test_add(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        li a0, 42
        li a1, 58
        add a2, a0, a1
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert regs["a0"] == 42
    assert regs["a1"] == 58
    assert regs["a2"] == 100


def test_sub(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        li a0, 200
        li a1, 58
        sub a2, a0, a1
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert regs["a0"] == 200
    assert regs["a1"] == 58
    assert regs["a2"] == 142


def test_xor(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        li a0, 127
        li a1, 127
        xor a2, a0, a1
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert regs["a0"] == 127
    assert regs["a1"] == 127
    assert regs["a2"] == 0


def test_or(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        li a0, 2
        li a1, 1
        or a2, a0, a1
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert regs["a0"] == 2
    assert regs["a1"] == 1
    assert regs["a2"] == 3


def test_and(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        li a0, 14
        li a1, 5
        and a2, a0, a1
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert regs["a0"] == 14
    assert regs["a1"] == 5
    assert regs["a2"] == 4


def test_sll(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        li a0, 1
        li a1, 6
        sll a2, a0, a1
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert regs["a0"] == 1
    assert regs["a1"] == 6
    assert regs["a2"] == 64


def test_srl(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        li a0, 19
        li a1, 2
        srl a2, a0, a1
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert regs["a0"] == 19
    assert regs["a1"] == 2
    assert regs["a2"] == 4


def test_sra(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        li a0, -11
        li a1, 2
        sra a2, a0, a1
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert to_signed32(regs["a0"]) == -11
    assert to_signed32(regs["a1"]) == 2
    assert to_signed32(regs["a2"]) == -3


def test_slt(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        li a0, -123
        li a1, 412
        slt a2, a0, a1
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert to_signed32(regs["a0"]) == -123
    assert to_signed32(regs["a1"]) == 412
    assert to_signed32(regs["a2"]) == 1


def test_sltu(compile_asm, run_emulator_ok, parse_regs):
    asm = """
        .section .text
        .globl _start
    _start:
        li a0, -123
        li a1, 412
        sltu a2, a0, a1
        j .
    """
    binary = compile_asm(asm)
    output = run_emulator_ok(binary)
    regs = parse_regs(output)

    assert regs["a0"] == 4294967173
    assert regs["a1"] == 412
    assert regs["a2"] == 0
