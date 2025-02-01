#include <iostream>
#include "DolphinProcess/DolphinProcess.h"
#include "DolphinReader/DolphinReader.h"

int main() {
    // ensure the correct version of the game is running

    if (!DolphinProcess::Instance()->FindPID()) {
        std::cerr << "dolphin is not running" << std::endl;
        return 1;
    } else if (!DolphinProcess::Instance()->Hook()) {
        std::cerr << "there is no game running" << std::endl;
        return 1;
    } else {
        std::vector<char> gameID = DolphinReader::Instance()->ReadBytes(0, 6);

        if (std::memcmp(gameID.data(), "RK5E01", 6) != 0) {
            std::cerr << "wrong game id. must be RK5E01" << std::endl;
            return 1;
        }
    }

    // playground

    const u32 GmkMngPtrAddr = 0x808e4dc0;
    u32 GmkMngAddr = DolphinReader::Instance()->Read32(GmkMngPtrAddr);
    std::cout << std::hex << GmkMngAddr << std::endl;

    return 0;
}
