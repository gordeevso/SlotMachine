#include "SlotMachineEngine.hpp"
#include "GLContext.hpp"


SlotMachineEngine::SlotMachineEngine() : mPtrTimeManager(new TimeManager),
                                         mPtrScene(nullptr)
{}

void SlotMachineEngine::Init() {
    GLContext::GetInstance()->Init();
    mPtrScene.reset(new Scene);

}

void SlotMachineEngine::Run() {
    mPtrTimeManager->UpdateMainLoop();
    while(!(GLContext::GetInstance()->CheckCloseWindow()))
    {
        mPtrTimeManager->UpdateMainLoop();
        GLContext::GetInstance()->PollEvents();

        mPtrScene->Update(mPtrTimeManager->FrameTime());

        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        mPtrScene->Draw();

        GLContext::GetInstance()->SwapBuffers();
    }
}
