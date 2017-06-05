#include "SlotMachineEngine.hpp"

int main() {

    SlotMachineEngine::GetInstance()->Init();
    SlotMachineEngine::GetInstance()->Run();

    return 0;
}