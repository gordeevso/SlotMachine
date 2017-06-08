
#include <iostream>
#include "TimeManager.hpp"
#include "GLFWWrapper.hpp"

TimeManager::TimeManager() : mLastGetTime{},
                             mTimeCollector{},
                             mFrameTime{},
                             mFps{} {
    mTimeCollector = std::chrono::high_resolution_clock::now();
}

void TimeManager::UpdateMainLoop() {
    mTimeCollector += TARGET_FRAME_TIME;

    mLastGetTime = std::chrono::high_resolution_clock::now();
    mFrameTime = mLastGetTime - mTimeNow;
    mTimeNow = mLastGetTime;

    std::cout << mFrameTime.count() <<  " " << TARGET_FRAME_TIME.count() << "\n";
    mSleepTime = mTimeCollector - mLastGetTime;

    if (mSleepTime > std::chrono::high_resolution_clock::duration::zero()) {
        std::this_thread::sleep_for(mSleepTime);
    }
}

float TimeManager::GetTimeNow() const noexcept {
    return mTimeNow.time_since_epoch().count();
}

void TimeManager::Reset() noexcept {
    mFrameTime = std::chrono::high_resolution_clock::duration::zero();
    mLastGetTime = std::chrono::high_resolution_clock::now();
    mTimeCollector = std::chrono::high_resolution_clock::now();
}

float TimeManager::FrameTime() noexcept {
    return mFrameTime.count();
}

float TimeManager::FramesPerSecond() noexcept {
    if (mFrameTime > std::chrono::steady_clock::duration::zero()) {
        mFps = 1.f / FrameTime();
        return mFps;
    }
    return 0.0;
}

