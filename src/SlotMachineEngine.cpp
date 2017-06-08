#include "SlotMachineEngine.hpp"
#include "GLFWWrapper.hpp"


SlotMachineEngine::SlotMachineEngine() : mPtrTimeManager(new TimeManager),
                                         mPtrScene(nullptr)
{}

void SlotMachineEngine::Init() {
    GLFWWrapper::GetInstance()->Init();
    mPtrScene.reset(new Scene);

}

void SlotMachineEngine::Run() {
    mPtrTimeManager->UpdateMainLoop();
    float elapsed {};

    while(!(GLFWWrapper::GetInstance()->CheckCloseWindow()))
    {
        mPtrTimeManager->UpdateMainLoop();
        elapsed += mPtrTimeManager->FrameTime();

        GLFWWrapper::GetInstance()->PollEvents();

        glClearColor(0.5f, 0.2f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        mPtrScene->Update(mPtrTimeManager->FrameTime());
        mPtrScene->Draw();
        mPtrScene->DrawButton();

        if(elapsed > 0.05f) {
            mPtrScene->UpdateButtonColor();
            elapsed = 0.f;
        }

        GLFWWrapper::GetInstance()->SwapBuffers();

    }
}
