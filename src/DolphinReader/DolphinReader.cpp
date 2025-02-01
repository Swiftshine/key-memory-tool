#include "DolphinReader/DolphinReader.h"

inline u32 AddressToOffset(u32 addr) {
    if (addr >= MEM1_START && addr < DolphinProcess::GetMEM1End()) {
        addr -= MEM1_START;
    } else if (addr >= MEM2_START && addr < DolphinProcess::GetMEM2End()) {
        addr -= MEM2_START;
        addr += (MEM2_START - MEM1_START);
    }

    return addr;
}
std::unique_ptr<DolphinReader> DolphinReader::sInstance = std::make_unique<DolphinReader>();

std::vector<char> DolphinReader::ReadBytes(const u32 address, size_t num) {
    std::vector<char> result(num);
    DolphinProcess::Instance()->ReadFromRAM(AddressToOffset(address), result.data(), num, false);
    return result;
}

u8 DolphinReader::Read8(const u32 address) {
    u8 value = 0;
    DolphinProcess::Instance()->ReadFromRAM(AddressToOffset(address), reinterpret_cast<char*>(&value), sizeof(value), false);
    return value;
}

u16 DolphinReader::Read16(const u32 address, bool byteswap) {
    u16 value = 0;
    DolphinProcess::Instance()->ReadFromRAM(AddressToOffset(address), reinterpret_cast<char*>(&value), sizeof(value), byteswap);
    return value;
}

u32 DolphinReader::Read32(const u32 address, bool byteswap) {
    u32 value = 0;
    DolphinProcess::Instance()->ReadFromRAM(AddressToOffset(address), reinterpret_cast<char*>(&value), sizeof(value), byteswap);
    return value;
}

u64 DolphinReader::Read64(const u32 address, bool byteswap) {
    u64 value = 0;
    DolphinProcess::Instance()->ReadFromRAM(AddressToOffset(address), reinterpret_cast<char*>(&value), sizeof(value), byteswap);
    return value;
}

f32 DolphinReader::ReadF32(const u32 address, bool byteswap) {
    f32 value = 0;
    DolphinProcess::Instance()->ReadFromRAM(AddressToOffset(address), reinterpret_cast<char*>(&value), sizeof(value), byteswap);
    return value;
}

f64 DolphinReader::ReadF64(const u32 address, bool byteswap) {
    f64 value = 0;
    DolphinProcess::Instance()->ReadFromRAM(AddressToOffset(address), reinterpret_cast<char*>(&value), sizeof(value), byteswap);
    return value;
}
