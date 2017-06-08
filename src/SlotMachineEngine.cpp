#include <windows.h>

#include "SlotMachineEngine.hpp"
#include "GLFWWrapper.hpp"


SlotMachineEngine::SlotMachineEngine() : mPtrTimeManager(new TimeManager),
                                         mPtrScene(nullptr),
                                         mPtrTextRenderer(nullptr)
{}

void SlotMachineEngine::Init() {
    GLFWWrapper::GetInstance()->Init();
    mPtrScene.reset(new Scene);
    mPtrTextRenderer.reset(new TextRenderer);

    mPtrTextRenderer->Load("../res/fonts/HTOWERT.TTF", 24);

}

void SlotMachineEngine::Run() {

    float elapsed {};
    float lastTime = static_cast<float>(GLFWWrapper::GetInstance()->GetTimeNow());
    float targetFrameTime = 1.f / 60.f;
    float timer = lastTime;
    float deltaTime = {};
    float nowTime = {};
    float sleepTime {};

    while(!(GLFWWrapper::GetInstance()->CheckCloseWindow()))
    {
        timer += targetFrameTime;
        nowTime = static_cast<float>(GLFWWrapper::GetInstance()->GetTimeNow());
        deltaTime = nowTime - lastTime;
        lastTime = nowTime;

        sleepTime = timer - nowTime;

        elapsed += deltaTime;

        if (sleepTime > 0.f) {
            Sleep(sleepTime * 1000.f);
        }

        GLFWWrapper::GetInstance()->PollEvents();

        glClearColor(0.5f, 0.4f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        mPtrScene->Update(deltaTime);
        mPtrScene->Draw();
        mPtrScene->DrawButton();
        DrawFPS(std::to_string(1.f/deltaTime));

        if(elapsed > 0.05f) {
            mPtrScene->UpdateButtonColor();
            elapsed = 0.f;
        }

        GLFWWrapper::GetInstance()->SwapBuffers();

    }
}

void SlotMachineEngine::DrawFPS(std::string fps) {
    mPtrTextRenderer->RenderText(fps,
                                 GLFWWrapper::GetInstance()->GetWidth() - 100.f,
                                 GLFWWrapper::GetInstance()->GetHeight() - 24.f,
                                 1.0f,
                                 glm::vec3(0.3f, 0.2f, 0.8f));
}
