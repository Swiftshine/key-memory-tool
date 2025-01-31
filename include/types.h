#pragma once

#include <cstdint>
#include <cstring>

using u8    = uint8_t;
using u16   = uint16_t;
using u32   = uint32_t;
using u64   = uint64_t;

using s8    = int8_t;
using s16   = int16_t;
using s32   = int32_t;
using s64   = int64_t;

using f32   = float;
using f64   = double;


constexpr u32 NextPowerOf2(u32 value) {
    value--;
    value |= value >> 1;
    value |= value >> 2;
    value |= value >> 4;
    value |= value >> 8;
    value |= value >> 16;
    value++;
    return value;
}


static u16 Swap16(u16 value) {
    return (value << 8) | (value >> 8);
}

static u32 Swap32(u32 value) {
    return ((value >> 24) & 0x000000FF) |
        ((value >> 8) & 0x0000FF00) |
        ((value << 8) & 0x00FF0000) |
        ((value << 24) & 0xFF000000);
}

static u64 Swap64(u64 value) {
    return ((value << 56) & 0xFF00000000000000ULL) |
        ((value << 40) & 0x00FF000000000000ULL) |
        ((value << 24) & 0x0000FF0000000000ULL) |
        ((value << 8) & 0x000000FF00000000ULL) |
        ((value >> 8) & 0x00000000FF000000ULL) |
        ((value >> 24) & 0x0000000000FF0000ULL) |
        ((value >> 40) & 0x000000000000FF00ULL) |
        ((value >> 56) & 0x00000000000000FFULL);
}

static f32 SwapF32(float value) {
    u32 intval;
    std::memcpy(&intval, &value, sizeof(float));
    intval = Swap32(intval);
    float result;
    std::memcpy(&result, &intval, sizeof(float));
    return result;
}

static f64 SwapF64(double value) {
    u64 intval;
    std::memcpy(&intval, &value, sizeof(double));
    intval = Swap64(intval);
    double result;
    std::memcpy(&result, &intval, sizeof(double));
    return result;
}
