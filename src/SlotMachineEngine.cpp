#include "SlotMachineEngine.hpp"
#include "GLFWWrapper.hpp"

float const FPS_UPDATE_LIMIT_TIME = 0.05f;

SlotMachineEngine::SlotMachineEngine() : mPtrTimeManager(new TimeManager),
                                         mPtrScene(new Scene),
                                         mPtrTextRenderer(new TextRenderer),
                                         mPtrRenderToTexture(new RenderToTexture)
{}


void SlotMachineEngine::Run() {

    mPtrTimeManager->UpdateMainLoop();
    float lastFPS {};

    while(!(GLFWWrapper::GetInstance()->CheckCloseWindow())) {
        //update frame time based on constand target fps
        mPtrTimeManager->UpdateMainLoop();

        //polling events like mouse button click
        GLFWWrapper::GetInstance()->PollEvents();

        //calculating all moves
        mPtrScene->Update(mPtrTimeManager->FrameTime());

        //drawing all stuff to texture
        //then drawing this texture
        mPtrRenderToTexture->PreRender();

        //drawing all slots
        mPtrScene->Draw();
        mPtrScene->DrawButton();

        //updating fps and button color more smoothly
        if(mPtrTimeManager->GetElapsed() > FPS_UPDATE_LIMIT_TIME) {
            mPtrScene->UpdateButtonColor();
            DrawFPS(std::to_string(static_cast<int32_t>(mPtrTimeManager->FramesPerSecond())));
            lastFPS = mPtrTimeManager->FramesPerSecond();
            mPtrTimeManager->ResetElapsed();
        }
        else {
            DrawFPS(std::to_string(static_cast<int32_t>(lastFPS)));
        }

        //drawing texture with all stuff
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
