import subprocess
import pathlib
import tempfile
import os
import re
import pytest


@pytest.fixture
def compile_asm():
    def _compile(asm_code: str) -> bytes:
        with tempfile.TemporaryDirectory() as tmpdir:
            asm_path = os.path.join(tmpdir, "test.S")
            elf_path = os.path.join(tmpdir, "test.elf")
            bin_path = os.path.join(tmpdir, "test.bin")

            with open(asm_path, "w") as f:
                f.write(asm_code)

            subprocess.run(
                [
                    "riscv64-unknown-elf-gcc",
                    "-nostdlib",
                    "-march=rv32i",
                    "-mabi=ilp32",
                    asm_path,
                    "-o",
                    elf_path,
                ],
                check=True,
            )

            subprocess.run(
                ["riscv64-unknown-elf-objcopy", "-O", "binary", elf_path, bin_path],
                check=True,
            )

            with open(bin_path, "rb") as f:
                return f.read()

    return _compile


@pytest.fixture
def run_emulator():
    def _run(binary: bytes) -> str:
        HERE = pathlib.Path(__file__).parent.resolve()
        EMU_PATH = (HERE.parent / "build" / "riscvemu").resolve()

        proc = subprocess.Popen(
            [str(EMU_PATH), "--test"],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
        )
        stdout, stderr = proc.communicate(input=binary)
        if proc.returncode != 0:
            raise RuntimeError(stderr.decode())
        return stdout.decode()

    return _run


@pytest.fixture
def parse_regs():
    def _parse(output: str) -> dict:
        pattern = re.compile(r"REG (\w+)\s+\(x[0-9a-f]{2}\): 0x([0-9a-f]{8})")
        return {m.group(1): int(m.group(2), 16) for m in pattern.finditer(output)}

    return _parse
