#pragma once

#include <windows.h>
#include "types.h"
#include <memory>

class DolphinProcess {
private:
    static std::unique_ptr<DolphinProcess> sInstance;
public:
    static std::unique_ptr<DolphinProcess>& Instance() {
        return sInstance;
    }

    DolphinProcess();

    static constexpr u32 GetDefaultMEM1Size() {
        return 24 * 1024 * 1024;
    }

    static constexpr u32 GetDefaultMEM2Size() {
        return 64 * 1024 * 1024;
    }

    static u32 GetMEM1Size() {
        return NextPowerOf2(GetDefaultMEM1Size());
    }

    static u32 GetMEM2Size() {
        return NextPowerOf2(GetDefaultMEM2Size());
    }

    // returns if the process id for Dolphin was found
    bool FindPID();
    bool Hook();
    bool ReadFromRAM(const u32 offset, char* buffer, size_t size, const bool byteswap);
    bool WriteToRAM(const u32 offset, const char* buffer, size_t size, const bool byteswap);

private:
    int mPID;
    HANDLE mDolphinHandle;
    bool mMEM2Present;
    u64 mEmulatedMEM1Start;
    u64 mEmulatedMEM2Start;
};
