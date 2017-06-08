#pragma once

#include <chrono>
#include <thread>

typedef std::chrono::duration<float> duration_float_seconds;
typedef std::chrono::time_point< std::chrono::steady_clock, duration_float_seconds > timepoint_float_seconds;

duration_float_seconds const TARGET_FRAME_RATE (150.0);
duration_float_seconds const TARGET_FRAME_TIME (1.0/TARGET_FRAME_RATE.count());

class TimeManager
{
public:
    explicit TimeManager();
    ~TimeManager() = default;
    TimeManager(TimeManager const &) = delete;
    TimeManager & operator=(TimeManager const &) = delete;

    void UpdateMainLoop();
    float GetTimeNow() const noexcept ;
    void Reset() noexcept ;
    float FrameTime() noexcept ;
    float FramesPerSecond() noexcept ;

private:
    timepoint_float_seconds mLastGetTime;
    timepoint_float_seconds mTimeCollector;
    timepoint_float_seconds mTimeNow;
    duration_float_seconds mFrameTime;
    duration_float_seconds mSleepTime;
    float mFps;
};

