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
    void DrawButton();

    void Update(float deltaTime);
    void UpdateButtonColor();
    void GenerateReelParams();

    bool CheckReadinessForStart() const noexcept;

private:
    std::vector<SceneObject> mSlots;
    SceneObject mButton;
    //needed for correct color updating
    //0.f -> 1.f  then 1.f -> 0.f
    bool mButtonColorState = true;

    //Slot and button drawing
    SpriteRenderer mSpriteRenderer;

    //used for generating target animating time (4 - 5 sec)
    //and generating path for each slot
    std::minstd_rand0 mRandGenerator;

    uint32_t mSlotsCountX = 5;
    uint32_t mSlotsCountY = 3;
    //Total slots count
    uint32_t mSlotsCountPool = mSlotsCountX * mSlotsCountY * 2;

    float mSlotsFieldWidth = 0.f;
    float mSlotsFieldHeight = 0.f;
    float mSlotWidth = 0.f;
    float mSlotHeight = 0.f;

    std::vector<SlotParams> mTargetParams;
};