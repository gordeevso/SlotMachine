
#include "TimeManager.hpp"

TimeManager::TimeManager() : mLastGetTime{},
                             mTimeCollector{},
                             mFrameTime{},
                             mFps{} {
    mTimeCollector = std::chrono::steady_clock::now();
}

void TimeManager::UpdateMainLoop() {
    mTimeCollector += TARGET_FRAME_TIME;

    mTimeNow = std::chrono::steady_clock::now();
    mFrameTime = mTimeNow - mLastGetTime;
    mLastGetTime = mTimeNow;

    mSleepTime = mTimeCollector - mLastGetTime;

    if (mSleepTime > std::chrono::steady_clock::duration::zero()) {
        std::this_thread::sleep_for(mSleepTime);
    }
}

float TimeManager::GetTimeNow() const noexcept {
    return mTimeNow.time_since_epoch().count();
}

void TimeManager::Reset() noexcept {
    mFrameTime = std::chrono::steady_clock::duration::zero();
    mLastGetTime = std::chrono::steady_clock::now();
    mTimeCollector = std::chrono::steady_clock::now();
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

