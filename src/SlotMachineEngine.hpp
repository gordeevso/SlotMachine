#pragma once

#include <memory>

#include "TimeManager.hpp"
#include "Scene.hpp"
#include "TextRenderer.hpp"
#include "RenderToTexture.hpp"

class SlotMachineEngine {
public:
    static SlotMachineEngine * GetInstance() noexcept {
        static SlotMachineEngine instance;
        return &instance;
    }

private:
    SlotMachineEngine();
    SlotMachineEngine(SlotMachineEngine const &) = delete;
    SlotMachineEngine & operator=(SlotMachineEngine const &) = delete;


public:
    ~SlotMachineEngine() = default;

    void Run();
    void DrawFPS(std::string fps);

private:

    std::shared_ptr<TimeManager> mPtrTimeManager;
    std::shared_ptr<Scene> mPtrScene;
    std::shared_ptr<TextRenderer> mPtrTextRenderer;
    std::shared_ptr<RenderToTexture> mPtrRenderToTexture;
};
