#include "DolphinAccessor/DolphinAccessor.h"

inline u32 AddressToOffset(u32 addr) {
    if (addr >= MEM1_START && addr < DolphinProcess::GetMEM1End()) {
        addr -= MEM1_START;
    } else if (addr >= MEM2_START && addr < DolphinProcess::GetMEM2End()) {
        addr -= MEM2_START;
        addr += (MEM2_START - MEM1_START);
    }

    return addr;
}
std::unique_ptr<DolphinAccessor> DolphinAccessor::sInstance = std::make_unique<DolphinAccessor>();

std::vector<char> DolphinAccessor::ReadBytes(const u32 address, size_t num) {
    std::vector<char> result(num);
    DolphinProcess::Instance()->ReadFromRAM(AddressToOffset(address), result.data(), num, false);
    return result;
}

u8 DolphinAccessor::Read8(const u32 address) {
    u8 value = 0;
    DolphinProcess::Instance()->ReadFromRAM(AddressToOffset(address), reinterpret_cast<char*>(&value), sizeof(value), false);
    return value;
}

u16 DolphinAccessor::Read16(const u32 address, bool byteswap) {
    u16 value = 0;
    DolphinProcess::Instance()->ReadFromRAM(AddressToOffset(address), reinterpret_cast<char*>(&value), sizeof(value), byteswap);
    return value;
}

u32 DolphinAccessor::Read32(const u32 address, bool byteswap) {
    u32 value = 0;
    DolphinProcess::Instance()->ReadFromRAM(AddressToOffset(address), reinterpret_cast<char*>(&value), sizeof(value), byteswap);
    return value;
}

u64 DolphinAccessor::Read64(const u32 address, bool byteswap) {
    u64 value = 0;
    DolphinProcess::Instance()->ReadFromRAM(AddressToOffset(address), reinterpret_cast<char*>(&value), sizeof(value), byteswap);
    return value;
}

f32 DolphinAccessor::ReadF32(const u32 address, bool byteswap) {
    f32 value = 0;
    DolphinProcess::Instance()->ReadFromRAM(AddressToOffset(address), reinterpret_cast<char*>(&value), sizeof(value), byteswap);
    return value;
}

f64 DolphinAccessor::ReadF64(const u32 address, bool byteswap) {
    f64 value = 0;
    DolphinProcess::Instance()->ReadFromRAM(AddressToOffset(address), reinterpret_cast<char*>(&value), sizeof(value), byteswap);
    return value;
}

void DolphinAccessor::WriteBytes(const u32 address, const char* value, size_t num) {
    DolphinProcess::Instance()->WriteToRAM(AddressToOffset(address), value, num, false);
}

void DolphinAccessor::Write8(const u32 address, u8 value) {
    DolphinProcess::Instance()->WriteToRAM(AddressToOffset(address), reinterpret_cast<char*>(&value), sizeof(value), false);
}

void DolphinAccessor::Write16(const u32 address, u16 value, bool byteswap) {
    DolphinProcess::Instance()->WriteToRAM(AddressToOffset(address), reinterpret_cast<char*>(&value), sizeof(value), byteswap);
}

void DolphinAccessor::Write32(const u32 address, u32 value, bool byteswap) {
    DolphinProcess::Instance()->WriteToRAM(AddressToOffset(address), reinterpret_cast<char*>(&value), sizeof(value), byteswap);
}

void DolphinAccessor::Write64(const u32 address, u64 value, bool byteswap) {
    DolphinProcess::Instance()->WriteToRAM(AddressToOffset(address), reinterpret_cast<char*>(&value), sizeof(value), byteswap);
}

void DolphinAccessor::WriteF32(const u32 address, f32 value, bool byteswap) {
    DolphinProcess::Instance()->WriteToRAM(AddressToOffset(address), reinterpret_cast<char*>(&value), sizeof(value), byteswap);
}

void DolphinAccessor::WriteF64(const u32 address, f64 value, bool byteswap) {
    DolphinProcess::Instance()->WriteToRAM(AddressToOffset(address), reinterpret_cast<char*>(&value), sizeof(value), byteswap);
}

