#include "SlotMachineEngine.hpp"
#include "GLContext.hpp"

SlotMachineEngine::SlotMachineEngine() {

}

void SlotMachineEngine::Init() {
    GLContext::GetInstance()->Init();


}

void SlotMachineEngine::Run() {
    while(!(GLContext::GetInstance()->CheckCloseWindow()))
    {
        GLContext::GetInstance()->PollEvents();

        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);



        GLContext::GetInstance()->SwapBuffers();


    }
}
