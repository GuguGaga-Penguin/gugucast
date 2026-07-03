#pragma once
#include <cstdint>

struct SH4_Registers {
    uint32_t R[16];   // 16 General Purpose 32-bit Registers (R0 - R15)
    uint32_t PC;      // Program Counter
    uint32_t PR;      // Procedure Register
    uint32_t SR;      // Status Register
};
