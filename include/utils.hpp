#pragma once

#include <cstdint>
#include <iomanip>
#include <string>

inline std::string to_hex(uint32_t value) {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(8) << std::right << std::hex << value;
    return oss.str();
}