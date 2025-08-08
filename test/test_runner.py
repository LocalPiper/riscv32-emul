import subprocess
import tempfile
import os
import sys
import re

def compile_asm(asm_code: str) -> bytes:
    with tempfile.TemporaryDirectory() as tmpdir:
        asm_path = os.path.join(tmpdir, 'test.S')
        elf_path = os.path.join(tmpdir, 'test.elf')
        bin_path = os.path.join(tmpdir, 'test.bin')

        with open(asm_path, 'w') as f:
            f.write(asm_code)

        subprocess.run([
            "riscv64-unknown-elf-gcc",
            "-nostdlib", "-march=rv32i", "-mabi=ilp32",
            asm_path, "-o", elf_path
        ], check=True)

        subprocess.run([
            "riscv64-unknown-elf-objcopy",
            "-O", "binary", elf_path, bin_path
        ], check=True)

        with open(bin_path, 'rb') as f:
            return f.read()

def run_emulator(binary: bytes) -> str:
    proc = subprocess.Popen(
        ['./build/riscvemu', '--test'],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE
    )
    stdout, stderr = proc.communicate(input=binary)
    if proc.returncode != 0:
        raise RuntimeError(stderr.decode())
    return stdout.decode()

def parse_regs(output: str) -> dict:
    pattern = re.compile(r"REG (\w+)\s+\(x[0-9a-f]{2}\): 0x([0-9a-f]{8})")
    return {m.group(1): int(m.group(2), 16) for m in pattern.finditer(output)}

def test_add():
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
    output = run_emulator(binary)
    regs = parse_regs(output)

    assert regs["a0"] == 42
    assert regs["a1"] == 58
    assert regs["a2"] == 100
    print("[OK] test_add")

if __name__ == "__main__":
    test_add()
