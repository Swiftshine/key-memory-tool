#include "DolphinProcess.h"

#include <cstring>
#include <locale>
#include <codecvt>
#include <cstdlib>
#include <string>
#include <tlhelp32.h>
#include <psapi.h>

const u32 MEM1_START = 0x80000000;
const u32 MEM2_START = 0x90000000;

#ifdef UNICODE
    std::wstring utf8_to_wstring(const std::string& str) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
        return conv.from_bytes(str);
    }
#endif

std::unique_ptr<DolphinProcess> DolphinProcess::sInstance = std::make_unique<DolphinProcess>();

DolphinProcess::DolphinProcess() {
    mPID = -1;
    mDolphinHandle = NULL;
    mMEM2Present = false;
    mEmulatedMEM1Start = 0;
    mEmulatedMEM2Start = 0;
}

bool DolphinProcess::FindPID() {
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(entry);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    mPID = -1;
    
    if (Process32First(snapshot, &entry)) {
        do {
            bool match = false;

            #ifdef UNICODE
                const std::wstring processName = entry.szExeFile;
                match = processName == L"Dolphin.exe";
            #else
                const std::string processName = entry.szExeFile;
                match = processName == "Dolphin.exe";
            #endif

            if (match) {
                mPID = entry.th32ProcessID;
                break;
            }

        } while (Process32Next(snapshot, &entry));
    }

    CloseHandle(snapshot);

    if (mPID == -1) {
        // dolphin isn't running
        return false;
    }

    mDolphinHandle = OpenProcess(
        PROCESS_QUERY_INFORMATION |
            PROCESS_VM_OPERATION |
            PROCESS_VM_READ |
            PROCESS_VM_WRITE,
        FALSE,
        mPID
    );

    return true;
}

bool DolphinProcess::Hook() {
    MEMORY_BASIC_INFORMATION info;
    bool mem1Found = false;

    for (
        u8* p = nullptr;
        VirtualQueryEx(mDolphinHandle, p, &info, sizeof(info)) == sizeof(info);
        p += info.RegionSize
    ) {
        // check region size so we know it's mem2
        if (!mMEM2Present && info.RegionSize == GetMEM2Size()) {
            u64 regionBaseAddress = 0;
            std::memcpy(&regionBaseAddress, &(info.BaseAddress), sizeof(info.BaseAddress));
            
            if (mem1Found && regionBaseAddress > mEmulatedMEM1Start + + 0x10000000) {
                break;
            }

            PSAPI_WORKING_SET_EX_INFORMATION wsInfo;
            wsInfo.VirtualAddress = info.BaseAddress;

            if (QueryWorkingSetEx(mDolphinHandle, &wsInfo, sizeof(wsInfo))) {
                if (wsInfo.VirtualAttributes.Valid) {
                    std::memcpy(&mEmulatedMEM2Start, &regionBaseAddress, sizeof(regionBaseAddress));
                    mMEM2Present = true;
                }
            }
        } else if (info.RegionSize == GetMEM1Size() && info.Type == MEM_MAPPED) {
            PSAPI_WORKING_SET_EX_INFORMATION wsInfo;
            wsInfo.VirtualAddress = info.BaseAddress;
            if (QueryWorkingSetEx(mDolphinHandle, &wsInfo, sizeof(PSAPI_WORKING_SET_EX_INFORMATION))) {
                if (wsInfo.VirtualAttributes.Valid) {
                    if (!mem1Found) {
                        std::memcpy(&mEmulatedMEM1Start, &(info.BaseAddress), sizeof(info.BaseAddress));
                        mem1Found = true;
                    }

                    // else aram stuff
                }
            }
        }
    }

    return mEmulatedMEM1Start != 0;
}

bool DolphinProcess::ReadFromRAM(const u32 offset, char* buffer, size_t size, const bool byteswap) {
    u64 ramAddress = 0;

    if (offset >= MEM2_START - MEM1_START) {
        ramAddress = mEmulatedMEM2Start + offset - (MEM2_START - MEM1_START);
    } else {
        ramAddress = mEmulatedMEM1Start + offset;
    }

    SIZE_T numRead = 0;
    bool readProcessResult = ReadProcessMemory(mDolphinHandle, reinterpret_cast<void*>(ramAddress), buffer, size, &numRead);

    if (readProcessResult && numRead == size) {
        if (byteswap) {
            switch (size) {
                case 2: {
                    u16 val = 0;
                    std::memcpy(&val, buffer, sizeof(val));
                    val = Swap16(val);
                    std::memcpy(buffer, &val, sizeof(val));
                    break;
                }

                case 4: {
                    u32 val = 0;
                    std::memcpy(&val, buffer, sizeof(val));
                    val = Swap32(val);
                    std::memcpy(buffer, &val, sizeof(val));
                    break;
                }

                case 8: {
                    u64 val = 0;
                    std::memcpy(&val, buffer, sizeof(val));
                    val = Swap64(val);
                    std::memcpy(buffer, &val, sizeof(val));
                    break;
                }
            }
        }

        return true;
    } 

    return false;
}
