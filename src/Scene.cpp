
#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>

#include "Scene.hpp"
#include "GLFWWrapper.hpp"
#include "ResourceManager.hpp"

Scene::Scene() : mSlots{},
                 mSpriteRenderer{},
                 mRandGenerator{static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count())},
                 mTargetParams{} {
    Scene::GenerateReelParams();

    float posX = mSlotsFieldWidth +
                 (GLFWWrapper::GetInstance()->GetWidth() - mSlotsFieldWidth) / 2.f -
                 ResourceManager::GetTexture("button")->GetWidth() / 2.f;
    float posY = GLFWWrapper::GetInstance()->GetHeight() / 2.f -
                 ResourceManager::GetTexture("button")->GetHeight() / 2.f;

    glm::vec2 positionVec(posX, posY);
    glm::vec2 sizeVec(ResourceManager::GetTexture("button")->GetWidth(),
                      ResourceManager::GetTexture("button")->GetHeight());
    glm::vec2 velocityVec(0.f, 0.f);
    glm::vec3 colorVec(1.f, 1.f, 1.f);

    mButton = SceneObject{0,
                          positionVec,
                          sizeVec,
                          colorVec,
                          velocityVec,
                          ResourceManager::GetTexture("button")};

}

void Scene::Draw(){
    for (auto &slot: mSlots) {
        auto pos = slot.GetPosition();
        if (pos.y < mSlotsFieldHeight && pos.y > -mSlotHeight) {
            slot.Draw(mSpriteRenderer);
        }

        mButton.Draw(mSpriteRenderer);
    }
}

void Scene::Update(float deltaTime) {

    for(auto & slot: mSlots) {
        auto pos = slot.GetPosition();
        auto num = slot.GetReelNumber();
        auto vel = slot.GetVelocity();
        auto id = slot.GetId();

        if(vel.y <= 0.f) {
            vel.y = 0.f;
            slot.SetVelocity(vel);

            if(static_cast<uint32_t>(pos.y) % static_cast<uint32_t>(mSlotHeight) != 0) {
                glm::vec2 velFinish {0.f, 16.f};
                pos.y += velFinish.y * deltaTime;
                slot.SetPosition(pos);
                for(auto & slotInner: mSlots) {
                    auto posInner = slotInner.GetPosition();
                    if(num == slotInner.GetReelNumber() && id != slotInner.GetId()) {
                        posInner.y += velFinish.y * deltaTime;
                        slotInner.SetPosition(posInner);
                    }
                }
            }
            else {
                slot.SetReadyForStart(true);
            }
            continue;
        }

        if(pos.y + vel.y * deltaTime > mSlotHeight * 5) {
            pos.y -= mSlotHeight * 6;
        }

        vel.y += mTargetParams[num].mAcceleration * deltaTime;
        pos.y += vel.y * deltaTime;

        slot.SetVelocity(vel);
        slot.SetPosition(pos);
    }

    double mousePosX {};
    double mousePosY {};
    GLFWWrapper::GetInstance()->GetCursorPos(&mousePosX, &mousePosY);

    if(mousePosX > mButton.GetPosition().x &&
       mousePosX < mButton.GetPosition().x + mButton.GetSize().x &&
       mousePosY > mButton.GetPosition().y &&
       mousePosY < mButton.GetPosition().y + mButton.GetSize().y &&
       GLFWWrapper::GetMouseButtonState() &&
       Scene::CheckReadinessForStart()) {

        GenerateReelParams();
        for(auto & slot: mSlots) {
            uint32_t reelNum = slot.GetReelNumber();
            slot.SetVelocity({0.f, mTargetParams[reelNum].mVelocity});
        }

    }
}

void Scene::GenerateReelParams() {
    mTargetParams.clear();
    mSlots.clear();

    mSlotsFieldHeight = GLFWWrapper::GetInstance()->GetHeight();
    mSlotsFieldWidth = mSlotsFieldHeight / 3.f * 5.f;

    std::cout << "slotField params "
              << "width = " << mSlotsFieldWidth << " "
              << "height = " << mSlotsFieldHeight << "\n";

    mSlotWidth = static_cast<GLfloat>(mSlotsFieldWidth) / mSlotsCountX;
    mSlotHeight = static_cast<GLfloat>(mSlotsFieldHeight) / mSlotsCountY;

    std::cout << "slot params "
              << "width = " << mSlotWidth << " "
              << "height = " << mSlotHeight << "\n";

    float velocity{};
    float time{};
    float path{};
    float acceleration{};

    uint32_t minSlotPath{10};
    uint32_t maxSlotPath{30};
    uint32_t minTimeMSec{240};
    uint32_t maxTimeMSec{300};

    for (uint32_t i = 0; i != mSlotsCountX; ++i) {
        auto pathInSlots = (mRandGenerator() % (maxSlotPath - minSlotPath)) + minSlotPath;
        path = pathInSlots * mSlotHeight;

        time = static_cast<float>((mRandGenerator() % (maxTimeMSec - minTimeMSec)) + minTimeMSec);
        time /= 60.f;

        velocity = 2 * path / time;
        acceleration = -(velocity / time);

        mTargetParams.push_back(std::move(SlotParams{velocity, acceleration, time}));
    }

    std::sort(mTargetParams.begin(), mTargetParams.end());

    int32_t reelNum{};
    for(auto const & p: mTargetParams) {
        std::cout << "slot number " << reelNum << " "
                  << "vel = " << p.mVelocity<< " "
                  << "time = " << p.mTime << " "
                  << "acc = " << p.mAcceleration<< " "
                  << "\n";
        ++reelNum;
    }

    glm::vec2 positionVec(0.f, 0.f);
    glm::vec2 sizeVec(mSlotWidth, mSlotHeight);
    glm::vec2 velocityVec(0.f, 0.f);
    glm::vec3 colorVec(1.f, 1.f, 1.f);

    mSlots.reserve(mSlotsCountPool);
    uint32_t cnt{1};
    uint32_t reelNumber{0};

    std::vector<std::string> vecSlotTextureNames {ResourceManager::GetTextureNames().begin(), ResourceManager::GetTextureNames().end()};
    vecSlotTextureNames.erase(std::find(vecSlotTextureNames.begin(), vecSlotTextureNames.end(), "button"));

    auto texturesCount = vecSlotTextureNames.size();

    std::cout << "texture count = " << texturesCount << "\n";

    size_t cntTexture {};
    for (uint32_t i = 0; i != mSlotsCountPool; ++i) {

        mSlots.push_back(std::move(SceneObject{reelNumber,
                                               positionVec,
                                               sizeVec,
                                               colorVec,
                                               velocityVec,
                                               ResourceManager::GetTexture(vecSlotTextureNames[cntTexture])}));
        ++cntTexture;
        if(cntTexture == texturesCount) cntTexture = 0;

        if (cnt == mSlotsCountY * 2) {
            ++reelNumber;
            cnt = 1;
            positionVec.y = 0.f;
            positionVec.x += sizeVec.x;
        } else {
            positionVec.y += sizeVec.y;
            ++cnt;
        }

        mSlots.back().SetReadyForStart(false);
    }

}

void Scene::SetReadiness(bool isReady) noexcept {
    for(auto & slot: mSlots)
        slot.SetReadyForStart(isReady);
}

bool Scene::CheckReadinessForStart() const noexcept {
    for(auto & slot: mSlots) {
        if (!slot.GetReadyForStart()) return false;
    }
    return true;
}

