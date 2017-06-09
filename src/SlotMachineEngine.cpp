#include <windows.h>

#include "SlotMachineEngine.hpp"
#include "GLFWWrapper.hpp"


SlotMachineEngine::SlotMachineEngine() : mPtrTimeManager(new TimeManager),
                                         mPtrScene(nullptr),
                                         mPtrTextRenderer(nullptr),
                                         mPtrRenderToTexture(nullptr)
{}

void SlotMachineEngine::Init() {
    GLFWWrapper::GetInstance()->Init();
    mPtrScene.reset(new Scene);
    mPtrTextRenderer.reset(new TextRenderer);
    mPtrRenderToTexture.reset(new RenderToTexture);

    mPtrTextRenderer->Init("../res/fonts/BKANT.TTF", 48);
    mPtrRenderToTexture->Init();

}

void SlotMachineEngine::Run() {

    mPtrTimeManager->UpdateMainLoop();
    float lastFPS {};

    while(!(GLFWWrapper::GetInstance()->CheckCloseWindow()))
    {
        mPtrTimeManager->UpdateMainLoop();

        GLFWWrapper::GetInstance()->PollEvents();

        mPtrScene->Update(mPtrTimeManager->FrameTime());

        mPtrRenderToTexture->PreRender();

        mPtrScene->Draw();
        mPtrScene->DrawButton();

        if(mPtrTimeManager->GetElapsed() > 0.05f) {
            mPtrScene->UpdateButtonColor();
            DrawFPS(std::to_string(static_cast<int32_t>(mPtrTimeManager->FramesPerSecond())));
            lastFPS = mPtrTimeManager->FramesPerSecond();
            mPtrTimeManager->ResetElapsed();
        }
        else {
            DrawFPS(std::to_string(static_cast<int32_t>(lastFPS)));
        }

        mPtrRenderToTexture->PostRender();

        GLFWWrapper::GetInstance()->SwapBuffers();

    }
}

void SlotMachineEngine::DrawFPS(std::string fps) {
    mPtrTextRenderer->RenderText(fps,
                                 GLFWWrapper::GetInstance()->GetWidth() - 50.f,
                                 GLFWWrapper::GetInstance()->GetHeight() - 40.f,
                                 1.0f,
                                 glm::vec3(0.2f, 0.2f, 0.8f));
}
