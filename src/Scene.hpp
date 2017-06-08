#pragma once

#include <vector>
#include <random>

#include "SpriteRenderer.hpp"
#include "SceneObject.hpp"

struct SlotParams {
    float mVelocity = 0.f;
    float mAcceleration = 0.f;
    float mTime = 0.f;

    SlotParams() = default;
    SlotParams(float vel, float acc, float time) : mVelocity(vel),
                                                   mAcceleration(acc),
                                                   mTime(time)
    {}

    ~SlotParams() = default;
    SlotParams(SlotParams const &) = default;
    SlotParams &operator=(SlotParams const &) = default;

    bool operator<(SlotParams const & rhs) const {
        return mTime < rhs.mTime;
    }
};

class Scene {
public:
    Scene();
    ~Scene() = default;

    void Draw();
    void Update(float deltaTime);
    void GenerateReelParams();

private:
    std::vector<SceneObject> mSlots;
    SpriteRenderer mSpriteRenderer;
    std::minstd_rand0 mRandGenerator;

    uint32_t mSlotsCountX = 5;
    uint32_t mSlotsCountY = 3;
    uint32_t mSlotsCountPool = mSlotsCountX * mSlotsCountY * 2;

    float mSlotsFieldWidth = 0.f;
    float mSlotsFieldHeight = 0.f;
    float mSlotWidth = 0.f;
    float mSlotHeight = 0.f;

    std::vector<SlotParams> mTargetParams;
};