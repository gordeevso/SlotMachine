#include "SlotMachineEngine.hpp"
#include "GLFWWrapper.hpp"

int main() {

    GLFWWrapper::GetInstance()->Init();
    SlotMachineEngine::GetInstance()->Run();

    return 0;
}