#pragma once
#include "DolphinProcess/DolphinProcess.h"
#include <vector>

class DolphinAccessor {
private:
    static std::unique_ptr<DolphinAccessor> sInstance;
public:
    static std::unique_ptr<DolphinAccessor>& Instance() {
        return sInstance;
    }

    std::vector<char> ReadBytes(const u32 address, size_t num);
    u8  Read8(const u32 address);
    u16 Read16(const u32 address, bool byteswap = true);
    u32 Read32(const u32 address, bool byteswap = true);
    u64 Read64(const u32 address, bool byteswap = true);
    f32 ReadF32(const u32 address, bool byteswap = true);
    f64 ReadF64(const u32 address, bool byteswap = true);

    void WriteBytes(const u32 address, const char* value, size_t num);
    void Write8(const u32 address, u8 value);
    void Write16(const u32 address, u16 value, bool byteswap = true);
    void Write32(const u32 address, u32 value, bool byteswap = true);
    void Write64(const u32 address, u64 value, bool byteswap = true);
    void WriteF32(const u32 address, f32 value, bool byteswap = true);
    void WriteF64(const u32 address, f64 value, bool byteswap = true);

};
