#include <iostream>
#include "DolphinProcess.h"

int main() {
    if (!DolphinProcess::Instance()->FindPID()) {
        std::cerr << "dolphin is not running" << std::endl;
        return 1;
    }

    if (!DolphinProcess::Instance()->Hook()) {
        std::cerr << "there is no game running" << std::endl;
        return 1;
    }


    char gameID[7] = { 0 };

    DolphinProcess::Instance()->ReadFromRAM(0, gameID, 6, false);

    if (std::string(gameID) != "RK5E01") {
        std::cerr << "wrong game id. must be RK5E01" << std::endl;
        return 1;
    }


    return 0;
}
