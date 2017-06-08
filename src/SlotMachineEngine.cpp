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

    mPtrScene->Draw();
    GLFWWrapper::GetInstance()->SwapBuffers();

    while(!(GLFWWrapper::GetInstance()->CheckCloseWindow()))
    {
        mPtrTimeManager->UpdateMainLoop();
        GLFWWrapper::GetInstance()->PollEvents();

        mPtrScene->Update(mPtrTimeManager->FrameTime());

        if(!mPtrScene->CheckReadinessForStart()) {
            glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            mPtrScene->Draw();
            GLFWWrapper::GetInstance()->SwapBuffers();
        }
    }
}
