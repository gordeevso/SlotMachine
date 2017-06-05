#pragma once

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

    void Init();
    void Run();

private:



};
