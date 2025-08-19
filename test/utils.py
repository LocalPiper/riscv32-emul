def to_signed32(val: int) -> int:
    val &= 0xFFFFFFFF
    if val & 0x80000000:
        return val - 0x100000000
    return val
